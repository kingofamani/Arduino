#include <Wire.h>

volatile int item;

void setup(){
  Wire.begin();
  item = 0;
  Serial.begin(9600);
}
/*读取单个键值*/
void loop(){
  Wire.beginTransmission(0x27);
    Wire.write(3);
  Wire.endTransmission();
  Wire.requestFrom(0x27, 1);
  while (Wire.available()) {
    item = Wire.read();
    Serial.println(item,DEC);
  }
  delay(100);

}
