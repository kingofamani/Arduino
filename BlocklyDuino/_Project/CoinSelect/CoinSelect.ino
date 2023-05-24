#include <FastLED.h>

#define NUM_LEDS 8 // 定義WS2812燈的數量
#define LED_PIN 2 // 定義WS2812 LED燈使用的D2腳位
#define BRIGHTNESS  64 // LED燈的亮度

CRGB leds[NUM_LEDS]; // 定義WS2812燈的陣列

const int UP_LDR_PIN = A2;
const int MID_LDR_PIN = A1;
const int DOWN_LDR_PIN = A0;

////上方光敏：沒有被遮蔽、遮一半、全遮時的亮度
//const int UP_LDR_LIGHT[3] = {800, 100, 400};
////中間光敏：沒有被遮蔽、遮一半、全遮時的亮度
//const int MID_LDR_LIGHT[3] = {800, 100, 400};
////下方光敏：沒有被遮蔽、遮一半、全遮時的亮度
//const int DOWN_LDR_LIGHT[3] = {800, 100, 400};

/***
  xxxxxxxxxx 硬幣被上、中、下3個光敏遮住的面積：
          上   中   下
   1元：  no    no  half
   5元：  no    no  all
   10元： no    all  all
   50元： half  all  all
   xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
*/
const int DOLLAR_1 = 0;
const int DOLLAR_5 = 1;
const int DOLLAR_10 = 2;
const int DOLLAR_50 = 3;
//1,5,10,50元
//Up_min、up_max、mid_min、mid_max、down_min、down_max
int coinsLight[4][6] = {
  {0,50,250,500,530,900},//1元
  {0,50,250,500,250,550},//5元
  {750,980,5,40,200,400},//10元
  {750,980,0,18,20,100},//50元
};
//int coinsLight[4][6] = {
//  {750,900,250,500,530,800},
//  {750,900,250,500,70,300},
//  {750,900,5,40,30,110},
//  {500,750,0,18,20,50},
//};

//int coinsLight[4][3] = {
//  {UP_LDR_LIGHT[0], MID_LDR_LIGHT[0], DOWN_LDR_LIGHT[1]},
//  {UP_LDR_LIGHT[0], MID_LDR_LIGHT[0], DOWN_LDR_LIGHT[2]},
//  {UP_LDR_LIGHT[0], MID_LDR_LIGHT[2], DOWN_LDR_LIGHT[2]},
//  {UP_LDR_LIGHT[1], MID_LDR_LIGHT[2], DOWN_LDR_LIGHT[2]},
//};

//偵測到的亮度
int upLight = 0;
int midLight = 0;
int downLight = 0;

//亮度允許±誤差值
//const int TOL = 10;

void setup()
{
  Serial.begin(9600);

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  //燈全亮
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::White;
  }
  FastLED.show();
}

void loop()
{
  //硬幣種類判斷
  upLight = analogRead(UP_LDR_PIN);
  midLight = analogRead(MID_LDR_PIN);
  downLight = analogRead(DOWN_LDR_PIN);

  //Serial.println(whichCoin(upLight, midLight, downLight));

  

//  Serial.print(upLight);
//  Serial.print(" ");
//  Serial.print(midLight);
//  Serial.print(" ");
//  Serial.println(downLight);
//  Serial.println("");
//  delay(200);

int coin = whichCoin(upLight, midLight, downLight);
  if(coin != -1){
    Serial.print(" ");
    Serial.println(coin);
  }
  delay(10);
}

int whichCoin(int up, int mid, int down) {
  int coin = -1;
  //範圍
  for (int i = 0; i < 6; i++) {
    bool isUpOk = ((coinsLight[i][0] <= up) && (up <= coinsLight[i][1]));
    bool isMidOk = ((coinsLight[i][2] <= mid) && (mid <= coinsLight[i][3]));
    bool isDownOk = ((coinsLight[i][4] <= down) && (down <= coinsLight[i][5]));
    if (isUpOk && isMidOk && isDownOk) {
      coin = i;
    }
  }
  return coin;
}

//int whichCoin(int up, int mid, int down) {
//  int coin = -1;
//  //範圍
//  for (int i = 0; i < 4; i++) {
//    bool isUpOk = ((coinsLight[i][0] - TOL <= up) && (up <= coinsLight[i][0] + TOL));
//    bool isMidOk = ((coinsLight[i][1] - TOL <= mid) && (mid <= coinsLight[i][1] + TOL));
//    bool isDownOk = ((coinsLight[i][2] - TOL <= down) && (down <= coinsLight[i][2] + TOL));
//    if (isUpOk && isMidOk && isDownOk) {
//      coin = i;
//    }
//  }
//  return coin;
//}
