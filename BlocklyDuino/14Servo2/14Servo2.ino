/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 11 Oct 2021 05:33:23 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include <Servo.h>

int A = 3;

Servo __myservoA;

void setup()
{
  __myservoA.attach(A);
  __myservoA.write(0);
  delay(1000);
}


void loop()
{
  __myservoA.write(45);
  delay(1000);
  __myservoA.write(90);
  delay(1000);
}