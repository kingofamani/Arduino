#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN        13// LED燈數位腳位

#define NUMPIXELS 8 // LED燈泡數

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int sounds ;//音量
int nums;//亮燈數
int MinSound = 500; //最低音量，必須介於0~1023
int MaxSound = 600; //最高音量，必須介於0~1023

uint32_t colors[8] = {
  pixels.Color(0, 255, 0),
  pixels.Color(128, 255, 0),
  pixels.Color(255, 255, 0),
  pixels.Color(255, 192 , 0),
  pixels.Color(255, 64 , 0),
  pixels.Color(255, 0, 0),
  pixels.Color(192, 0, 64),
  pixels.Color(128, 0, 128)
};

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  Serial.begin(9600);
  pixels.begin();
}

void loop() {
  light(setNums());//依音量顯示LED燈數
  Serial.println(sounds);
  Serial.println(nums);
  Serial.println("");
  delay(100);//聽音樂可改成10
}

int setNums() {
  sounds =  analogRead(A0);
  if (sounds > MaxSound) {
    sounds = MaxSound;
  }
  if (sounds < MinSound) {
    sounds = MinSound;
  }
  nums = ((NUMPIXELS - 1) * (sounds - MinSound) / (MaxSound - MinSound)) + 1;
  return nums;
}

void light(int nums) {
  pixels.clear();
  for (int i = 0; i < nums; i++) {
    pixels.setPixelColor(i, colors[i]);
    pixels.show();
  }
}
