/*
 * 【求紅外線感應器的平均距離】
 * 
 * 解決測距數據有時會忽然增大的問題
*/
#include <Ultrasonic.h>
#include <ArduinoSort.h>


int distance;
Ultrasonic ultrasonic(5, 6);

void setup() {
  Serial.begin(9600); 
}


void loop() {
  distance = avgDistance();
  Serial.println(distance);    
}//loop end

int avgDistance() {
  int avg = 0;
  int dists[13];
  int distSum=0;

  for (int i = 0; i < 13; i++) {
    dists[i] = ultrasonic.read();
    distSum += dists[i];
    delay(10);
  }

  sortArray(dists,13);
  avg = (distSum-dists[10]-dists[11]-dists[12])/10;

  return avg;
}
