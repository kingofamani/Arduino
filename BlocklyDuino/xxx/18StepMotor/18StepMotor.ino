/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 18 Jan 2021 06:06:25 GMT
 */

#include <Stepper.h>

int  i;

int steps=2048;
Stepper myStepper(steps, 8, 10, 9, 11);

void setup()
{
  Serial.begin(9600);

  myStepper.setSpeed(12);
}


void loop()
{
  /*
  ★接腳依序8,9,10,11，但程式要寫成8,10,9,11
*/

/*
    轉1圈(0-7共8次，8*256=2048)
  */
  /*
    若要轉2圈則迴圈改成0-15
  */
  for (i = 0; i <= 7; i++) {
    myStepper.step(256);
  }
  delay(1000);
}