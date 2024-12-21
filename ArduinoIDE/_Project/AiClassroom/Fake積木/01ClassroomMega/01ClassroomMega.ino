//Generated Date: Sat, 21 Dec 2024 02:45:23 GMT

#include <Wire.h>
#include <INA226_WE.h>

#define I2C_ADDRESS 0x40

/* There are several ways to create your INA226 object:
 * INA226_WE ina226 = INA226_WE(); -> uses I2C Address = 0x40 / Wire
 * INA226_WE ina226 = INA226_WE(I2C_ADDRESS);
 * INA226_WE ina226 = INA226_WE(&Wire); -> uses I2C_ADDRESS = 0x40, pass any Wire Object
 * INA226_WE ina226 = INA226_WE(&Wire, I2C_ADDRESS);
 */
INA226_WE ina226 = INA226_WE(I2C_ADDRESS);

#include <Adafruit_NeoPixel.h>
#include <Servo.h>
#include <SimpleTimer.h>
SimpleTimer timer;

float fan_mWh;
float led_mWh;
float airctrl_mWh;
Adafruit_NeoPixel LED1 = Adafruit_NeoPixel(12,26,NEO_GRB + NEO_KHZ800);
uint32_t LED1_arr[12]={0};
Adafruit_NeoPixel LED2 = Adafruit_NeoPixel(12,27,NEO_GRB + NEO_KHZ800);
uint32_t LED2_arr[12]={0};
Adafruit_NeoPixel strip = Adafruit_NeoPixel(12,28,NEO_GRB + NEO_KHZ800);
uint32_t strip_arr[12]={0};
Servo __myservo9;
String controls[2] = {(serialMsg)};
void startDeviceControl(String myDevice, String mySwitch) {
  if (myDevice == "fan") {
    //風扇
    if (mySwitch == "1") {
      digitalWrite(22, HIGH);
      digitalWrite(23, HIGH);
      digitalWrite(24, HIGH);
    } else if (mySwitch == "0") {
      digitalWrite(22, LOW);
      digitalWrite(23, LOW);
      digitalWrite(24, LOW);
    }
  } else if (myDevice == "led") {
    //電燈
    if (mySwitch == "1") {
      LED1SetAllLedsColor(LED1.Color(255,102,0));
      LED1ShowAllLedsColor();
      LED2SetAllLedsColor(LED2.Color(51,204,0));
      LED2ShowAllLedsColor();
      LED3SetAllLedsColor(LED3.Color(0,204,204));
      LED3ShowAllLedsColor();
    } else if (mySwitch == "0") {
      LED1.clear();
      LED1.show();
      LED2.clear();
      LED2.show();
      LED3.clear();
      LED3.show();
    }
  } else if (myDevice == "airctrl") {
    //冷氣
    if (mySwitch == "1") {
      //冷氣風、出風口轉向、狀態燈
      digitalWrite(24, HIGH);
      __myservo9.write(90);
      digitalWrite(24, HIGH);
      digitalWrite(24, LOW);
      digitalWrite(24, LOW);
    } else if (mySwitch == "0") {
      digitalWrite(24, LOW);
      __myservo9.write(180);
      digitalWrite(24, LOW);
      digitalWrite(24, LOW);
      digitalWrite(24, HIGH);
    }
  }
}

int inteval_ID0 = 0;
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

void stripSetAllLedsColor(uint32_t myLedColor)
{
  for(int i=0;i<12;i++)
    strip_arr[i]=myLedColor;
}

void stripShowAllLedsColor()
{
  for(int i=0;i<12;i++)
    strip.setPixelColor(i,strip_arr[i]);
  strip.show();
}

void stripFlowLedsColors(byte dir)
{
  uint32_t tempData=0;
  if (dir==1){
    tempData=strip_arr[0];
    for(int i=0;i<11;i++)
      strip_arr[i]=strip_arr[i+1];
    strip_arr[11]=tempData;
  } else if (dir==2){
    tempData=strip_arr[11];
    for(int i=11;i>0;i--)
      strip_arr[i]=strip_arr[i-1];
    strip_arr[0]=tempData;
  }
  stripShowAllLedsColor();
}

void setup()
{
  Serial1.begin(9600, SERIAL_8N1, 19, 18);
  delay(10);
  Wire.begin();
  if(!ina226.init()){
    Serial.println("Failed to init INA226. Check your wiring.");
    while(1){}
  }
  ina226.waitUntilConversionCompleted(); //if you comment this line the first data might be zero

  LED1.begin();
  LED1.setBrightness(5);
  LED1.show();
  LED1ShowAllLedsColor();
  LED2.begin();
  LED2.setBrightness(5);
  LED2.show();
  LED2ShowAllLedsColor();
  strip.begin();
  strip.setBrightness(5);
  strip.show();
  stripShowAllLedsColor();
  __myservo9.attach(9);
  pinMode(30, OUTPUT);
  pinMode(31, OUTPUT);
  pinMode(32, OUTPUT);
  ina226.powerUp();
  //LED燈
  __myservo9.write(180);
  //冷氣狀態燈
  digitalWrite(30, LOW);
  digitalWrite(31, LOW);
  digitalWrite(32, HIGH);
  timer.disable(inteval_ID0);
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(24, OUTPUT);
  inteval_ID0 = timer.setInterval(60000, intevalFunc0);
timer.disable(inteval_ID0);

}

void loop()
{
  timer.run();  //接收訊息：ESP32→Mega
  if (Serial1.available()) {
    String serialMsg = "";
    while (Serial1.available()) {
      serialMsg = Serial1.readString();
      //收到電器控制指令（例如fan,1），開始開關電器
    startDeviceControl(controls[0], controls[1]);
    //開始計算耗電量，每分鐘上傳Google試算表
    if ((controls[1]) == "1") {
      timer.enable(inteval_ID0);
    } else if ((controls[1]) == "0") {
      timer.disable(inteval_ID0);
    }
    }
  }
}

void intevalFunc0(){
   //計算耗電量
  fan_mWh = ( * ) / 1000;
  led_mWh = ( * ) / 1000;
  airctrl_mWh = ( * ) / 1000;
  //通知ESP32，上傳Google試算表
  Serial1.print((String(fan_mWh)+String(",")+String(led_mWh)+String(",")+String(airctrl_mWh)));
  }
