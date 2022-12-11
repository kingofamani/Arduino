#include <SoftwareSerial.h>
SoftwareSerial ESP32Serial(3, 2);
SoftwareSerial ESP32Serial2(5, 4);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }

  ESP32Serial.begin(9600);
  ESP32Serial2.begin(9600);
}

void loop() {
  //傳送訊息：UNO→ESP32
  if (Serial.available()) {
    String str = Serial.readString();
    ESP32Serial.print(str);
    //    delay(1000);
    ESP32Serial2.print(str);
  }//用print


  //  if(Serial.available()){
  //    String str=Serial.readString();
  //    char c[99];
  //    str.toCharArray(c, sizeof(c));
  //    ESP32Serial.write(c);
  //  }//用write

  //接收訊息：ESP32→UNO
  ESP32Serial.listen();
  delay(2);
  //Serial.print("");
  while (ESP32Serial.available()) {
    char inByte = ESP32Serial.read();
    Serial.write(inByte);
    delay(1);
    //    String val=ESP32Serial.readString();
    //    Serial.println(val);
    //delay(10);
  }

  //  Serial.println();

//  ESP32Serial2.listen();
//  delay(2);
//  while (ESP32Serial2.available()) {
//    delay(1);
//    String val = ESP32Serial2.readString();
//    Serial.println(val);
//    delay(10);
//  }


  //  Serial.println();
}
