#include <Wire.h>

volatile int code;

void setup(){
  Wire.begin();
  code = 0;
  Serial.begin(9600);
}
/*读取单个键值*/
void loop(){
  Wire.beginTransmission(0x27);
    Wire.write(3);
  Wire.endTransmission();
  Wire.requestFrom(0x27, 1);
  while (Wire.available()) {
    code = Wire.read();
    if(code != 16){//沒按按鈕傳回16
      Serial.println(code,DEC);
    }    
  }
  delay(100);
}
