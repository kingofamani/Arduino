#include <Keyboard.h>
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
int MaxSound = 800; //最高音量，必須介於0~1023

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

  Keyboard.begin();
  Keyboard.releaseAll();
}

void loop() {
  light(setNums());//依音量顯示LED燈數
  Serial.println(sounds);
  Serial.println(nums);
  Serial.println("");
  delay(100);

  if ( analogRead( A0 ) > MaxSound ) {

    pinMode(4,INPUT_PULLUP); //make pin 4 an input and turn on the pullup resistor so it goes high unless connected to ground
    if(digitalRead(4)==LOW){  // do nothing until pin 4 goes low
      Keyboard.press(131); //the key to press (ASCII code)
    }
    pinMode(4,INPUT_PULLUP); //make pin 4 an input and turn on the pullup resistor so it goes high unless connected to ground
    if(digitalRead(4)==LOW){  // do nothing until pin 4 goes low
      Keyboard.press('r'); //the key to press (ASCII code)
    }
    Keyboard.releaseAll();
    delay( 2000 ); // waits a few milliseconds 

    pinMode(4,INPUT_PULLUP); //make pin 4 an input and turn on the pullup resistor so it goes high unless connected to ground
    if(digitalRead(4)==LOW){  // do nothing until pin 4 goes low
      Keyboard.print("notepad"); //Send the message
    }  
    delay( 1000 ); // waits a few milliseconds 

    pinMode(4,INPUT_PULLUP); //make pin 4 an input and turn on the pullup resistor so it goes high unless connected to ground
    if(digitalRead(4)==LOW){  // do nothing until pin 4 goes low
      Keyboard.press(176); //the key to press (ASCII code)
    }
    Keyboard.releaseAll();
    delay( 1000 ); // waits a few milliseconds 

    pinMode(4,INPUT_PULLUP); //make pin 4 an input and turn on the pullup resistor so it goes high unless connected to ground
    if(digitalRead(4)==LOW){  // do nothing until pin 4 goes low
      Keyboard.print("Stop Talking..."); //Send the message
    }
  }
  
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
