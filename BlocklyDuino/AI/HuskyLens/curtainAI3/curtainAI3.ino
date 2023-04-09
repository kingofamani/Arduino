#include "HUSKYLENS.h"
#include <Stepper.h>
#include <SoftwareSerial.h>
#include <IRremote.h>
#include <Servo.h>

HUSKYLENS huskylens;
//物體識別閾值，連續識別正確次數
int recValue = 100;
//辨識ID的次數
int countIDs[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//訓練的ID
int IDs[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//辨識的ID
int ReplyID = 0;

//步進馬達
int steps = 2048;
Stepper myStepper(steps, 8, 10, 9, 11);

//ESP32S2 WiFi
SoftwareSerial ESP32S2Serial(7, 6);

//銀髮族：房間,x,y,
String elderlyInfo;

//是否立即暫停窗簾
boolean isStopNow = false;
//窗簾全開最大轉數(1圈8轉)
int maxTurns = 22;
//窗簾目前位置
int posTurns = 22;

//紅外線接收器
IRrecv irrecv(3);
decode_results results;


//伺服馬達(pin D2)
Servo myServo;

//光敏電阻A0
//int ldrPin = A0;

//模式
//a手勢 b防盜 c守護
char whichMode = 'a';

void printResult(HUSKYLENSResult result);

void initHL() {
  Wire.begin();
  while (!huskylens.begin(Wire))
  { Serial.println(F("Begin failed!"));
    Serial.println(F("1.Please recheck the Protocol Type in HUSKYLENS (General Settings>>Protocol Type>>I2C)"));
    Serial.println(F("2.Please recheck the connection."));
    delay(100);
  }
  huskylens.writeAlgorithm(ALGORITHM_OBJECT_CLASSIFICATION);
}

void startRecog() {
  if (huskylens.request())
  {
    HUSKYLENSResult result;
    //連續辨別成功次數
    for (int i = 0; i < sizeof(IDs) / sizeof(IDs[0]); i++) {
      if (huskylens.countBlocks(IDs[i]) >= 1) {
        countIDs[IDs[i]]++;
      }
    }
    //判斷哪個ID達到閾值
    for (int i = 0; i < sizeof(countIDs) / sizeof(countIDs[0]); i++) {
      if (countIDs[i] >= recValue) {
        result = huskylens.getBlock(i, 0);
        printResult(result);
        //重置
        for (int j = 0; j < sizeof(countIDs) / sizeof(countIDs[0]); j++) {
          countIDs[j] = 0;
        }
      }
    }
  }   else   {
    Serial.println("失敗!無法從Huskylens請求物件!");
  }
}

void printResult(HUSKYLENSResult result) {
  if (result.command == COMMAND_RETURN_BLOCK) {
    //Serial.println(String() + F("方框:X中心=") + result.xCenter + F(",Y中心=") + result.yCenter + F(",寬=") + result.width + F(",高=") + result.height + F(",ID=") + result.ID);
    ReplyID = result.ID;
    //Serial.println(ReplyID);
    if (ReplyID == 4 && whichMode == 'c') {
      elderlyInfo = String() + F("elderly,客廳,") + result.ID + F(",") + result.xCenter + F(",") + result.yCenter + F(",");
      Serial.println(elderlyInfo);
    }
  }
}

void turnStop(float c) {
  Serial.println((String("position：") + String(posTurns)));
  if (c > 0 && posTurns == maxTurns) {
    isStopNow = true;
    //posStatus();
  }
  if (c < 0 && posTurns == 0) {
    isStopNow = true;
    //posStatus();
  }
}

void irrStop() {
  if (irrecv.decode(&results)) {
    if (String(results.value, HEX) == "ffa25d" || String(results.value, HEX) == "e318261b") {
      isStopNow = true;
    }

    irrecv.resume();
  }
}

void recogStop(int stopID) {
  if (huskylens.request()) {
    HUSKYLENSResult result;
    if ((huskylens.countBlocks(IDs[stopID])) >= 1) {
      isStopNow = true;
    }
  }
}

void btStop() {
  if (ESP32S2Serial.available()) {
    String espMsg = (ESP32S2Serial.readString());
    if (espMsg == "3") {
      posStatus();
      isStopNow = true;
    }
  }
}

void sendToEsp(String myMsg) {
  ESP32S2Serial.println(myMsg);
}

void go(float c) {
  int num = ((abs(c)) * 8) - 1;
  for (int i = 0; i <= num; i++) {
    //是否暫停窗簾
    btStop();//藍牙傳送暫停訊息
    turnStop(c);//轉到最底要暫停
    irrStop();//紅外線傳送暫停訊息
    recogStop(3);//AI鏡頭傳送暫停訊息(布)
    if (isStopNow) {
      isStopNow = false;
      sendToEsp("stop,");
      delay(500);
      String posStr=String() + F("position,") + posTurns + F(",");
      sendToEsp(posStr);
      break;
    }
    //旋轉
    if (c >= 0) {
      posTurns = posTurns + 1;
      myStepper.step(256);
    } else {
      posTurns = posTurns + -1;
      myStepper.step(-256);
    }
  }
}

void posStatus() {
  String pos = String() + F("position,") + posTurns + F(",");
  sendToEsp(pos);
  Serial.println(pos);

}

void notifyFindThief() {
  //sendToEsp("FindThiefBeCareful");
  sendToEsp("line,客廳,警告！偵測到不明人士，請留意公寓門窗狀況,");  
  delay(5000);
  //ESP32S2Serial.print("line,客廳,警告！偵測到小偷，請留意家中狀況,");
}

void setup()
{
  Serial.begin(9600);
  //BtDevice.begin(9600);
  ESP32S2Serial.begin(9600);
  //初始AI鏡頭
  initHL();
  //初始紅外線搖控
  irrecv.enableIRIn();
  //初始步進馬達
  myStepper.setSpeed(12);
  go(-10);
  posTurns = 0;
  sendToEsp("working,");//啟動中

  //初始伺服馬達
  myServo.attach(2);
  myServo.write(0);
  delay(1000);
}


void loop()
{

  //AI識別
  startRecog();
  if (ReplyID != 0) {
    if (ReplyID == 1) {
      go(10);
    } else if (ReplyID == 2) {
      go(-10);
    } else if (ReplyID == 4 && whichMode == 'b') {
      Serial.println("notifyFindThief");
      notifyFindThief();      
    }
    else if (ReplyID == 4 && whichMode == 'c') {
      Serial.println(elderlyInfo);
      sendToEsp(elderlyInfo);
      delay(10000);
      //ESP32S2Serial.print(elderlyInfo);
    }
    ReplyID = 0;
  }

  //紅外線搖控
  if (irrecv.decode(&results)) {
    //Serial.println(String(results.value, HEX));
    if (String(results.value, HEX) == "ff02fd") {
      go(10);
    }
    if (String(results.value, HEX) == "ffc23d") {
      go(-10);
    }

    irrecv.resume();
  }

  //傳送訊息：UNO序列埠視窗→ESP32S2
  if (Serial.available()) {
    String str = Serial.readString();
    sendToEsp(str);
  }

  //接收訊息：ESP32S2→UNO
  if (ESP32S2Serial.available()) {
    String espMsg = ESP32S2Serial.readString();
    Serial.println(espMsg);
    if (espMsg == "1") {
      go(10);
    } else if (espMsg == "2") {
      go(-10);
    } else if (espMsg == "p") {
      posStatus();
    } else if (espMsg == "a") {
      //物體分類(手勢)
      whichMode = 'a';
      huskylens.writeAlgorithm(ALGORITHM_OBJECT_CLASSIFICATION);
      myServo.write(0);
      delay(1000);
    } else if (espMsg == "b") {
      //物體識別(不明人士)
      whichMode = 'b';
      huskylens.writeAlgorithm(ALGORITHM_OBJECT_RECOGNITION);
      myServo.write(180);
      delay(1000);
    }
    else if (espMsg == "c") {
      //物體識別(銀髮族)
      whichMode = 'c';
      huskylens.writeAlgorithm(ALGORITHM_OBJECT_RECOGNITION);
      myServo.write(0);
      delay(1000);
    }else if (espMsg == "getUp") {
      go(10);
      Serial.println("天亮起床");
    }else if (espMsg == "goToSleep") {
      go(-10);
      Serial.println("夜晚睡覺");
    }
  }



}//end loop
