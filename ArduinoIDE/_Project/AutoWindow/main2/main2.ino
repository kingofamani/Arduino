/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Wed, 03 Mar 2021 23:35:10 GMT
 */

#include <Stepper.h>
#include <DHT.h>
#include <SPI.h>
#include <Wire.h>
#include <SoftwareSerial.h>

int pinPowerOn;

int pinPowerOff;

float tem;

boolean isPowerOff;

int preheatSec;

unsigned long th;

unsigned long tl;

unsigned long co2;

float HIGH_CO2;

int ledPower;

int delayTime;

float dustVal;

float MID_CO2;

int dustPin;

int delayTime2;

float LOW_CO2;

float offTime;

float pm25;

float HIGH_PM25;

float MID_PM25;

float LOW_PM25;

float MAX_TEP;

float MIN_TEP;

int i;

#define pwmPin 3 //D3腳位
Stepper myStepper(2048, 8, 10, 9, 11);//D8,9,10,11腳位
DHT dht11(12, DHT11);//D12腳位
void openWindow(float circle) {
int steps = abs(circle) * 9 - 1;
for (i = 0; i <= abs(steps); i++) {
if (circle >= 0) {
myStepper.step(256);
} else {
myStepper.step(-256);
}
}
}
void ow() {
}

void setup()
{
  Serial.begin(9600);

  //按鈕button
  //ON按鈕D4腳位
  pinPowerOn = 4;
  //OFF按鈕D5腳位
  pinPowerOff = 5;
  //是否按下關閉鈕
  isPowerOff = false;
  //
  //CO2
  //預熱時間120s
  preheatSec = 1;
  th = 0;
  tl = 0;
  co2 = 0;
  //★CO2高濃度標準
  HIGH_CO2 = 1000;
  //★CO2中濃度標準
  MID_CO2 = 850;
  //★CO2低濃度標準
  LOW_CO2 = 650;
  //
  //PM2.5
  pm25 = 0;
  //★PM2.5高濃度標準
  HIGH_PM25 = 1050;
  //★PM2.5中濃度標準
  MID_PM25 = 300;
  //★PM2.5低濃度標準
  LOW_PM25 = 150;
  //A0腳位
  dustPin = 0;
  dustVal = 0;
  ledPower = 2;
  delayTime = 280;
  delayTime2 = 40;
  offTime = 9680;
  //
  //步進馬達
  i = 0;
  //
  //溫度
  tem = 0;
  //★最高溫
  MAX_TEP = 30;
  //★最低溫
  MIN_TEP = 15;
  //馬達
  myStepper.setSpeed(12);
  openWindow(-1); //預設全關
  delay(1000);
  //
  //溫度
  dht11.begin();
  //補pinMode
  pinMode(pwmPin, INPUT);
  pinMode(dustPin, INPUT);
  pinMode(ledPower, OUTPUT);
  pinMode(pinPowerOn, INPUT);
  pinMode(pinPowerOff, INPUT);
}


void loop()
{
  //溫度
  tem = dht11.readTemperature();
  Serial.print("溫度：");
  Serial.println(tem);
  //
  //CO2
  do {
  th = pulseIn(pwmPin, HIGH, 1004000) / 1000;
  tl = 1004 - th;
  co2 = 2000 * (th - 2) / (th + tl - 4);
  } while (th == 0);
  if (preheatSec > 0) {
    Serial.print(preheatSec);
    Serial.print(",");
    preheatSec--;

  } else {
    Serial.print("CO2:");
    Serial.println(co2);

  }
  //
  //PM2.5
  digitalWrite(ledPower, LOW);
  delayMicroseconds(delayTime);
  dustVal = analogRead(dustPin);
  delayMicroseconds(delayTime2);
  digitalWrite(ledPower, HIGH);
  delayMicroseconds(offTime);
  delay(1000);
  if (dustVal > 36.455) {
    pm25 = (float(dustVal / 1024) - 0.0356) * 120000 * 0.035;
    Serial.print("PM2.5:");
    Serial.println(pm25);

  }
  delay(2000);
  //
  //按下ON按鈕
  if (digitalRead(pinPowerOn) == true) {
    Serial.println("按下ON按鈕");
    isPowerOff = false;
    openWindow(-1);//先全關

  }
  //按下OFF按鈕
  if (digitalRead(pinPowerOff) == true) {
    Serial.println("按下OFF按鈕");
    isPowerOff = true;
    openWindow(-1);//全關

  }
  //目前狀態(開機or關機)
  Serial.println("");
  if (isPowerOff) {
    Serial.println("========OFF 關機中========");

  } else {
    Serial.println("========ON 開機中========");

  }
  //自動化開關窗
  if (!isPowerOff) {
    if (tem >= MAX_TEP) {
      openWindow(1);
      Serial.println("氣溫高於MAX_TEP，全開");
      delay(1000);
      if (pm25 >= HIGH_PM25) {
        openWindow(-0.33);
        Serial.println("關閉1/3");

      } else if (pm25 < HIGH_PM25 && pm25 >= MID_PM25) {
        openWindow(-0.25);
        Serial.println("關閉1/4");
      } else if (pm25 < MID_PM25 && pm25 >= LOW_PM25) {
        openWindow(-0.17);
        Serial.println("關閉1/6");
      } else {
        Serial.println("PM2.5未達濃度，不做調整");

      }

    } else if (tem < MAX_TEP && tem > MIN_TEP) {
      openWindow(0.5);
      Serial.println("氣溫介於MAX_TEP與MIN_TEP，半開");
      delay(1000);
      if (pm25 >= HIGH_PM25) {
        openWindow(-0.33);
        Serial.println("關閉1/3");

      } else if (pm25 < HIGH_PM25 && pm25 >= MID_PM25) {
        openWindow(-0.25);
        Serial.println("關閉1/4");
      } else if (pm25 < MID_PM25 && pm25 >= LOW_PM25) {
        openWindow(-0.17);
        Serial.println("關閉1/6");
      } else {
        Serial.println("PM2.5未達濃度，不做調整");

      }
    } else if (tem <= MIN_TEP) {
      openWindow(-1);
      Serial.println("氣溫小於MIN_TEP，全關");
      delay(1000);
      if (co2 >= HIGH_CO2) {
        openWindow(0.25);
        Serial.println("打開1/4");

      } else if (co2 < HIGH_CO2 && co2 >= MID_CO2) {
        openWindow(0.17);
        Serial.println("打開1/6");
      } else if (co2 < MID_CO2 && co2 >= LOW_CO2) {
        openWindow(0.125);
        Serial.println("打開1/8");
      } else {
        Serial.println("CO2未達濃度，不做調整");

      }
    }

  }
}