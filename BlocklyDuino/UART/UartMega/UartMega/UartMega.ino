//#include <SoftwareSerial.h>
//SoftwareSerial ESP32Serial(19,18);

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  //傳送訊息：UNO→ESP32
  if(Serial.available()){
    String str=Serial.readString();
    Serial1.print(str);
  }//用print

  


  //接收訊息：ESP32→UNO
  while(Serial1.available()){
    String val=Serial1.readString();
    Serial.println(val);    
  }
//  while(ESP32Serial.available()){
//    String val=ESP32Serial.readString();
//    Serial.println(val);    
//  }
}
