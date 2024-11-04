#include <SoftwareSerial.h>
SoftwareSerial UnoSerial(4,5);

void setup() {
  Serial.begin(9600);
  UnoSerial.begin(9600);
}

void loop() {
  //傳送訊息：ESP32→UNO
  if(Serial.available()){
    String msg=Serial.readString();
    UnoSerial.print(msg);
  }

  //接收訊息：UNO→ESP32
  while(UnoSerial.available()){
    String val=UnoSerial.readString();
    Serial.println(val);    
  }
}
