/*
   Generated using BlocklyDuino:

   https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt

   Date: Mon, 18 Jan 2021 06:06:25 GMT
*/

#include <Stepper.h>

int  i;

int steps = 2048;
Stepper myStepper(steps, 8, 10, 9, 11);

void setup()
{
  Serial.begin(9600);

  myStepper.setSpeed(12);
}


void loop()
{
  openWindow(0.75);
  delay(3000);
  openWindow(-0.75);
  delay(3000);
}

void openWindow(float circle) {
  int steps = abs(circle) * 9 - 1;
  for (i = 0; i <= abs(steps); i++) {
    if (circle >= 0) {
      myStepper.step(256);
    } else {
      myStepper.step(-256);
    }
  }  
}
