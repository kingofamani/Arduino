//Generated Date: Wed, 20 Sep 2023 01:23:10 GMT

#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>

byte m1aL9110=16;
byte m1bL9110=17;
byte m2aL9110=21;
byte m2bL9110=22;
byte m1bCH=13;
byte m2bCH=14;

void forward() {
  digitalWrite(m1aL9110,1);
  ledcWrite(m1bCH,255-255);
  digitalWrite(m2aL9110,1);
  ledcWrite(m2bCH,255-255);
}

void backward() {
  digitalWrite(m1aL9110,0);
  ledcWrite(m1bCH,255);
  digitalWrite(m2aL9110,0);
  ledcWrite(m2bCH,255);
}

void turnRight() {
  digitalWrite(m1aL9110,1);
  ledcWrite(m1bCH,255-255);
  digitalWrite(m2aL9110,1);
  ledcWrite(m2bCH,255);
}

void turnLeft() {
  digitalWrite(m2aL9110,1);
  ledcWrite(m2bCH,255-255);
  digitalWrite(m1aL9110,1);
  ledcWrite(m1bCH,255);
}

void stopCar() {
  digitalWrite(m1aL9110,1);
  ledcWrite(m1bCH,255);
  digitalWrite(m2aL9110,1);
  ledcWrite(m2bCH,255);
}

void setup()
{
  pinMode(m1aL9110,OUTPUT);
  pinMode(m2aL9110,OUTPUT);
  ledcSetup(m1bCH, 5000, 8);
  ledcAttachPin(m1bL9110,m1bCH);
  ledcSetup(m2bCH, 5000, 8);
  ledcAttachPin(m2bL9110,m2bCH);
  digitalWrite(m1aL9110,1);
  ledcWrite(m1bCH,255);
  digitalWrite(m2aL9110,1);
  ledcWrite(m2bCH,255);

  Dabble.begin("CarDabble");


}

void loop()
{
  Dabble.processInput();
  if ((GamePad.getJoystickData(3)) >= 3) {
    forward();
  } else if ((GamePad.getJoystickData(3)) <= -3) {
    backward();
  } else if ((GamePad.getJoystickData(2)) <= -3) {
    turnLeft();
  } else if ((GamePad.getJoystickData(2)) >= 3) {
    turnRight();
  } else if (GamePad.isCrossPressed()) {
    stopCar();
  }
}
