#include <Wire.h>

volatile int item,x,qz;
volatile boolean f1,f2,f3;

void setup(){
  Wire.begin();
  item = 0;
  x = 0;
  f1 = 1;
  f2 = 1;
  f3 = 1;
  qz = 0;
  Serial.begin(9600);
}

void loop(){
  Wire.beginTransmission(0x27);
    Wire.write(2);
    Wire.write(1);
    Wire.write(3);
    Wire.write(4);
  Wire.endTransmission();
  Wire.requestFrom(0x27, 2);
  while (Wire.available()) {
    item = Wire.read();
    x = x + 1;
    if ((long) (x) % (long) (2) == 1) {
        qz = item;
    }
    if (x == 2) {//处理、并打印第一个输入的按键
        if (item == 1 && f1 == 1) {
            f1 = 0;
            f2 = 1;
            f3 = 0;
            Serial.print(qz,DEC);
        }
    }
    if (x == 4) {//处理、并打印第一个输入的按键
        if (item == 2 && f2 == 1) {
            f2 = 0;
            f1 = 0;
            f3 = 1;
            Serial.print(qz,DEC);
        }
    }
    if (x == 6) {//处理、并打印第一个输入的按键
        if (item == 3 && f3 == 1) {
            f1 = 1;
            f2 = 0;
            f3 = 0;
            if (qz == 18) {
                Serial.println("Wrong");
            }
            if (qz == 17) {
                Serial.println("OK");
            }
        }
      x = 0;
    }
  }
  delay(100);
}
