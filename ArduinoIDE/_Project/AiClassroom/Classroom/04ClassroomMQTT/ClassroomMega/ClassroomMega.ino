#include <SimpleTimer.h>
#include <Servo.h>
#include <Wire.h>
#include <INA226_WE.h>
#include <Adafruit_NeoPixel.h>

//INA226功率器
INA226_WE ina226 = INA226_WE(0x40);
INA226_WE ina226_2 = INA226_WE(0x41);
INA226_WE ina226_3 = INA226_WE(0x44);

//WS2812
Adafruit_NeoPixel LED1 = Adafruit_NeoPixel(12, 26, NEO_GRB + NEO_KHZ800);
uint32_t LED1_arr[12] = { 0 };
Adafruit_NeoPixel LED2 = Adafruit_NeoPixel(12, 27, NEO_GRB + NEO_KHZ800);
uint32_t LED2_arr[12] = { 0 };
Adafruit_NeoPixel LED3 = Adafruit_NeoPixel(12, 28, NEO_GRB + NEO_KHZ800);
uint32_t LED3_arr[12] = { 0 };

//伺服馬達
Servo __myservo9;

//計時器
SimpleTimer timer;

//消耗能量
float fan_mWh = 0;
float led_mWh = 0;
float lair_mWh = 0;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);

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

  //冷氣
  pinMode(25, OUTPUT);  //冷氣風
  //digitalWrite(25, HIGH);

  __myservo9.attach(9);  //出風口轉向
  __myservo9.write(0);

  pinMode(30, OUTPUT);  //R冷氣狀態燈
  pinMode(31, OUTPUT);  //G
  pinMode(32, OUTPUT);  //B
  digitalWrite(30, HIGH);

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

  //傳送訊息：Mega→ESP32
  //Serial1.print("test");

  //接收訊息：ESP32→Mega
  while (Serial1.available()) {
    //說明：電器只有冷氣airctrl、風扇fan、電燈led這3種而已。控制代碼(開=1、關=0)
    //例如：fan,1
    String deviceControl = Serial1.readString();
    Serial.println(deviceControl);
    //電器、開關
    String myDevice = "";
    String mySwitch = "";
    String tmpArray[2];
    char* token = strtok((char*)str.c_str(), ",");
    int tokenLen = 0;
    while (token != NULL && tokenLen < 2) {
      tmpArray[tokenLen] = token;
      token = strtok(NULL, ",");
      tokenLen++;
    }
    String myDevice = tmpArray[0];
    String mySwitch = tmpArray[1];

    if (myDevice = "fan") {
      if (mySwitch == "1") {
        digitalWrite(22, HIGH);
        digitalWrite(23, HIGH);
        digitalWrite(24, HIGH);
      } else {
        digitalWrite(22, LOW);
        digitalWrite(23, LOW);
        digitalWrite(24, LOW);
      }
    } else if (myDevice = "led") {
      if (mySwitch == "1") {
        LED1SetAllLedsColor(LED1.Color(255, 0, 0));
        LED1ShowAllLedsColor();
        LED2SetAllLedsColor(LED2.Color(255, 102, 0));
        LED2ShowAllLedsColor();
        LED3SetAllLedsColor(LED3.Color(51, 204, 0));
        LED3ShowAllLedsColor();
      } else {
        LED1.clear();
        LED1.show();
        LED2.clear();
        LED2.show();
        LED3.clear();
        LED3.show();
      }
    } else if (myDevice = "airctrl") {
      if (mySwitch == "1") {
        digitalWrite(25, HIGH);//冷氣風
        __myservo9.write(90);//出風口轉向
        digitalWrite(30, LOW);//冷氣狀態燈
        digitalWrite(31, HIGH);
        digitalWrite(32, LOW);
      } else {
        digitalWrite(25, LOW);//冷氣風
        __myservo9.write(0);//出風口轉向
        digitalWrite(30, HIGH);//冷氣狀態燈
        digitalWrite(31, LOW);
        digitalWrite(32, LOW);
      }
    }

  }  //end while
}

void timerFunc0() {
  fan_mWh = 4 * (ina226.getShuntVoltage_mV() * ina226.getCurrent_mA()) / 1000 / 60;
  led_mWh = 28 * (ina226_2.getShuntV oltage_mV() * ina226_2.getCurrent_mA() / 1000 / 60);
  lair_mWh = 1000 * (ina226_3.getShuntVoltage_mV() * ina226_3.getCurrent_mA() / 1000 / 60);
  Serial.println("累加能量(mWh):");
  Serial.print("風扇:");
  Serial.println(fan_mWh);
  Serial.print("LED燈:");
  Serial.println(led_mWh);
  Serial.print("冷氣:");
  Serial.println(lair_mWh);
  Serial.println("---------");
}

void LED1SetAllLedsColor(uint32_t myLedColor) {
  for (int i = 0; i < 12; i++)
    LED1_arr[i] = myLedColor;
}

void LED1ShowAllLedsColor() {
  for (int i = 0; i < 12; i++)
    LED1.setPixelColor(i, LED1_arr[i]);
  LED1.show();
}

void LED1FlowLedsColors(byte dir) {
  uint32_t tempData = 0;
  if (dir == 1) {
    tempData = LED1_arr[0];
    for (int i = 0; i < 11; i++)
      LED1_arr[i] = LED1_arr[i + 1];
    LED1_arr[11] = tempData;
  } else if (dir == 2) {
    tempData = LED1_arr[11];
    for (int i = 11; i > 0; i--)
      LED1_arr[i] = LED1_arr[i - 1];
    LED1_arr[0] = tempData;
  }
  LED1ShowAllLedsColor();
}

void LED2SetAllLedsColor(uint32_t myLedColor) {
  for (int i = 0; i < 12; i++)
    LED2_arr[i] = myLedColor;
}

void LED2ShowAllLedsColor() {
  for (int i = 0; i < 12; i++)
    LED2.setPixelColor(i, LED2_arr[i]);
  LED2.show();
}

void LED2FlowLedsColors(byte dir) {
  uint32_t tempData = 0;
  if (dir == 1) {
    tempData = LED2_arr[0];
    for (int i = 0; i < 11; i++)
      LED2_arr[i] = LED2_arr[i + 1];
    LED2_arr[11] = tempData;
  } else if (dir == 2) {
    tempData = LED2_arr[11];
    for (int i = 11; i > 0; i--)
      LED2_arr[i] = LED2_arr[i - 1];
    LED2_arr[0] = tempData;
  }
  LED2ShowAllLedsColor();
}

void LED3SetAllLedsColor(uint32_t myLedColor) {
  for (int i = 0; i < 12; i++)
    LED3_arr[i] = myLedColor;
}

void LED3ShowAllLedsColor() {
  for (int i = 0; i < 12; i++)
    LED3.setPixelColor(i, LED3_arr[i]);
  LED3.show();
}

void LED3FlowLedsColors(byte dir) {
  uint32_t tempData = 0;
  if (dir == 1) {
    tempData = LED3_arr[0];
    for (int i = 0; i < 11; i++)
      LED3_arr[i] = LED3_arr[i + 1];
    LED3_arr[11] = tempData;
  } else if (dir == 2) {
    tempData = LED3_arr[11];
    for (int i = 11; i > 0; i--)
      LED3_arr[i] = LED3_arr[i - 1];
    LED3_arr[0] = tempData;
  }
  LED3ShowAllLedsColor();
}
