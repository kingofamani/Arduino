/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Wed, 26 Oct 2022 06:28:26 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include <Stepper.h>

int steps=2048;
Stepper myStepper(steps, 8, 10, 9, 11);
void go(float c,Stepper stepper) {
  /*
    轉1圈(num為0-7)
  */
  /*
    若要轉2圈則num改成0-15
  */
  int num = ((abs(c)) * 8) - 1;
  for (int i = 0; i <= num; i++) {
    if (c >= 0) {
      stepper.step(256);
    } else {
      stepper.step(-256);
    }
  }
  delay(1000);
}

void setup()
{
  myStepper.setSpeed(12);
}


void loop()
{
  /*
    可輸入圈數(倒數要輸入負值)
  */
  go(1,myStepper);
  go(-1,myStepper);
}