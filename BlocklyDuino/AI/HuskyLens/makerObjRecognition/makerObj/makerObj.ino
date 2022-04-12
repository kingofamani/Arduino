#include "HUSKYLENS.h"
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

HUSKYLENS huskylens;
//HUSKYLENS 綠線 >> SDA(A4); 藍線 >> SCL(A5)
int ID0 = 0;
int ID1 = 1;
int ID2 = 2;
int ID3 = 3;
int ID4 = 4;
int ID5 = 5;

int AnsID = 0;//亂數答案
int ReplyID = 0;//使用者舉牌

int LedPins[5] = {2, 3, 4, 5, 6}; //LED腳位

int BtnPin = 7;//按鈕腳位
int BeepPin = 8;//無源蜂嗚器腳位

int YesLightPin = 9;//答對燈號
int NoLightPin1 = 10;//答錯燈號
int NoLightPin2 = 11;//答錯燈號

int BtnResetPin = 12;//重開機按鈕腳位

boolean isWin = false;//是否猜對

#define LED_COUNT 12//WS2812燈泡數
Adafruit_NeoPixel strip(LED_COUNT, YesLightPin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripNo1(LED_COUNT, NoLightPin1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripNo2(LED_COUNT, NoLightPin2, NEO_GRB + NEO_KHZ800);

//Mario
int melody[] = {
  2637, 2637, 0, 2637,
  0, 2093, 2637, 0,
  3136, 0, 0,  0,
  1568, 0, 0, 0,

  2093, 0, 0, 1568,
  0, 0, 1319, 0,
  0, 1760, 0, 1976,
  0, 1865, 1760, 0,

  1568, 2637, 3136,
  3520, 0, 2794, 3136,
  0, 2637, 0, 2093,
  2349, 1976, 0, 0

};

//Mario tempo
int tempo[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12


};

void printResult(HUSKYLENSResult result);

void setup() {
  Serial.begin(115200);

  //腳位
  pinMode(BtnPin, INPUT);
  pinMode(BtnResetPin, INPUT);
  pinMode(BeepPin, OUTPUT);
  pinMode(YesLightPin, OUTPUT);
  pinMode(NoLightPin1, OUTPUT);
  pinMode(NoLightPin2, OUTPUT);
  for (int i = 0; i < 5; i++) {
    pinMode(LedPins[i], OUTPUT);
  }

  //WS2812
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  strip.begin();
  strip.show();
  strip.setBrightness(10);

  stripNo1.begin();
  stripNo1.show();
  stripNo1.setBrightness(10);

  stripNo2.begin();
  stripNo2.show();
  stripNo2.setBrightness(10);

  //初始HuskyLens
  Wire.begin();
  while (!huskylens.begin(Wire))
  {
    Serial.println(F("Begin failed!"));
    Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>I2C)"));
    Serial.println(F("2.Please recheck the connection."));
    delay(100);
  }

  huskylens.writeAlgorithm(ALGORITHM_OBJECT_RECOGNITION);

  //亂數
  randomSeed(analogRead(0));

  Serial.println("請按鈕");

}

void loop() {


  if (digitalRead(BtnPin) == 1) {
    //亂數跑燈
    runLights();
    //AI物件識別
    startRecog();
    //重新開始
    if (isWin) {
      reStart();
    }
    //delay(2000);
  }




}

void reStart() {
  Serial.println("################重新開始###################");
  ReplyID = 0;
  AnsID = 0;
  isWin = false;

  yesNoLight(LOW);
  //yesNoLight(true,LOW);
  //yesNoLight(false,LOW);

  for (int i = 0; i < 5; i++) {
    digitalWrite(LedPins[i], LOW);
  }

  Serial.println(String() + "答案是：" + AnsID);
}

void yesNoLight(int light) {

  if (light == HIGH) {
    theaterChaseRainbow(50);
    //rainbow(10);
  } else {
    //燈滅
    for (int j = 255; j >= 0; j--) {
      strip.fill(strip.Color(0, 0, 0, strip.gamma8(j)));
      strip.show();
    }
  }

  //Serial.println(String() + "YesLightPin:" + light);
}

//void yesNoLight(boolean ans, int light) {
////  digitalWrite(YesLightPin, ((ans && light == HIGH) ? 1 : 0));
////  digitalWrite(NoLightPin1, ((!ans && light == HIGH) ? 1 : 0));
//
//  Serial.println(String() + "YesLightPin:" + ((ans && light == HIGH) ? 1 : 0));
//  //Serial.println(String() + "NoLightPin1:" + ((!ans && light == HIGH) ? 1 : 0));
//
//
//}

void colorWipe(uint32_t color, int wait) {
  for (int j = 0; j <= 2; j++) {
    for (int i = 0; i < stripNo1.numPixels(); i++) {
      stripNo1.setPixelColor(i, color);
      stripNo1.show();
      stripNo2.setPixelColor(i, color);
      stripNo2.show();
      delay(wait);
    }
  }

  //燈滅
  for (int j = 255; j >= 0; j--) {
    stripNo1.fill(stripNo1.Color(0, 0, 0, stripNo1.gamma8(j)));
    stripNo1.show();
    stripNo2.fill(stripNo2.Color(0, 0, 0, stripNo2.gamma8(j)));
    stripNo2.show();
  }
}

void rainbow(int wait) {
  for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
    strip.rainbow(firstPixelHue);
    strip.show();
    delay(wait);
  }
}

