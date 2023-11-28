#include <SoftwareSerial.h>
SoftwareSerial ESP32Serial(19,18);

void setup() {
  Serial.begin(9600);
  ESP32Serial.begin(9600);
}

void loop() {
  //傳送訊息：UNO→ESP32
  if(Serial.available()){
    String str=Serial.readString();
    ESP32Serial.print(str);
  }//用print

  
//  if(Serial.available()){
//    String str=Serial.readString();
//    char c[99];
//    str.toCharArray(c, sizeof(c));
//    ESP32Serial.write(c);
//  }//用write

  //接收訊息：ESP32→UNO
  while(ESP32Serial.available()){
    String val=ESP32Serial.readString();
    Serial.println(val);    
  }
}
