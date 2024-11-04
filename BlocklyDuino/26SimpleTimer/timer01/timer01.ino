//Generated Date: Mon, 15 Apr 2024 04:18:01 GMT

#include <SimpleTimer.h>
SimpleTimer timer;

int inteval_ID1 = 0;

void setup()
{
  Serial.begin(9600);

  timer.setInterval(5000, timerFunc0);

  inteval_ID1 = timer.setInterval(1000, intevalFunc1);
timer.disable(inteval_ID1);

  timer.setTimeout(10000, timeoutFunc2);
  timer.setTimer(300, setTimerFunc3, 5);

  pinMode(5, INPUT);
}

void loop()
{
  timer.run();  //當按下按鈕，才開始計時
  if (digitalRead(5) == false) {
    timer.enable(inteval_ID1);
  } else {
    timer.disable(inteval_ID1);
  }
}

void timerFunc0(){
   Serial.println("第一種：每5秒執行1次");
  }


void intevalFunc1(){
   Serial.println("第二種：[按下按鈕] 開始計時了...");
  }


void timeoutFunc2(){
   Serial.println("第三種：10秒後執行，只執行1次");
  }


void setTimerFunc3(){
   Serial.println("第四種：每300毫秒執行1次，總共5次");
  }
