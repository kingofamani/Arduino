#include <SimpleTimer.h>
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <SPI.h>
#include <MFRC522.h>
#include <Ultrasonic.h>
#include <ArduinoSort.h>
#include <Adafruit_MLX90614.h>
#include "U8glib.h"
#include <Servo.h>

//學生卡號與溫度
const int NUMS = 6;
String cards[NUMS] = { "B936FFC1", "7AEDED6E", "D0241E10", "91A64FE1", "",""};//cards[0] B936FFC1設定「請將卡片對準刷卡機mp3」靜音切換
float temps[NUMS] = { 0.00, 0.00, 0.00, 0.00, 0.00, 0.00};
                    
/*
const int NUMS = 30;
String cards[NUMS] = { "B936FFC1", "7AEDED6E", "D0241E10", "91A64FE1", "",
                       "", "", "", "", "",
                       "", "", "", "", "",
                       "", "", "", "", "",
                       "", "", "", "", "",
                       "", "", "", "", ""
                     };//cards[0] B936FFC1設定「請將卡片對準刷卡機mp3」靜音切換
float temps[NUMS] = { 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00,
                      0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00,
                      0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00
                    };
*/

//MP3宣告
SoftwareSerial mySoftwareSerial(7, 8);
DFRobotDFPlayerMini myDFPlayer;

//計時器
SimpleTimer timer;

int play1TimeId;//播歡迎光臨,請量體溫的time id

//紅外線測距
int distance;
Ultrasonic ultrasonic(5, 6);

//RFID卡號
String myCardId;
int myNumber;//學生座號
bool isScanCardId = false;// 是否掃RFID
MFRC522 rfid(/*SS_PIN*/ 10, /*RST_PIN*/ UINT8_MAX);
int playStudentTimeId;//播學生座號姓名&請將額頭靠近體溫計的time id
bool isPlay1Mute = false;//設定「請將卡片對準刷卡機mp3」靜音切換

//紅外線體溫計
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
bool isScanTemp = false;// 是否量體溫(要靠近紅外線體溫計取得溫度才算
//bool isTodayScannedTemp = false;//某位同學今天是否已經量過體溫(一天只能量1次)
int playTempTimeId;//播體溫測量結果time id
int playTodayTempTimeId;//播放今天已量過體溫
int playNextTimeId;//播換下一位同學time id

float amb = 0.00; //室溫
float obj = 0.00; //體溫
const float WARNING_TEMPERATURE = 37.5;//高溫警示

//LCD螢幕
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE); // I2C / TWI ;

//馬達
Servo motor;

void setup() {
  Serial.begin(115200);

  //蜂鳴器
  pinMode(4, OUTPUT);

  //MP3 初始
  mySoftwareSerial.begin(9600);
  if (!(myDFPlayer.begin(mySoftwareSerial))) {
    while (true) { }
  }
  myDFPlayer.volume(30);

  //歡迎光臨請刷卡mp3 timer
  play1TimeId = timer.setInterval(3500, RepeatPlay1); //每隔n秒觸發1次
  //Serial.print("play1TimeId:");
  //Serial.println(play1TimeId);
  timer.disable(play1TimeId);

  //學生姓名座號mp3 timer
  //playStudentTimeId= timer.setTimeout(100, playStudent);//once
  playStudentTimeId = timer.setInterval(5500, playStudent);
  //Serial.print("playStudentTimeId:");
  //Serial.println(playStudentTimeId);
  timer.disable(playStudentTimeId);

  //體溫測量結果 mp3 timer
  playTempTimeId = timer.setInterval(2000, playTemp);
  timer.disable(playTempTimeId);
  //Serial.println("playTempTimeId");
  playTodayTempTimeId = timer.setInterval(6000, playTempScanned);
  timer.disable(playTodayTempTimeId);
  //Serial.println("playTodayTempTimeId");
  playNextTimeId = timer.setInterval(2500, playNext);
  timer.disable(playNextTimeId);
  //Serial.println("playNextTimeId");



  //RFID 初始
  SPI.begin();
  rfid.PCD_Init();

  //紅外線體溫
  mlx.begin();

  //馬達接D3腳位
  motor.attach(3);
  motor.write(45);//旗放下
  delay(1000);//旋轉需要時間
  motor.detach();//停止
}

