
#include <Wire.h>

volatile int item;

void setup(){
  Wire.begin();
  item = 0;
}
/*i2c发送2，输入密码*/
void loop(){
  Wire.beginTransmission(0x27);
    Wire.write(2);
  Wire.endTransmission();
  Wire.requestFrom(0x27, 2);
  while (Wire.available()) {
    item = Wire.read();
  }
  delay(100);

}
