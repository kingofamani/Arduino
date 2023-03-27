#include <Adafruit_NeoPixel.h>

#define PIN_LED 5
#define NUM_LED 8

#define PIN_MIC A0

Adafruit_NeoPixel leds(NUM_LED, PIN_LED, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  leds.begin();
  leds.setBrightness(50);
}

void loop() {
  int soundValue = analogRead(PIN_MIC);
  int numLedsOn = map(soundValue, 400, 800, 0, NUM_LED);

  for(int i = 0; i < NUM_LED; i++) {
    if(i < numLedsOn) {
      leds.setPixelColor(i, 255, 255, 255);
    } else {
      leds.setPixelColor(i, 0, 0, 0);
    }
  }

  leds.show();

  Serial.println(soundValue);

  delay(10);
}