void loop() {
  //timer啟用
  timer.run();

  //紅外線測距
  distance = ultrasonic.read();
  //Serial.println(distance);

  if (distance < 60 && !isScanCardId && !isScanTemp && !isPlay1Mute) {
    timer.enable(play1TimeId);
    //Serial.println("play1 on");
  } else {
    timer.disable(play1TimeId);
    //Serial.println("play1 off");
  }

  //RFID卡片感應


  //「請將卡片對準刷卡機mp3」靜音切換
  /*
    if(myCardId == cards[0]){
    isPlay1Mute = !isPlay1Mute;
    }*/



  if (!isScanCardId) {
    myCardId = mfrc522_readID();
    myCardId.toUpperCase();
    myNumber = getStudentNum(myCardId);
    if ((myCardId.length()) > 0) {
      //今天是否已經量過體溫
      if (hasTodayScannedTemp()) {
        timer.enable(playTodayTempTimeId);//播今天已量過體溫mp3
        isScanCardId = false;
        //Serial.println("已量過");
      } else {
        if (myCardId == cards[0]) {
          isPlay1Mute = !isPlay1Mute;
          //Serial.println(isPlay1Mute);
          //isPlay1Mute = (myCardId == cards[0]) ? (isPlay1Mute = !isPlay1Mute) : isPlay1Mute;
          //isScanCardId = false;
        } else {
          isScanCardId = true;
          timer.enable(playStudentTimeId);//播幾號同學mp3
          timer.disable(playTodayTempTimeId);

          //Serial.println(myCardId);
        }

      }
      beep();
      delay(100);
    }

  }



  //體溫檢查
  amb = mlx.readAmbientTempC();
  obj = mlx.readObjectTempC();
  if (isScanCardId && obj > 34) {
    delay(2000);
    obj = mlx.readObjectTempC();//2秒後取得體溫,若還是>34度才取值
    if (obj > 34) {
      timer.enable(playTempTimeId);//播體溫測量結果mp3
      isScanTemp = true;
      //Serial.println(obj);
      setTemp();//儲存同學體溫
      delay(10);
    }
  }

  //LCD螢幕

  u8g.firstPage();
  do {
    draw();
  } while ( u8g.nextPage() );
  delay(100);


}//loop end


void RepeatPlay1() {
  //myDFPlayer.play(1);
  myDFPlayer.playFolder(1, 1);//01請將卡片對準刷卡機
  //Serial.println("每隔n秒執行1次");
}

bool hasTodayScannedTemp() {
  //int num = getStudentNum(myCardId);
  return temps[myNumber] > 0;
}

void playTempScanned() {
  myDFPlayer.playFolder(1, 11);//今天已量過體溫mp3
  delay(6000);
  timer.disable(playTodayTempTimeId);
}

void playStudent() {
  //int num = getStudentNum(myCardId);
  //Serial.println(myCardId);
  //Serial.println(num);
  if (myNumber > 0 && !isScanTemp) {
    /*
       讀取SD:01資料夾第num個mp3
       ★命名規則：資料夾01~99、檔名001xxx.mp3~255xxx.mp3，其中xxx可為中文
    */
    myDFPlayer.playFolder(2, myNumber);
    //Serial.print("學生:");
    //Serial.println(myNumber);
    delay(2000);
    myDFPlayer.playFolder(1, 5);//05請將額頭靠近體溫計
    //timer.disable(playStudentTimeId);
  }
}

void playTemp() {
  if (obj > WARNING_TEMPERATURE) {
    myDFPlayer.playFolder(1, 8);//體溫過高mp3
    //舉旗(溫度太高)
    motor.attach(3);
    motor.write(170);
    //Serial.print("170！");
    delay(675);
    motor.detach();
    //Serial.print("體溫過高！");
  } else {
    myDFPlayer.playFolder(1, 9);//體溫正常mp3
  }
  beep();
  timer.disable(playTempTimeId);
  timer.enable(playNextTimeId);
}

void playNext() {
  myDFPlayer.playFolder(1, 10);//10請換下一位同學mp3
  delay(2500);
  timer.disable(playNextTimeId);
  Init();//初始變數
}

void Init() {
  myCardId = "";
  myNumber=0;
  isScanCardId = false;
  isScanTemp = false;
  amb = 0.00;
  obj = 0.00;
  timer.disable(play1TimeId);
  timer.disable(playStudentTimeId);
  timer.disable(playTempTimeId);
  timer.disable(playTodayTempTimeId);
  timer.disable(playNextTimeId);
  
  motor.attach(3);
  motor.write(45);
  delay(675);
  motor.detach();
  //Serial.println("Init");
}

void setTemp() {
  //int num = getStudentNum(myCardId);
  temps[myNumber] = obj;
  /*
    for (int i = 0; i < NUMS; i++) {
    Serial.print(temps[i]);
    Serial.print(",");
    }
    Serial.println();
  */
}

int getStudentNum(String id) {
  for (int i = 0; i < NUMS; i++) {
    if (cards[i] == id) {
      return i;
    }
  }
  return 0;
}

String mfrc522_readID()
{
  String ret;
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial())
  {
    MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);

    for (byte i = 0; i < rfid.uid.size; i++) {
      ret += (rfid.uid.uidByte[i] < 0x10 ? "0" : "");
      ret += String(rfid.uid.uidByte[i], HEX);
    }
  }

  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
  return ret;
}


void beep() {
  for (int count = 0; count < 80; count++) {
    digitalWrite(4, LOW);
    delay(1);
    digitalWrite(4, HIGH);
    delay(1);
  }
  digitalWrite(4, HIGH);
}


void draw() {
  u8g.setFont(u8g_font_osb21);//u8g_font_fur25
  /*
  u8g.setPrintPos(10, 29);
  u8g.print(amb, 1);
  u8g.drawStr( 80, 29, "*C");
  */
  u8g.setPrintPos(10, 29);
  u8g.drawStr( 10, 29, "^____^");
  
  u8g.setPrintPos(10, 63);
  u8g.print(obj, 1);
  u8g.drawStr( 80, 63, "*C");
}
