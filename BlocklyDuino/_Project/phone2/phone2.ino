/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Thu, 25 Mar 2021 10:17:48 GMT
 */

#include <Stepper.h>
#include <DHT.h>
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

int  j;

int button;

int steps=1024;
Stepper myStepper(steps, 3, 5, 4, 7 );
#ifdef __AVR__
#endif
#define PIN 6 // 腳位
#define DELAYVAL 500
#define NUMPIXELS 8 // 燈泡數
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
DHT dht11_p8(8, DHT11);
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

void motor() {
  for (j = 0; j <= 7; j++) {
    myStepper.step(256);
  }
}

void setup()
{
  Serial.begin(9600);

  myStepper.setSpeed(15);
  pixels.clear();
  WS1();
  dht11_p8.begin();
  pinMode(9, INPUT);
}


void loop()
{
  button = digitalRead(9);
  if (button == 1) {
    //單色向上跑馬燈
    theaterChase(pixels.Color(160,32,240), 350);
    delay(2000);
    motor();

  } else {
    pixels.clear();

  }
  Serial.println(button);
  delay(100);
  Serial.println(dht11_p8.readTemperature());
}