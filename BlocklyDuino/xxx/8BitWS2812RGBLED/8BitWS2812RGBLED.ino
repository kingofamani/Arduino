/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 28 Dec 2020 14:05:52 GMT
 */

#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

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

void setup()
{
  WS1();
}


void loop()
{
  //預設腳位D6

pixels.clear();
  //單色8顆燈依序亮
  colorWipe(pixels.Color(160, 32, 240), 50);
  //單色向上跑馬燈
  //theaterChase(pixels.Color(160,32,240), 50);
  //彩虹向下跑馬燈
  //  rainbow(10);
}