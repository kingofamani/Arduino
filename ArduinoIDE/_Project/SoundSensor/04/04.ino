#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN        13// LED燈數位腳位

#define NUMPIXELS 24 // LED燈泡數

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int sounds ;//音量
int nums;//亮燈數
int MinSound = 500; //最低音量，必須介於0~1023
int MaxSound = 800; //最高音量，必須介於0~1023



void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif



  Serial.begin(9600);
  pixels.begin();


}

void loop() {
  light(setNums());//依音量顯示LED燈數(1~NUMPIXELS間)
  Serial.println(sounds);
  Serial.println(nums);
  Serial.println("");
  delay(10);//聽音樂可改成10
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
  uint32_t colors[NUMPIXELS];
  setColor(colors);//設定彩虹色

  pixels.clear();
  for (int i = 0; i < nums; i++) {
    pixels.setPixelColor(i, colors[i]);
    pixels.show();
  }
}

void setColor(uint32_t *colors) {
  uint32_t green = pixels.Color(0, 255, 0);
  uint32_t yellow = pixels.Color(255, 255, 0);
  uint32_t red = pixels.Color(255, 0, 0);
  uint32_t purple = pixels.Color(128, 0, 128);

  int otherColorNums = NUMPIXELS - 4;//上述4顏色以外的顏色數量
  int greenRangeNums = otherColorNums * 0.33 + 0.5; //綠色區間數量佔33.3%(加0.5是四捨五入)
  int yellowRangeNums = otherColorNums * 0.5 + 0.5; //綠色區間數量佔50%
  int redRangeNums = otherColorNums * 0.17 + 0.5; //綠色區間數量佔16.6%

  //開始設定彩虹色系
  colors[0] = green;
  int r = 255 / (greenRangeNums + 1); //變化顏色間距
  for (int i = 0; i < greenRangeNums; i++) {
    colors[1 + i] = pixels.Color(r * (i + 1), 255, 0);
  }

  colors[1 + greenRangeNums] = yellow;
  int g = 255 / (yellowRangeNums + 1);
  for (int j = 0; j < yellowRangeNums; j++) {
    colors[2 + greenRangeNums + j] = pixels.Color(255, g * (j + 1), 0);
  }

  colors[1 + 1 + greenRangeNums + yellowRangeNums] = red;
  int r2 = (255 - 128) / (redRangeNums + 1);
  int b = (128 - 0) / (redRangeNums + 1);
  for (int k = 0; k < redRangeNums; k++) {
    colors[3 + greenRangeNums + yellowRangeNums + k] = pixels.Color(255 - r2 * (k + 1), 0, b * (k + 1));
  }

  colors[NUMPIXELS - 1] = purple;

  //  colors[0] =    pixels.Color(0, 255, 0);//
  //  colors[1] =    pixels.Color(128, 255, 0);
  //  colors[2] =    pixels.Color(255, 255, 0);//
  //  colors[3] =    pixels.Color(255, 192 , 0);
  //  colors[4] =    pixels.Color(255, 64 , 0);
  //  colors[5] =    pixels.Color(255, 0, 0);//
  //  colors[6] =    pixels.Color(192, 0, 64);
  //  colors[7] =    pixels.Color(128, 0, 128);//

  //   colors = {
  //    pixels.Color(0, 255, 0),
  //    pixels.Color(128, 255, 0),
  //    pixels.Color(255, 255, 0),
  //    pixels.Color(255, 192 , 0),
  //    pixels.Color(255, 64 , 0),
  //    pixels.Color(255, 0, 0),
  //    pixels.Color(192, 0, 64),
  //    pixels.Color(128, 0, 128)
  //  };
}
