/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Wed, 17 Mar 2021 07:16:39 GMT
 */

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

String myCardId;

int  count;

int play1TimeId;

int myNumber;

boolean isScanCardId;

int distance;

boolean isScanTemp;

float amb;

float obj;

boolean isPlay1Mute;

int playStudentTimeId;

int playTempTimeId;

int playTodayTempTimeId;

int playNextTimeId;

float WARNING_TEMPERATURE;

//學生卡號與溫度
const int NUMS = 6;
String cards[NUMS] = { "B936FFC1", "7AEDED6E", "D0241E10", "1ABCB76E", "6A62A76E",""};
float temps[NUMS] = { 0.00, 0.00, 0.00, 0.00, 0.00, 0.00};
//MP3宣告
SoftwareSerial mySoftwareSerial(7, 8);
DFRobotDFPlayerMini myDFPlayer;
//計時器
SimpleTimer timer;
Ultrasonic ultrasonic(5, 6);
MFRC522 rfid(/*SS_PIN*/ 10, /*RST_PIN*/ UINT8_MAX);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);
Servo motor;
void t0() {
  //紅外線體溫計
  //LCD螢幕
  //馬達
}

void var1() {
  //播歡迎光臨,請量體溫的time id
  play1TimeId = 0;
  //紅外線測距
  distance = 0;
  //RFID卡號
  myCardId = "";
  //學生座號
  myNumber = 0;
  //是否掃RFID
  isScanCardId = false;
  //播學生座號姓名&請將額頭靠近體溫計的time id
  playStudentTimeId = 0;
  //播學生座號姓名&請將額頭靠近體溫計的time id
  playStudentTimeId = 0;
  //設定「請將卡片對準刷卡機mp3」靜音切換
  isPlay1Mute = false;
  //是否量體溫(要靠近紅外線體溫計取得溫度才算
  isScanTemp = false;
  //播體溫測量結果time id
  playTempTimeId = 0;
  //播放今天已量過體溫
  playTodayTempTimeId = 0;
  //播換下一位同學time id
  playNextTimeId = 0;
  //室溫
  amb = 0;
  //體溫
  obj = 0;
  //高溫警示
  WARNING_TEMPERATURE = 37.5;
}

void mp3init() {
  mySoftwareSerial.begin(9600);
  if (!(myDFPlayer.begin(mySoftwareSerial))) {
  while (true) { }
  }
  myDFPlayer.volume(30);
  //歡迎光臨請刷卡mp3 timer
  play1TimeId = timer.setInterval(3500, RepeatPlay1);
  timer.disable(play1TimeId);
  //學生姓名座號mp3 timer
  playStudentTimeId = timer.setInterval(5500, playStudent);
  timer.disable(playStudentTimeId);
  //體溫測量結果 mp3 timer
  playTempTimeId = timer.setInterval(2000, playTemp);
  timer.disable(playTempTimeId);
  playTodayTempTimeId = timer.setInterval(6000, playTempScanned);
  timer.disable(playTodayTempTimeId);
  playNextTimeId = timer.setInterval(2500, playNext);
  timer.disable(playNextTimeId);
}

void motoInit() {
  motor.attach(3);
  motor.write(45);//旗放下
  delay(1000);
  motor.detach();//停止
}

void RepeatPlay1() {
  myDFPlayer.playFolder(1, 1);//01請將卡片對準刷卡機
}

bool hasTodayScannedTemp() {
return temps[myNumber] > 0;
}
void hasTodayScannedTemp0() {
}

void playTempScanned() {
  myDFPlayer.playFolder(1, 11);//今天已量過體溫mp3
  delay(6000);
  timer.disable(playTodayTempTimeId);
}

void playStudent() {
  if (myNumber > 0 && !isScanTemp) {
    myDFPlayer.playFolder(2, myNumber);
    delay(2000);
    myDFPlayer.playFolder(1, 5);//05請將額頭靠近體溫計

  }
}

void playTemp() {
  if (obj > WARNING_TEMPERATURE) {
    myDFPlayer.playFolder(1, 8);//體溫過高mp3
    //舉旗(溫度太高)
    motor.attach(3);
    motor.write(170);
    delay(675);
    motor.detach();

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
  myNumber = 0;
  isScanCardId = false;
  isScanTemp = false;
  amb = 0;
  obj = 0;
  timer.disable(play1TimeId);
  timer.disable(playStudentTimeId);
  timer.disable(playTempTimeId);
  timer.disable(playTodayTempTimeId);
  timer.disable(playNextTimeId);
  motor.attach(3);
  motor.write(45);
  delay(675);
  motor.detach();
}

void setTemp() {
  temps[myNumber] = obj;
}

int getStudentNum(String id) {
for (int i = 0; i < NUMS; i++) {
if (cards[i] == id) {
return i;
}
}
return 0;
}
void getStudentNum0() {
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
rfid.PICC_HaltA();
rfid.PCD_StopCrypto1();
return ret;
}
void mfrc522_readID0() {
}

void beep() {
  for (count = 0; count <= 80; count++) {
    digitalWrite(4, LOW);
    delay(1);
    digitalWrite(4, HIGH);
    delay(1);
  }
  digitalWrite(4, HIGH);
}

void draw() {
  u8g.setFont(u8g_font_osb21);
  u8g.setPrintPos(10, 29);
  u8g.drawStr( 10, 29, "^____^");
  u8g.setPrintPos(10, 63);
  u8g.print(obj, 1);
  u8g.drawStr( 80, 63, "*C");
}

void setup()
{
  Serial.begin(115200);

  //變數宣告
  var1();
  //MP3 初始
  mp3init();
  //RFID 初始
  SPI.begin();
  rfid.PCD_Init();
  //紅外線體溫
  mlx.begin();
  //馬達接D3腳位
  motoInit();
  pinMode(4, OUTPUT);
}


void loop()
{
  //timer啟用
  timer.run();
  //紅外線測距
  distance = ultrasonic.read();
  if (distance < 60 && (isScanCardId == false && (isScanTemp == false && isPlay1Mute == false))) {
    timer.enable(play1TimeId);

  } else {
    timer.disable(play1TimeId);

  }
  if (isScanCardId == false) {
    myCardId = mfrc522_readID();
    myCardId.toUpperCase();
    myNumber = getStudentNum(myCardId);
    if ((myCardId.length()) > 0) {
      ////今天是否已經量過體溫
      if (hasTodayScannedTemp()) {
        timer.enable(playTodayTempTimeId);//播今天已量過體溫mp3
        isScanCardId = false;

      } else {
        if (myCardId == cards[0]) {
          isPlay1Mute = !isPlay1Mute;

        } else {
          isScanCardId = true;
          timer.enable(playStudentTimeId);//播幾號同學mp3
          timer.disable(playTodayTempTimeId);

        }

      }
      beep();
      delay(100);

    }

  }
  //體溫檢查
  amb = mlx.readAmbientTempC();
  obj = mlx.readObjectTempC();
  if (isScanCardId == true && obj > 34) {
    delay(2000);
    obj = mlx.readObjectTempC();//2秒後取得體溫,若還是>34度才取值
    if (obj > 32) {
      timer.enable(playTempTimeId);//播體溫測量結果mp3
      isScanTemp = true;
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
}