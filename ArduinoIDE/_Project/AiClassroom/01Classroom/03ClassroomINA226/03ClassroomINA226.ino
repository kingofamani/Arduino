//Generated Date: Mon, 09 Dec 2024 04:03:49 GMT

#include <SimpleTimer.h>
#include <Wire.h>
#include <INA226_WE.h>
#include <Adafruit_NeoPixel.h>

INA226_WE ina226 = INA226_WE(0x40);
INA226_WE ina226_2 = INA226_WE(0x41);
INA226_WE ina226_3 = INA226_WE(0x44);

Adafruit_NeoPixel LED1 = Adafruit_NeoPixel(12,26,NEO_GRB + NEO_KHZ800);
uint32_t LED1_arr[12]={0};
Adafruit_NeoPixel LED2 = Adafruit_NeoPixel(12,27,NEO_GRB + NEO_KHZ800);
uint32_t LED2_arr[12]={0};
Adafruit_NeoPixel LED3 = Adafruit_NeoPixel(12,28,NEO_GRB + NEO_KHZ800);
uint32_t LED3_arr[12]={0};

SimpleTimer timer;

float fan_mW = 0;
float led_mW = 0;
float air_mW = 0;

void setup() {
  Serial.begin(9600);

  //INA226功率器
  Wire.begin();
  if (!ina226.init()) {
    Serial.println("Failed to init INA226. Check your wiring.");
    while (1) {}
  }
  if (!ina226_2.init()) {
    Serial.println("Failed to init ina226_2. Check your wiring.");
    while (1) {}
  }
  if (!ina226_3.init()) {
    Serial.println("Failed to init ina226_3. Check your wiring.");
    while (1) {}
  }
  ina226.waitUntilConversionCompleted();
  ina226_2.waitUntilConversionCompleted();
  ina226_3.waitUntilConversionCompleted();

  ina226.powerUp();
  ina226_2.powerUp();
  ina226_3.powerUp();

  ina226.init();
  ina226_2.init();
  ina226_3.init();
 
  //風扇
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(24, OUTPUT);

  digitalWrite(22, HIGH);
  digitalWrite(23, HIGH);
  digitalWrite(24, HIGH);

  //冷氣
  pinMode(25, OUTPUT);//出風口
  digitalWrite(25, HIGH);

  //WS2812燈
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

  //計時器
  timer.setInterval(1000, timerFunc0);
}

void loop() {
  timer.run();

  LED1SetAllLedsColor(LED1.Color(255,0,0));
  LED1ShowAllLedsColor();
  LED2SetAllLedsColor(LED2.Color(255,102,0));
  LED2ShowAllLedsColor();
  LED3SetAllLedsColor(LED3.Color(51,204,0));
  LED3ShowAllLedsColor();
}

void timerFunc0() {
  fan_mW = 4*(ina226.getShuntVoltage_mV() * ina226.getCurrent_mA())/1000/60;
  led_mW = 28*(ina226_2.getShuntV                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             oltage_mV() * ina226_2.getCurrent_mA()/1000/60);
  air_mW = 1000*(ina226_3.getShuntVoltage_mV() * ina226_3.getCurrent_mA()/1000/60);
  Serial.println("累加能量(mWh):");
  Serial.print("風扇:");
  Serial.println(fan_mW);
  Serial.print("LED燈:");
  Serial.println(led_mW);
  Serial.print("冷氣:");
  Serial.println(air_mW);
   Serial.println("---------");
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



