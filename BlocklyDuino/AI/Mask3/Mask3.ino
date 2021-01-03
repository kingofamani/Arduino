/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Sun, 03 Jan 2021 08:41:48 GMT
 */



int PIN_NO_MASK;

boolean isMasked;

int PIN_MASK;

int PIN_LED;

int PIN_NOTHING;

int count;

void mask1() {
  //沒口罩 腳位(配合RPi GPIO 26)
  PIN_NO_MASK = 3;
  //有口罩 腳位(配合RPi GPIO 19)
  PIN_MASK = 4;
  //空 腳位(配合RPi GPIO 13)
  PIN_NOTHING = 5;
  //LED 腳位
  PIN_LED = 8;
  count = 0;
  //是否戴口罩
  isMasked = false;
}

bool mask(){
  if(digitalRead(PIN_MASK) && !digitalRead(PIN_NO_MASK) && !digitalRead(PIN_NOTHING)){
count ++;
}else{
count =0;
}
delay(600);
if(count >=3){
return true;
 }else{
return false;
}
}
void m() {
}

void setup()
{
  Serial.begin(9600);

  mask1();
  pinMode(PIN_LED, OUTPUT);
}


void loop()
{
  isMasked = mask();
  if (isMasked) {
    digitalWrite(PIN_LED, HIGH);
    Serial.println("已戴口罩 請通行");

  } else {
    digitalWrite(PIN_LED, LOW);
    Serial.println("XX禁止通行(請戴口罩)XX");

  }
}