/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Thu, 26 Nov 2020 00:52:19 GMT
 */



int PIN_WATER;

boolean hasWater;

boolean WATER_TRIGGER;

bool waterSersor(int pinWater, bool trigger) {
  int count = 0;
  for (int i = 0; i < 20; i++) {
    if (digitalRead(pinWater) == trigger) count ++;
    delay(10);
  }
  return (count == 20);
}
void o() {
  /*
    判斷是否有水
     傳入值：
        pinWater:水位偵測器腳位
        trigger:水位算測器種類(高/低電平)HIGH/LOW
     傳回值：有水回傳true，沒水回傳false

  */
}

void setup()
{
  Serial.begin(9600);

  pinMode(PIN_WATER, INPUT);
}


void loop()
{
  //水位測器腳位
PIN_WATER = 6;
//水位偵測器高/低電平
WATER_TRIGGER = HIGH;

hasWater = 0;
  hasWater = waterSersor(PIN_WATER, WATER_TRIGGER);
  if (hasWater) {
    Serial.println("有水");

  } else {
    Serial.println("空…");

  }
}