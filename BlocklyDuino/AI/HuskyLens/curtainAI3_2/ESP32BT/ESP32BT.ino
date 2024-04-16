#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);//連接ESP32S2
  SerialBT.begin("ESP32-2292"); //藍牙裝置名稱
  Serial.println("藍牙已成功建立，請開啟手機搜尋藍牙裝置：ESP32-2292!");
  //通知ESP32S2已成功連線藍牙
  Serial2.print("t");
}

void loop() {
  if (Serial.available()) {
    Serial2.write(Serial.read());
  }
  //不用能，只能Serial2、BluetoothSerial二選一
//  if (Serial2.available()) {
//    Serial.write(Serial2.read());
//  }
  if (SerialBT.available()) {
    String btMsg = (SerialBT.readString());
    Serial.print(btMsg);
    Serial2.print(btMsg);
  }
  delay(20);
}
