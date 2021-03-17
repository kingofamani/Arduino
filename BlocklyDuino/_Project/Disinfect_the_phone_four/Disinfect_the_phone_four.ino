/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Wed, 17 Mar 2021 01:57:18 GMT
 */

#include <Stepper.h>
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>
#include <SPI.h>
#include <RFID.h>

int  j;

int button;

String myId;

int  i;

int steps=2048;
Stepper myStepper(steps, 3, 5, 4, 7 );
#ifdef __AVR__
#endif
#define PIN 6 // 腳位
#define DELAYVAL 500
#define NUMPIXELS 8 // 燈泡數
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
void WS0() {
}

void WS1() {
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif
   pixels.begin();
}

void colorWipe(uint32_t color, int wait) {
for (int i = 0; i < pixels.numPixels(); i++) {
pixels.setPixelColor(i, color);
pixels.show();
delay(wait);
}
}
void a1() {
}

void rainbow(int wait) {
for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
for (int i = 0; i < pixels.numPixels(); i++) {
int pixelHue = firstPixelHue + (i * 65536L / pixels.numPixels());
pixels.setPixelColor(i, pixels.gamma32(pixels.ColorHSV(pixelHue)));
}
 pixels.show();
 delay(wait);
 }
 }
void a3() {
}

void theaterChase(uint32_t color, int wait) {
for (int a = 0; a < 10; a++) {
for (int b = 0; b < 3; b++) {
pixels.clear();
for (int c = b; c < pixels.numPixels(); c += 3) {
pixels.setPixelColor(c, color);
}
pixels.show();
delay(wait);
}
}
}
void a2() {
}

#define SDA_DIO 9
#define RESET_DIO 8
RFID RC522(SDA_DIO, RESET_DIO);
void R0() {
  myId = "";
}

void motor() {
  for (j = 0; j <= 12; j++) {
    myStepper.step(256);
  }
}

void setup()
{
  Serial.begin(9600);

  myStepper.setSpeed(12);
  SPI.begin();
  RC522.init();
  pixels.clear();
  WS1();
  pinMode(21, INPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
}


void loop()
{
  button = digitalRead(21);
  if (RC522.isCard())
  {
  myId = "";
  RC522.readCardSerial();
  for (i = 0; i <= 4; i++) {
    myId += String(RC522.serNum[i]);
  }
  //從這裡開始改程式：
  Serial.println(myId);
  if (myId == "1217321417985" || (myId == "22761511208" || myId == "106121243111143")) {
    digitalWrite(14, HIGH);
    digitalWrite(15, LOW);

  } else {
    digitalWrite(14, LOW);
    digitalWrite(15, HIGH);

  }
  }//end if
  if (button == 1) {
    //單色向上跑馬燈
    theaterChase(pixels.Color(160,32,240), 400);
    delay(2000);
    motor();

  } else {
    pixels.clear();

  }
  Serial.println(button);
  delay(100);
}