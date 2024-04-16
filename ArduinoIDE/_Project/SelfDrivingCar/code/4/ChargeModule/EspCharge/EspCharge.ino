//Generated Date: Sat, 23 Dec 2023 13:07:19 GMT

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <Wire.h>
#include <Adafruit_INA219.h>
#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal_I2C.h>
//https://docs.google.com/spreadsheets/d/1EhpZyQILsXqWKgGFPZdoaBGQzfcb2x20n4-tTqJc-uI/edit#gid=399078205
//====變數設定 Start====
//WiFi
const char* ssid = "tyes-itc";
const char* password = "22924152";
//google 試算表
String sheetId = "1EhpZyQILsXqWKgGFPZdoaBGQzfcb2x20n4-tTqJc-uI";  //試算表id
String sheetTag = "";
const char* sTag = "charge";  //工作表名稱
//限位器
const int PIN_BTN_PLUS = 4;
const int PIN_BTN_MINUS = 5;
//WS2812
String matrixString = "000000000000000000000000000000000000000000000000";
int MatrixLed_marquee_time = 500;
int MatrixLed_marquee_rotate = 0;
int MatrixLed_leds_number = 8;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(8, 13, NEO_GRB + NEO_KHZ800);
String strTemp_ = "";
unsigned long preMillis;

//LCM1602
LiquidCrystal_I2C lcd_i2c(0x27,20,4);
unsigned long preMillisLcm;
bool switchLine = false;


//====變數設定 End====
//asId不要變更
const char* asId = "AKfycbyR-Yp-uu4nIvnjvnkILaQ5AX8yFxp-UpBO-Sqs0su3ai1N_BvQsz_Q";

//測電流電壓
float shuntvoltage = 0;
float busvoltage = 0;
float current_mA = 0;
float loadvoltage = 0;
float power_mW = 0;
Adafruit_INA219 ina219Bat;  //太陽能→14500鋰電池
Adafruit_INA219 ina219Car;  //14500鋰電池→小車
//紀錄上一次上傳google sheet時間
unsigned long preMillisBat;
unsigned long preMillisCar;


void setup() {
  Serial.begin(9600);
  while (!Serial) { delay(1); }
  delay(500);
  setup_wifi();

  //限位器
  pinMode(PIN_BTN_PLUS, INPUT_PULLUP);
  pinMode(PIN_BTN_MINUS, INPUT_PULLUP);

  //WS2812
  pixels.begin();
  pixels.show();
  pixels.setBrightness(50);

  //LCM1602
  lcd_i2c.init(); 
  lcd_i2c.backlight();

  //測電流電壓初始
  if (!ina219Bat.begin()) {
    Serial.println("Failed to find ina219Bat chip");
    while (1) { delay(10); }
  }
  if (!ina219Car.begin()) {
    Serial.println("Failed to find ina219Car chip");
    while (1) { delay(10); }
  }
}

void loop() {
  batCharging();
  //carCharging();
  triggerButton();
}

