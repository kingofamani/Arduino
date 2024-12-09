//Generated Date: Sat, 07 Dec 2024 02:54:21 GMT

#include <Adafruit_NeoPixel.h>
#include <Servo.h>

Adafruit_NeoPixel LED1 = Adafruit_NeoPixel(12,26,NEO_GRB + NEO_KHZ800);
uint32_t LED1_arr[12]={0};
Adafruit_NeoPixel LED2 = Adafruit_NeoPixel(12,27,NEO_GRB + NEO_KHZ800);
uint32_t LED2_arr[12]={0};
Adafruit_NeoPixel LED3 = Adafruit_NeoPixel(12,28,NEO_GRB + NEO_KHZ800);
uint32_t LED3_arr[12]={0};
Servo __myservo9;
void funcFan() {
  Serial.println("風扇");
  digitalWrite(22, HIGH);
  delay(1000);
  digitalWrite(22, LOW);
  delay(1000);
  digitalWrite(23, HIGH);
  delay(1000);
  digitalWrite(23, LOW);
  delay(1000);
  digitalWrite(24, HIGH);
  delay(1000);
  digitalWrite(24, LOW);
  delay(1000);
  digitalWrite(25, HIGH);
  delay(1000);
  digitalWrite(25, LOW);
  delay(3000);
}

void funcLed() {
  Serial.println("LED燈");
  LED1Breathe(LED1.Color(51,255,51),10);
  LED1.setBrightness(5);
  delay(1000);
  LED2Breathe(LED2.Color(255,204,102),10);
  LED2.setBrightness(5);
  delay(1000);
  LED3Breathe(LED3.Color(51,204,255),10);
  LED3.setBrightness(5);
  delay(1000);
}

void funcServo() {
  Serial.println("馬達");
  __myservo9.write(90);
  delay(1000);
  __myservo9.write(0);
  delay(1000);
}

void funcAirLight() {
  Serial.println("冷氣狀態燈");
  digitalWrite(30, HIGH);
  digitalWrite(31, HIGH);
  digitalWrite(32, HIGH);
  delay(1000);
  digitalWrite(30, LOW);
  digitalWrite(31, LOW);
  digitalWrite(32, LOW);
  delay(1000);
}

void LED1SetAllLedsColor(uint32_t myLedColor)
{
  for(int i=0;i<12;i++)
    LED1_arr[i]=myLedColor;
}

void LED1ShowAllLedsColor()
{
  for(int i=0;i<12;i++)
    LED1.setPixelColor(i,LED1_arr[i]);
  LED1.show();
}

void LED1FlowLedsColors(byte dir)
{
  uint32_t tempData=0;
  if (dir==1){
    tempData=LED1_arr[0];
    for(int i=0;i<11;i++)
      LED1_arr[i]=LED1_arr[i+1];
    LED1_arr[11]=tempData;
  } else if (dir==2){
    tempData=LED1_arr[11];
    for(int i=11;i>0;i--)
      LED1_arr[i]=LED1_arr[i-1];
    LED1_arr[0]=tempData;
  }
  LED1ShowAllLedsColor();
}

void LED2SetAllLedsColor(uint32_t myLedColor)
{
  for(int i=0;i<12;i++)
    LED2_arr[i]=myLedColor;
}

void LED2ShowAllLedsColor()
{
  for(int i=0;i<12;i++)
    LED2.setPixelColor(i,LED2_arr[i]);
  LED2.show();
}

void LED2FlowLedsColors(byte dir)
{
  uint32_t tempData=0;
  if (dir==1){
    tempData=LED2_arr[0];
    for(int i=0;i<11;i++)
      LED2_arr[i]=LED2_arr[i+1];
    LED2_arr[11]=tempData;
  } else if (dir==2){
    tempData=LED2_arr[11];
    for(int i=11;i>0;i--)
      LED2_arr[i]=LED2_arr[i-1];
    LED2_arr[0]=tempData;
  }
  LED2ShowAllLedsColor();
}

void LED3SetAllLedsColor(uint32_t myLedColor)
{
  for(int i=0;i<12;i++)
    LED3_arr[i]=myLedColor;
}

void LED3ShowAllLedsColor()
{
  for(int i=0;i<12;i++)
    LED3.setPixelColor(i,LED3_arr[i]);
  LED3.show();
}

void LED3FlowLedsColors(byte dir)
{
  uint32_t tempData=0;
  if (dir==1){
    tempData=LED3_arr[0];
    for(int i=0;i<11;i++)
      LED3_arr[i]=LED3_arr[i+1];
    LED3_arr[11]=tempData;
  } else if (dir==2){
    tempData=LED3_arr[11];
    for(int i=11;i>0;i--)
      LED3_arr[i]=LED3_arr[i-1];
    LED3_arr[0]=tempData;
  }
  LED3ShowAllLedsColor();
}

void LED1Breathe(uint32_t myLedColor,uint8_t interval)
{
  LED1.clear();
  LED1.show();
  LED1.setBrightness(0);
  LED1SetAllLedsColor(myLedColor);
  LED1ShowAllLedsColor();
  for(int i=0;i<255;i++){
    LED1.setBrightness(i);
    LED1.show();
    if (i==1)
      LED1ShowAllLedsColor();
    delay(interval);
  }
  for(int i=255;i>-1;i--){
    LED1.setBrightness(i);
    LED1.show();
    delay(interval);
  }
}

void LED2Breathe(uint32_t myLedColor,uint8_t interval)
{
  LED2.clear();
  LED2.show();
  LED2.setBrightness(0);
  LED2SetAllLedsColor(myLedColor);
  LED2ShowAllLedsColor();
  for(int i=0;i<255;i++){
    LED2.setBrightness(i);
    LED2.show();
    if (i==1)
      LED2ShowAllLedsColor();
    delay(interval);
  }
  for(int i=255;i>-1;i--){
    LED2.setBrightness(i);
    LED2.show();
    delay(interval);
  }
}

void LED3Breathe(uint32_t myLedColor,uint8_t interval)
{
  LED3.clear();
  LED3.show();
  LED3.setBrightness(0);
  LED3SetAllLedsColor(myLedColor);
  LED3ShowAllLedsColor();
  for(int i=0;i<255;i++){
    LED3.setBrightness(i);
    LED3.show();
    if (i==1)
      LED3ShowAllLedsColor();
    delay(interval);
  }
  for(int i=255;i>-1;i--){
    LED3.setBrightness(i);
    LED3.show();
    delay(interval);
  }
}

void setup()
{
  LED1.begin();
  LED1.setBrightness(5);
  LED1.show();
  LED1ShowAllLedsColor();
  LED2.begin();
  LED2.setBrightness(5);
  LED2.show();
  LED2ShowAllLedsColor();
  LED3.begin();
  LED3.setBrightness(5);
  LED3.show();
  LED3ShowAllLedsColor();
  __myservo9.attach(9);
  __myservo9.write(0);
  Serial.begin(9600);

  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(30, OUTPUT);
  pinMode(31, OUTPUT);
  pinMode(32, OUTPUT);
}

void loop()
{
  funcFan();
  funcLed();
  funcServo();
  funcAirLight();
}
