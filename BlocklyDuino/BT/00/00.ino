//Generated Date: Mon, 18 Sep 2023 01:39:24 GMT

#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
  #error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial SerialBT;

void setup()
{
  Serial.begin(9600);
  delay(10);
  SerialBT.begin("ESP32test");
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
    Serial.println((BluetoothData));
  }
}
