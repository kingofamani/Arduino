/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 11 Oct 2021 06:04:48 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include <Stepper.h>

int steps=2048;
Stepper myStepper(steps, 8, 10, 9, 11);
void go(float c) {
  /*
    轉1圈(num為0-7)
  */
  /*
    若要轉2圈則num改成0-15
  */
  int num = (c * 8) - 1;
  for (int i = 0; i <= num; i++) {
    myStepper.step(256);
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
    可輸入圈數
  */
  go(1);
}