void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;
  for (int a = 0; a < 30; a++) {
    for (int b = 0; b < 3; b++) {
      strip.clear();

      for (int c = b; c < strip.numPixels(); c += 3) {
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue));
        strip.setPixelColor(c, color);
      }
      strip.show();
      delay(wait);
      firstPixelHue += 65536 / 90;
    }
  }
}

void runLights() {
  AnsID = random(1, 6);

  int randLight = 0;
  for (int i = 0; i < 100; i++) {
    int randLight = random(1, 6) + 1;
    digitalWrite(randLight, HIGH);
    tone(BeepPin, 400, 30);
    delay(50);
    digitalWrite(randLight, LOW);
    noTone(BeepPin);
  }

  digitalWrite(AnsID + 1, HIGH);
  Serial.println(String() + "答案是：" + AnsID);

}

void startRecog() {
  while (!isWin) {
    delay(500);
    if (huskylens.request())
    {
      Serial.println("###################################");
      //Serial.println(String() + F("訓練總數量 IDs:") + huskylens.countLearnedIDs());

      HUSKYLENSResult result;
      if (huskylens.countBlocks(ID1) >= 1) {
        result = huskylens.getBlock(ID1, 0);
      } else if (huskylens.countBlocks(ID2) >= 1) {
        result = huskylens.getBlock(ID2, 0);
      } else if (huskylens.countBlocks(ID3) >= 1) {
        result = huskylens.getBlock(ID3, 0);
      } else if (huskylens.countBlocks(ID4) >= 1) {
        result = huskylens.getBlock(ID4, 0);
      } else if (huskylens.countBlocks(ID5) >= 1) {
        result = huskylens.getBlock(ID5, 0);
      } else {
        result = huskylens.getBlock(0, 0);
      }
      printResult(result);

      if (ReplyID == AnsID) {
        Serial.println("答對了！");
        isWin = true;
        winSing();
        yesNoLight(HIGH);        
        //yesNoLight(true, HIGH);
        delay(2000);

      } else {
        Serial.println(String() + "錯誤！答案是：" + AnsID + "。請再拿其他卡片試試看：");
        isWin = false;
        yesNoLight(LOW);
        
        //yesNoLight(false, HIGH);

        if (ReplyID >= 1 && ReplyID <= 5) {
          tone(BeepPin, 400, 500);
          delay(500);
          noTone(BeepPin);

          colorWipe(stripNo1.Color(255,   0,   0), 50);
          //colorWipe2(stripNo2.Color(255,   0,   0), 50);
        }
        ReplyID = 0; //避免一直beep

      }

    }
    else
    {
      Serial.println("Fail to request objects from Huskylens!");
    }
  }


}

void printResult(HUSKYLENSResult result) {
  if (result.command == COMMAND_RETURN_BLOCK) { //result is a block
    Serial.println(String() + F("方框:X中心=") + result.xCenter + F(",Y中心=") + result.yCenter + F(",寬=") + result.width + F(",高=") + result.height + F(",ID=") + result.ID);
    ReplyID = result.ID;
  }
  //    else if (result.command == COMMAND_RETURN_ARROW){//result is an arrow
  //        Serial.println(String()+F("Arrow:xOrigin=")+result.xOrigin+F(",yOrigin=")+result.yOrigin+F(",xTarget=")+result.xTarget+F(",yTarget=")+result.yTarget+F(",ID=")+result.ID);
  //    }
  else { //result is unknown.
    Serial.println("xx未知的物體!");
  }
}

//Mario
void winSing() {
    int size = sizeof(melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {
      int noteDuration = 1000 / tempo[thisNote];
      buzz(BeepPin, melody[thisNote], noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      // stop
      buzz(BeepPin, 0, noteDuration);
    }
}

//Mario
void buzz(int targetPin, long frequency, long length) {
  long delayValue = 1000000 / frequency / 2; 
  long numCycles = frequency * length / 1000; 
  for (long i = 0; i < numCycles; i++) { 
    digitalWrite(targetPin, HIGH); 
    delayMicroseconds(delayValue); 
    digitalWrite(targetPin, LOW); 
    delayMicroseconds(delayValue);
  }
}
