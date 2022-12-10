#include <SoftwareSerial.h>
SoftwareSerial ESP32Serial(3,2);

void setup() {
  Serial.begin(9600);
  ESP32Serial.begin(9600);
}

void loop() {
  while(ESP32Serial.available()){
    String val=ESP32Serial.readString();
    Serial.println(val);    
  }
}
