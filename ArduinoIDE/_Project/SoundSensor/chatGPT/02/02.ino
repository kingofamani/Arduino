#include <Adafruit_NeoPixel.h>

#define PIN_LED 6   // LED燈接腳
#define PIN_SOUND A0 // 聲音傳感器接腳

#define NUM_LEDS 8 // LED燈數量

Adafruit_NeoPixel leds = Adafruit_NeoPixel(NUM_LEDS, PIN_LED, NEO_GRB + NEO_KHZ800);

int soundValue = 0; // 聲音傳感器數值
int ledCount = 0;   // 亮燈數量

void setup() {
  Serial.begin(9600);
  leds.begin();
  leds.setBrightness(5); // 初始化亮度
}

void loop() {
  soundValue = analogRead(PIN_SOUND);
  Serial.println(soundValue);
  
  // 聲音傳感器數值最小400時，亮0顆LED燈；最大800時，亮8顆LED燈
  ledCount = map(soundValue, 400, 800, 0, 8);

  for (int i = 0; i < NUM_LEDS; i++) {
    if (i < ledCount) {
      // 將LED燈顏色設為彩虹色
      int r = 255 * (NUM_LEDS - i) / NUM_LEDS;
      int g = 255 * i / NUM_LEDS;
      int b = 0;
      leds.setPixelColor(i, r, g, b);
    } else {
      leds.setPixelColor(i, 0, 0, 0); // LED燈熄滅
    }
  }
  leds.show(); // 更新LED燈顯示
  delay(10); // 延遲10毫秒
}
