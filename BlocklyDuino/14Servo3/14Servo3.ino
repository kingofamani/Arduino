/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 05 Dec 2022 01:24:11 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include <Servo.h>

int ServoPin = 3;

Servo __myservoServoPin;
void servoGo(boolean isCW) {
  if (isCW == true) {
    __myservoServoPin.write(0);
    __myservoServoPin.attach(ServoPin)
    ;
  } else {
    __myservoServoPin.write(180);
    __myservoServoPin.attach(ServoPin)
    ;
  }
}

void servoStop() {
  __myservoServoPin.detach();
}

void setup()
{
  Serial.begin(9600);


  __myservoServoPin.attach(ServoPin);
}


void loop()
{
  if (Serial.available() == 1) {
    char key = Serial.read();
    if (key == '1') {
      //順時鐘
      servoGo(true);
    } else if (key == '2') {
      //逆時鐘
      servoGo(false);
    } else if (key == '3') {
      servoStop();
    }
  }
}