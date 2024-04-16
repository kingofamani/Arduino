#include <SPI.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#define pwmPin 3          //接D3
int preheatSec = 6;      //預熱時間120s

unsigned long th, tl, ppm2, ppm3 = 0;

void setup() {
  Serial.begin(9600);
  pinMode(pwmPin, INPUT);
}

void loop() {
  //CO2 via pwm
  do {
    th = pulseIn(pwmPin, HIGH, 1004000) / 1000;
    tl = 1004 - th;
    ppm2 = 2000 * (th - 2) / (th + tl - 4);
    //ppm3 = 5000 * (th - 2) / (th + tl - 4);
  } while (th == 0);
  if (preheatSec > 0) {
    //Serial.print("Preheating");
    Serial.print(preheatSec);
    Serial.print(",");
    preheatSec--;
  }
  else {
    //Serial.println(th);
    Serial.println(ppm2);   //PWM (0-2000PPM)
    //Serial.println(ppm3);   //PWM (0-5000PPM)
    //Serial.println("-----------");
  }

  delay(1000);
}
