#include <SoftwareSerial.h>
SoftwareSerial UnoSerial(2,3);

void setup() {
  Serial.begin(9600);
  UnoSerial.begin(9600);
//  pinMode(2,INPUT);
//  pinMode(3,OUTPUT);
}

void loop() {
  //用write，不要用print
  //不要傳中文字
  UnoSerial.write("UNO test");
  delay(1000);
}
