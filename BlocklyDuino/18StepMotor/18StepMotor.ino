/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Thu, 29 Oct 2020 07:19:19 GMT
 */

#include <Stepper.h>

int  i;

int steps=2048;
Stepper myStepper(steps, 8, 10, 9, 11);

void setup()
{
  Serial.begin(9600);

  myStepper.setSpeed(13);
}


void loop()
{
  myStepper.step(steps);
  //for (i = 0; i <= 100; i++) {
    //myStepper.step(steps);
  //}
  //delay(500);
  //myStepper.step(-steps);
  //delay(500);
}
