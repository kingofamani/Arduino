#include <SoftwareSerial.h>
SoftwareSerial Esp32GpsSerial(2,3);

void setup() {
  Serial.begin(9600);
  Esp32GpsSerial.begin(9600);
//  pinMode(2,INPUT);
//  pinMode(3,OUTPUT);
}

void loop() {
  //用write，不要用print
  //不要傳中文字
  Esp32GpsSerial.write("UNO test");
  delay(1000);
}
