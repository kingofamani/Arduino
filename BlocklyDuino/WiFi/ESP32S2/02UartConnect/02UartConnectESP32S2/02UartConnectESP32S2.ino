#include <SoftwareSerial.h>
SoftwareSerial UnoSerial(2,3);

void setup() {
  Serial.begin(9600);
  UnoSerial.begin(4800);
  pinMode(2,INPUT);
  pinMode(3,OUTPUT);
}

void loop() {
  UnoSerial.print("10");
  UnoSerial.println("\n");
  delay(100);
}
