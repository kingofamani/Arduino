#include <Mouse.h>

const int buttonPin = 2;
const int screenWidth = 1024; // 請根據您的螢幕尺寸修改
const int screenHeight = 768; // 請根據您的螢幕尺寸修改
int moveWidth =screenWidth/100;
int moveHeight =screenHeight/100;

unsigned long previousMillis = 0;
const long interval = 1000;
int step = 0;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  Mouse.begin();
}

void loop() {
  int buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);
  if (buttonState == LOW) {
    moveToTopLeft();
    delay(1000);
    moveToBottomRight();
    delay(1000);
    moveToCenter();
    delay(3000);
  }
}

void moveToTopLeft() {
  for (int i = 0; i < 100; i++) {
    Mouse.move(-moveWidth, -moveHeight);
    delay(20);
  }
}

void moveToBottomRight() {
  for (int i = 0; i < 100; i++) {
    Mouse.move(moveWidth, moveHeight);
    delay(20);
  }
}

void moveToCenter() {
  for (int i = 0; i < 50; i++) {
    Mouse.move(-moveWidth, -moveHeight);
    delay(20);
  }
}
