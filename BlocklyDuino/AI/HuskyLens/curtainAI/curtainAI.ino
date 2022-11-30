/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Wed, 30 Nov 2022 00:28:24 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include "HUSKYLENS.h"
#include <Stepper.h>
#include <SoftwareSerial.h>
#include <IRremote.h>
#include <Servo.h>

HUSKYLENS huskylens;
int recValue = 100;

int countIDs[6] = {0, 0, 0, 0, 0, 0};

int IDs[6] = {0, 1, 2, 3, 4, 5};

int ReplyID = 0;

void printResult(HUSKYLENSResult result);
int steps=2048;
Stepper myStepper(steps, 8, 10, 9, 11);
SoftwareSerial BtDevice(4, 5);
boolean isStopNow = false;

int maxTurns = 22;

int posTurns = 22;

IRrecv irrecv(3);
decode_results results;
boolean isObjectRecognitionMode = false;

Servo __myservo2;
void initHL() {
  Wire.begin();
  while (!huskylens.begin(Wire))
  {     Serial.println(F("Begin failed!"));
  Serial.println(F("1.Please recheck the Protocol Type in HUSKYLENS (General Settings>>Protocol Type>>I2C)"));
  Serial.println(F("2.Please recheck the connection."));
  delay(100);
  }   huskylens.writeAlgorithm(ALGORITHM_OBJECT_CLASSIFICATION);
}

void startRecog() {
  if (huskylens.request())
  {
  HUSKYLENSResult result;
  //連續辨別成功次數
  for (int i = 0; i < sizeof(IDs) / sizeof(IDs[0]); i++) {
  if (huskylens.countBlocks(IDs[i]) >= 1) {
  countIDs[IDs[i]]++;
  }     }
  //判斷哪個ID達到閾值
  for (int i = 0; i < sizeof(countIDs) / sizeof(countIDs[0]); i++) {
  if (countIDs[i] >= recValue) {
  result = huskylens.getBlock(i, 0);
  printResult(result);
  //重置
  for (int j = 0; j < sizeof(countIDs) / sizeof(countIDs[0]); j++) {
  countIDs[j] = 0;
  }       }     }
  }   else   {
  Serial.println("失敗!無法從Huskylens請求物件!");
  }
}

void printResult(HUSKYLENSResult result) {
if (result.command == COMMAND_RETURN_BLOCK) {
Serial.println(result.ID);
ReplyID = result.ID;
}
}
void pR() {
}

void turnStop(float c) {
  Serial.println((String("目前位置：")+String(posTurns)));
  if (c > 0 && posTurns == maxTurns) {
    isStopNow = true;
  }
  if (c < 0 && posTurns == 0) {
    isStopNow = true;
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
  if (BtDevice.available()) {
    String btMsg = (BtDevice.readString());
    if (btMsg == "3") {
      posStatus();
      isStopNow = true;
    }
  }
}

void sendToBtDevice(String myMsg) {
  BtDevice.println(myMsg);
}

void go(float c) {
  int num = ((abs(c)) * 8) - 1;
  for (int i = 0; i <= num; i++) {
    //是否中斷
    btStop();
    turnStop(c);
    irrStop();
    recogStop(3);
    if (isStopNow) {
      isStopNow = false;
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
    irrStop();
    if (isStopNow) {
      isStopNow = false;
      break;
    }
  }
}

void posStatus() {
  String pic = "";
  for (int i = 0; i <= maxTurns - 1; i++) {
    pic += (i + posTurns < maxTurns) ? "1" : "0";
  }
  Serial.println(pic);
  sendToBtDevice(pic);
}

void notifyFindThief() {
  sendToBtDevice("FindThiefBeCareful");
}

void setup()
{
  Serial.begin(9600);

  irrecv.enableIRIn();
  __myservo2.attach(2);
  //打開最大轉數(1圈8轉)
  //目前位置
  BtDevice.begin(9600);
  myStepper.setSpeed(12);
  go(-10);
  posTurns = 0;
  initHL();
  //ai鏡頭切換至物體識別(小偷)
  __myservo2.write(0);
  delay(1000);
}


void loop()
{
  //物體識別閾值，連續識別正確次數
//訓練的ID
//辨識的ID

startRecog();
  if (ReplyID != 0) {
    if (ReplyID == 1) {
      go(10);
    } else if (ReplyID == 2) {
      go(-10);
    } else if (ReplyID == 4) {
      notifyFindThief();
    }
    ReplyID = 0;
  }
  if (irrecv.decode(&results)) {
      if (String(results.value, HEX) == "ff02fd") {
      go(10);
    }
    if (String(results.value, HEX) == "ffc23d") {
      go(-10);
    }

    irrecv.resume();
  }
  if (BtDevice.available()) {
    String btMsg = (BtDevice.readString());
    Serial.println(btMsg);
    if (btMsg == "1") {
      go(10);
    } else if (btMsg == "2") {
      go(-10);
    } else if (btMsg == "s") {
      posStatus();
    } else if (btMsg == "a") {
      //物體分類(手勢)
      isObjectRecognitionMode = false;
      huskylens.writeAlgorithm(ALGORITHM_OBJECT_CLASSIFICATION);
      sendToBtDevice("HandMode");
      __myservo2.write(0);
      delay(1000);
    } else if (btMsg == "b") {
      //物體識別(小偷)
      isObjectRecognitionMode = true;
      sendToBtDevice("ThiefMode");
      huskylens.writeAlgorithm(ALGORITHM_OBJECT_RECOGNITION);
      __myservo2.write(180);
      delay(1000);
    }
  }
}