void triggerButton() {
  if (digitalRead(PIN_BTN_PLUS) == 0 || digitalRead(PIN_BTN_MINUS) == 0) {
    //Serial.print("車子已停妥");

    //計算小車充電瓦數
    carCharging();
    
    if (millis() - preMillis >= 500) {
      //開啟WS2812
      MatrixLedList(String(MatrixLedColorRandom()) + String(MatrixLedColorRandom()) + String(MatrixLedColorRandom()) + String(MatrixLedColorRandom()) + String(MatrixLedColorRandom()) + String(MatrixLedColorRandom()) + String(MatrixLedColorRandom()) + String(MatrixLedColorRandom()));      

      //開啟LCM1602      
      if(switchLine){
        lcd_i2c.setCursor(0,0);
        lcd_i2c.print("Charging...");
        lcd_i2c.setCursor(0,1);
        lcd_i2c.print("               ");
      }else{
        lcd_i2c.setCursor(0,0);
        lcd_i2c.print("               ");
        lcd_i2c.setCursor(0,1);
        lcd_i2c.print("Charging...");
      }       
      switchLine = !switchLine; 

      preMillis = millis();
    }
    
  }else{
    //清除WS2812
    MatrixLedAll("000000");
    //清除LCM1602
    lcd_i2c.clear();
  }
}

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
String URLEncode(const char* msg) {
  const char* hex = "0123456789abcdef";
  String encodedMsg = "";
  while (*msg != '\0') {
    if (('a' <= *msg && *msg <= 'z')
        || ('A' <= *msg && *msg <= 'Z')
        || ('0' <= *msg && *msg <= '9')) {
      encodedMsg += *msg;
    } else {
      encodedMsg += '%';
      encodedMsg += hex[*msg >> 4];
      encodedMsg += hex[*msg & 15];
    }
    msg++;
  }
  return encodedMsg;
}
void sendToGoogleSheets(const String& dateInclude, const String& data) {
  sheetTag = URLEncode(sTag);
  static WiFiClientSecure sheetClient;
  sheetClient.setInsecure();
  const char* host = "script.google.com";
  if (sheetClient.connect(host, 443)) {
    const String url = String() + "https://" + host + "/macros/s/" + asId + "/exec?type=insert&dateInclude=" + dateInclude + "&sheetId=" + sheetId + "&sheetTag=" + sheetTag + "&data=" + data;
    sheetClient.println("GET " + url + " HTTP/1.1");
    sheetClient.println(String() + "Host: " + host);
    sheetClient.println("Accept: */*");
    sheetClient.println("Connection: close");
    sheetClient.println();
    sheetClient.println();
    sheetClient.stop();
  }
}
void batCharging() {
  //Serial.println("bat");
  int interval = 61;  //31每隔幾秒紀錄一次
  if (millis() - preMillisBat >= interval * 1000) {
    Serial.println("bat:millis");
    preMillisBat = millis();

    shuntvoltage = ina219Bat.getShuntVoltage_mV();
    busvoltage = ina219Bat.getBusVoltage_V();          //Bus Voltage電池電壓(V)
    current_mA = ina219Bat.getCurrent_mA();            //Current負載電流(mA)
    power_mW = ina219Bat.getPower_mW();                //Power負載功率(mW)
    loadvoltage = busvoltage + (shuntvoltage / 1000);  //Load Voltage負載電壓(V)

    Serial.print(shuntvoltage);
    Serial.print(",");
    Serial.print(busvoltage);
    Serial.print(",");
    Serial.print(current_mA);
    Serial.print(",");
    Serial.println(power_mW);

    //寫入google試算表
    if (busvoltage*current_mA > 0) {//power_mW > 0
      Serial.println("bat:Sheets");
      sendToGoogleSheets("1", URLEncode((String() + "太陽能板產生能量" + "," + busvoltage*current_mA + "," + interval).c_str()));
    }
  }
}
void carCharging() {
  //Serial.println("car");
  int interval = 10;  //61每隔幾秒紀錄一次
  if (millis() - preMillisCar >= interval * 1000) {
    Serial.println("car:millis");
    preMillisCar = millis();

    shuntvoltage = ina219Car.getShuntVoltage_mV();
    busvoltage = ina219Car.getBusVoltage_V();          //Bus Voltage電池電壓(V)
    current_mA = ina219Car.getCurrent_mA();            //Current負載電流(mA)
    power_mW = ina219Car.getPower_mW();                //Power負載功率(mW)
    loadvoltage = busvoltage + (shuntvoltage / 1000);  //Load Voltage負載電壓(V)

    Serial.print(shuntvoltage);
    Serial.print(",");
    Serial.print(busvoltage);
    Serial.print(",");
    Serial.print(current_mA);
    Serial.print(",");
    Serial.println(power_mW);

    //寫入google試算表
    if (busvoltage*current_mA > 0) {
      Serial.println("car:Sheets");
      sendToGoogleSheets("1", URLEncode((String() + "小車消耗能量" + "," + busvoltage*current_mA + "," + interval).c_str()));
    }
  }
}

int HextoRGB(char val) {
  String hex = "0123456789abcdef";
  return hex.indexOf(val);
}

void MatrixLedList(String color) {
  color.replace("#", "");
  uint32_t R, G, B;
  for (int i = 0; i < (color.length() / 6); i++) {
    matrixString[i * 6 + 0] = color[i * 6 + 0];
    matrixString[i * 6 + 1] = color[i * 6 + 1];
    matrixString[i * 6 + 2] = color[i * 6 + 2];
    matrixString[i * 6 + 3] = color[i * 6 + 3];
    matrixString[i * 6 + 4] = color[i * 6 + 4];
    matrixString[i * 6 + 5] = color[i * 6 + 5];
    R = (HextoRGB(color[i * 6 + 0]) * 16 + HextoRGB(color[i * 6 + 1]));
    G = (HextoRGB(color[i * 6 + 2]) * 16 + HextoRGB(color[i * 6 + 3]));
    B = (HextoRGB(color[i * 6 + 4]) * 16 + HextoRGB(color[i * 6 + 5]));
    pixels.setPixelColor(i, pixels.Color(R, G, B));
  }
  pixels.show();
}

String MatrixLedColorRandom() {
  String s = "0123456789abcdef";
  String color = "#000000";
  int R = random(0, 255);
  int G = random(0, 255);
  int B = random(0, 255);
  int r1 = (R - R % 16) / 16;
  int r2 = R % 16;
  int g1 = (G - G % 16) / 16;
  int g2 = G % 16;
  int b1 = (B - B % 16) / 16;
  int b2 = B % 16;
  color[1] = s[r1];
  color[2] = s[r2];
  color[3] = s[g1];
  color[4] = s[g2];
  color[5] = s[b1];
  color[6] = s[b2];
  return color;
}

void MatrixLedAll(String color) {
  color.replace("#", "");
  for (int i = 0; i < (matrixString.length() / 6); i++) {
    matrixString[i * 6 + 0] = color[0];
    matrixString[i * 6 + 1] = color[1];
    matrixString[i * 6 + 2] = color[2];
    matrixString[i * 6 + 3] = color[3];
    matrixString[i * 6 + 4] = color[4];
    matrixString[i * 6 + 5] = color[5];
    uint32_t R, G, B;
    R = (HextoRGB(color[0]) * 16 + HextoRGB(color[1]));
    G = (HextoRGB(color[2]) * 16 + HextoRGB(color[3]));
    B = (HextoRGB(color[4]) * 16 + HextoRGB(color[5]));
    pixels.setPixelColor(i, pixels.Color(R, G, B));
  }
  pixels.show();
}
