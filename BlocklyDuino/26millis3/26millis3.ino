/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Sat, 19 Nov 2022 02:58:11 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include <SimpleTimer.h>

SimpleTimer timer;
int secs = 5;

boolean isTimeOut = false;

void countDown(int secs) {
  timer.setTimer(1000, printSec, secs+1);
}

void printSec() {
  static int k = 0;
  k++;
  Serial.println((String(secs-k+1)+String("秒")));
  if ((k) == secs + 1) {
    k = 0;
    isTimeOut = true;
  }
}

void setup()
{
  Serial.begin(9600);


}


void loop()
{
  timer.run();
  //開始計時
  countDown(secs);
  //結束計時
  if (isTimeOut) {
    Serial.println("結束");
    isTimeOut = false;
  }
}