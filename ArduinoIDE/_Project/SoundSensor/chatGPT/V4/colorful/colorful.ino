#include <FastLED.h>
#include <Keyboard.h>

#define LED_PIN     6
#define NUM_LEDS    8
#define SENSOR_PIN  A0

CRGB leds[NUM_LEDS];

int minSound = 300;
int maxSound = 600;
int counter = 0;
bool notepadOpened = false;

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(255);
  pinMode(SENSOR_PIN, INPUT);
  Serial.begin(9600);
  Keyboard.begin();
}

CRGB gradientBetween(CRGB color1, CRGB color2, uint8_t ratio) {
  return color1.lerp8(color2, ratio);
}

void loop() {
  int soundValue = analogRead(SENSOR_PIN);
  soundValue = constrain(soundValue, minSound, maxSound);
  Serial.println(soundValue);

  int mappedValue = map(soundValue, minSound, maxSound, 0, NUM_LEDS);

  for (int i = 0; i < NUM_LEDS; i++) {
    if (i < mappedValue) {
      uint8_t gradient = (i * 255) / (NUM_LEDS - 1);
      leds[i] = gradientBetween(CRGB::Green, CRGB::Red, gradient);
    } else {
      leds[i] = CRGB::Black;
    }
  }

  FastLED.show();

  if (soundValue == maxSound) {
    counter++;

    if (!notepadOpened) {
      notepadOpened = true;
      Keyboard.press(KEY_LEFT_GUI);
      delay(100);
      Keyboard.press('r');
      delay(100);
      Keyboard.releaseAll();
      delay(500);
      Keyboard.print("notepad.exe");
      delay(100);
      Keyboard.press(KEY_RETURN);
      delay(100);
      Keyboard.releaseAll();
      delay(500);
    }

    Keyboard.print("stop talking ");
    Keyboard.print(counter);
    Keyboard.press(KEY_RETURN);
    delay(100);
    Keyboard.releaseAll();
    delay(500);
  }
}
