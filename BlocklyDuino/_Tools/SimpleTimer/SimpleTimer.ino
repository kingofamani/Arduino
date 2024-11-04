/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 28 Sep 2020 13:44:02 GMT
 */

#include <SimpleTimer.h>

SimpleTimer timer;
void RepeatTask() {
  Serial.println("每隔n秒執行1次");
}

void OnceOnlyTask() {
  Serial.println("只執行1次，執行完畢");
}

void TimesTask() {
  static int k = 0;
  k++;
  Serial.print("第");
  Serial.print(k);
  Serial.println("次");
}

void DigitalClockDisplay() {
  int h,m,s;
  s = millis() / 1000;
  m = s / 60;
  h = s / 3600;
  s = s - m * 60;
  m = m - h * 60;
  Serial.print(h);
  printDigits(m);
  printDigits(s);
  Serial.println("");
}

void printDigits(int digits) {
Serial.print(":");
if(digits < 10){
Serial.print("0");
}
Serial.print(digits);
}

void setup()
{
  Serial.begin(9600);

  timer.setInterval(15000, RepeatTask);//每隔15秒觸發1次
  timer.setTimeout(10000, OnceOnlyTask);//10秒後觸發1次，只有1次
  timer.setInterval(1000, DigitalClockDisplay);//時鐘
  timer.setTimer(300, TimesTask, 10);//每隔0.3秒觸發1次，共有10次
}


void loop()
{
  timer.run();
}