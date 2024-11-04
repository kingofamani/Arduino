//Generated Date: Mon, 18 Sep 2023 07:38:00 GMT

#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
  #error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial SerialBT;

byte m1aL9110=16;
byte m1bL9110=17;
byte m2aL9110=21;
byte m2bL9110=22;
byte m1bCH=13;
byte m2bCH=14;

void forward() {
  digitalWrite(m1aL9110,1);
  ledcWrite(m1bCH,255-255);
  digitalWrite(m2aL9110,1);
  ledcWrite(m2bCH,255-255);
}

void backward() {
  digitalWrite(m1aL9110,0);
  ledcWrite(m1bCH,255);
  digitalWrite(m2aL9110,0);
  ledcWrite(m2bCH,255);
}

void turnRight() {
  digitalWrite(m1aL9110,1);
  ledcWrite(m1bCH,255-255);
  digitalWrite(m2aL9110,1);
  ledcWrite(m2bCH,255);
}

void turnLeft() {
  digitalWrite(m2aL9110,1);
  ledcWrite(m2bCH,255-255);
  digitalWrite(m1aL9110,1);
  ledcWrite(m1bCH,255);
}

void stopCar() {
  //★若不設定秒數會永遠stopCar。約每100毫秒手機會傳送訊號過來一次，所以設定200較適合。
  delay(200);
  digitalWrite(m1aL9110,1);
  ledcWrite(m1bCH,255);
  digitalWrite(m2aL9110,1);
  ledcWrite(m2bCH,255);
}

void setup()
{
  pinMode(m1aL9110,OUTPUT);
  pinMode(m2aL9110,OUTPUT);
  ledcSetup(m1bCH, 5000, 8);
  ledcAttachPin(m1bL9110,m1bCH);
  ledcSetup(m2bCH, 5000, 8);
  ledcAttachPin(m2bL9110,m2bCH);
  digitalWrite(m1aL9110,1);
  ledcWrite(m1bCH,255);
  digitalWrite(m2aL9110,1);
  ledcWrite(m2bCH,255);

  Serial.begin(9600);
  delay(10);
  SerialBT.begin("ESP32test2");
  delay(10);


}

void loop()
{
  if (SerialBT.available()) {
    String BluetoothData = "";
    while (SerialBT.available()) {
      char c=SerialBT.read();
      BluetoothData=BluetoothData+String(c);
      delay(1);
    }
    Serial.print((BluetoothData));
    if ((BluetoothData) == "f") {
      forward();
      stopCar();
    } else if ((BluetoothData) == "b") {
      backward();
      stopCar();
    } else if ((BluetoothData) == "l") {
      turnLeft();
      stopCar();
    } else if ((BluetoothData) == "r") {
      turnRight();
      stopCar();
    }
  }
}
