/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 28 Sep 2020 03:22:53 GMT
 */

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(7, 8);
DFRobotDFPlayerMini myDFPlayer;

void setup()
{
  Serial.begin(115200);

  mySoftwareSerial.begin(9600);
  if (!(myDFPlayer.begin(mySoftwareSerial))) {
    while (true) {
    }

  }
  myDFPlayer.volume(10);
  myDFPlayer.play(1);
}


void loop()
{
  delay(3000);
  myDFPlayer.next();
}