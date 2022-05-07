#include <DFRobot_DF1201S.h>
#include <SoftwareSerial.h>

SoftwareSerial DF1201SSerial(2, 3);  //RX  TX

DFRobot_DF1201S DF1201S;

void setup(void) {
  Serial.begin(115200);
  DF1201SSerial.begin(115200);
  while (!DF1201S.begin(DF1201SSerial)) {
    Serial.println("Init failed, please check the wire connection!");
    delay(1000);
  }
  /*max val 30*/
  DF1201S.setVol(15);
  DF1201S.switchFunction(DF1201S.MUSIC);
  delay(100);
}

void loop() {  
  DF1201S.start();

  DF1201S.playSpecFile("/01/1.mp3");
  delay(2000);
  DF1201S.playSpecFile("/01/5.mp3");
  delay(2000);
  //while (1);

}
