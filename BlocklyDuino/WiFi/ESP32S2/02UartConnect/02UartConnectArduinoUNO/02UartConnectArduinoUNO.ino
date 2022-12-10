#include <SoftwareSerial.h>
SoftwareSerial ESP32Serial(3,2);

void setup() {
  Serial.begin(9600);
  ESP32Serial.begin(4800);
}

void loop() {
  while(ESP32Serial.available()){
    int val=ESP32Serial.parseInt();
    if(ESP32Serial.read()=='\n'){
      Serial.println(val);
    }
  }
}
