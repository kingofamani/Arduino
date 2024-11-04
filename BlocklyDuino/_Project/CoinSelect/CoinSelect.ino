/***
 *先測試每種硬幣的亮度值，填入coinsLight[4][6]陣列裡後，才可以使用
  testCoinLight(upLight, midLight, downLight);
 */

#include <FastLED.h>

#define NUM_LEDS 8 // 定義WS2812燈的數量
#define LED_PIN 2 // 定義WS2812 LED燈使用的D2腳位
#define BRIGHTNESS  64 // LED燈的亮度

CRGB leds[NUM_LEDS]; // 定義WS2812燈的陣列

const int UP_LDR_PIN = A2;
const int MID_LDR_PIN = A1;
const int DOWN_LDR_PIN = A0;

int coin = 0;//投入多少錢
int coinValue[4] = {1, 5, 10, 50};
String coinName[4] = {"1元", "5元", "10元", "50元"};
//硬幣索引值0,1,2,3，分別是1元,5元,10元,50元
int coinIndex = -1;
int preCoinIndex = -1;

//硬幣連續感應次數
int coinCount = 0;
//閾值(連續幾次判斷成功才算)
int THRESHOLD = 200;
//兩次coin判斷超過幾毫秒才算是投下1個硬幣
int nextCoinMillisSeconds = 200;//71.4
unsigned long preMillis = 0;

//1,5,10,50元
//Up_min、up_max、mid_min、mid_max、down_min、down_max
//自行測試並填入
int coinsLight[4][6] = {
  {715, 955, 230, 490, 230, 840}, //1元
  {680, 900, 140, 380, 0, 240}, //5元
  {540, 770, 0, 50, 0, 230}, //10元
  {0, 180, 0, 50, 0, 206}, //50元
};

void setup()
{
  Serial.begin(9600);
  turnOnLight();//開Led燈
}

void loop()
{
  //偵測到的亮度
  int upLight = analogRead(UP_LDR_PIN);
  int midLight = analogRead(MID_LDR_PIN);
  int downLight = analogRead(DOWN_LDR_PIN);

  //先測試每種硬幣的亮度值，填入coinsLight[4][6]陣列裡後，才可以使用
  //testCoinLight(upLight, midLight, downLight);

  //硬幣種類判斷
  int  c = whichCoin(upLight, midLight, downLight);
  if (c != 0) {
    Serial.print(c);
  }

}

void testCoinLight(int up, int mid, int down) {
  Serial.print("上:");
  Serial.print(up);
  Serial.print(" 中：");
  Serial.print(mid);
  Serial.print(" 下：");
  Serial.println(down);
  Serial.println("");
  delay(200);
}

int whichCoin(int up, int mid, int down) {
  //判斷幣別
  for (int i = 0; i < 4; i++) {
    bool isUpOk = ((coinsLight[i][0] <= up) && (up <= coinsLight[i][1]));
    bool isMidOk = ((coinsLight[i][2] <= mid) && (mid <= coinsLight[i][3]));
    bool isDownOk = ((coinsLight[i][4] <= down) && (down <= coinsLight[i][5]));
    if (isUpOk && isMidOk && isDownOk) {
      coinIndex = i;
      break;
    } else {
      coinIndex = -1;
    }
  }

  //判斷連續達到閾值才算成功
  if (coinIndex != -1) {
    if (coinIndex != preCoinIndex) {
      preCoinIndex = coinIndex;
      coinCount = 0;
    } else {
      coinCount++;
    }

    if (coinCount == THRESHOLD) {
      coin = coinValue[coinIndex];

      //是否投入下一個代幣
      if ((millis() - preMillis) >= nextCoinMillisSeconds) {
        return coinValue[coinIndex];
      }

      //歸零
      preMillis = millis();
      coin = 0;
      coinCount = 0;
      coinIndex = -1;
      preCoinIndex = -1;
    }

  }// END if(coinIndex != -1)
  return 0;
}// END whichCoin

void turnOnLight() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  //燈全亮
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::White;
  }
  FastLED.show();
}
