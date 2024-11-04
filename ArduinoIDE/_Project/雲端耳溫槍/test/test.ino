#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include "secrets.h"
#include "RC522.h"
#include <SPI.h>
#include <Adafruit_MLX90614_2.h>
#include "U8glib.h"

String data1 = "";

//Doit連接id及key
char uid[] = SECRET_UID;
char key[] = SECRET_KEY;

//腳位
const byte BTN_INIT = 5;
const byte BTN_SEND = 7;
const byte LED_REMOTE_CONTROL = 6;
const byte LED_SEND_TO_REMOTE = 2;
const byte LED_INIT = 3;
//byte value;

//Interval cmd keep
unsigned long previousMillis  = 0;
unsigned long currentMillis   = 0;
//Interval 體溫
unsigned long previousMillis2  = 0;
unsigned long currentMillis2   = 0;

//RFID卡號
unsigned char serNum[5];
String stringID = "";//將卡號轉成8碼字串

//LCD顯示器
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE); // I2C / TWI ;

//紅外線人體溫度計
Adafruit_MLX90614_2 mlx = Adafruit_MLX90614_2();
float tmax = 0.00;//單次測得最高溫
const float WARNING_TEMPERATURE = 37.5;//高溫警示
float ambientTemperature = 0.00;//環境溫度
const float A_T_OFFSET = 3.00;//環境校正溫度。當測量體度>環境溫度+環境校正溫度時，表示已測量體度。
const int A_T_SECOND = 2000;//偵測2秒後，將值寫入環境溫度，會比較準確
bool IS_GET_A_T = false;//是否已取得環境溫度

//蜂嗚器腳位
const int BUZZER = 4;

//量體溫整體流程
const int STEP_CARD = 0;
const int STEP_TEMPERATURE = 1;
const int STEP_REQUEST = 2;
const int STEP_RESPONSE = 3;
bool theStep[] = {false, false, false, false}; //{是否感應卡片,是否量過體溫,是否送出資料,是否收到回傳訊息}


void setup()
{
  Serial.begin(9600);
  Serial.setTimeout(3000); // 根據本案例感測模組送出一筆資料的耗費時間上限
  //randomSeed(analogRead(0));

  //Button, LED
  pinMode(BTN_INIT, INPUT);
  pinMode(BTN_SEND, INPUT);
  pinMode(LED_INIT, OUTPUT);
  pinMode(LED_SEND_TO_REMOTE, OUTPUT);
  pinMode(LED_REMOTE_CONTROL, OUTPUT);

  //蜂嗚器
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, HIGH);

  //人體體溫校正係數
  mlx.multi = .02;
  mlx.offset = 271.70;/*273.15為沒有補償的標準值,數字改小顯示溫度增加*/
  mlx.begin();

  //取得環境溫度
  getAmbientTemperature();

  //WiFi  subscribe 才能從 Doit遠端控制Arduino LED燈
  //subscribe和Arduino傳資料至遠端DB無關，沒有subscribe也可以
  subscribe();

  //RFID初始
  SPI.begin();
  pinMode(chipSelectPin, OUTPUT); // Set digital pin 10 as OUTPUT to connect it to the RFID /ENABLE pin
  digitalWrite(chipSelectPin, LOW); // Activate the RFID reader
  pinMode(NRSTPD, OUTPUT); // Set digital Reset , Not Reset and Power-down
  MFRC522_Init();

  //清空緩衝器
  Serial.flush();
  while (Serial.read() >= 0) {};

}
void loop()
{
  //Serial.print("before:");
  //Serial.println(data1.length());

  //人體體溫記錄
  myTemperature();

  //LCD顯示溫度
  u8g.firstPage();
  do {
    draw();
  } while ( u8g.nextPage() );
  delay(100);

  //重新subscribe
  if (digitalRead(BTN_INIT) == 1) {
    digitalWrite(LED_INIT, HIGH);
    subscribe();
    delay(100);
  } else {
    digitalWrite(LED_INIT, LOW);
    delay(100);
  }



  //接收回傳字串
  while (Serial.available()) {
    char c = Serial.read();
    //Serial.print(c);
    if (c != '\n') {
      data1 += c;
    }
    delay(5);    // 沒有延遲的話 UART 串口速度會跟不上Arduino的速度，會導致資料不完整
  }
  //data1.replace("cmd=keep&res=1","");//keep回傳值不收
  //data1.replace("cmd=publish&res=1","");//publish回傳值不收




  /*readString()不好用，容易丟失數據
    if (Serial.available() > 0)
    {

    delay(100);//★等待100ms保證數據接收完畢
    if(Serial.readString()!="cmd=keep&res=1")//keep回傳值不收，以免和其他回傳值打架
    {
    data1 = Serial.readString();
    }
    }
  */


  //處理回傳命令
  if (data1.indexOf("LEDon") > 0)
  {
    //Serial.println("LED ON");
    digitalWrite(LED_REMOTE_CONTROL, HIGH);
  }
  if (data1.indexOf("LEDoff") > 0)
  {
    //Serial.println("LED OFF");
    digitalWrite(LED_REMOTE_CONTROL, LOW);
  }

  //清空緩衝器
  if (data1 != "") {
    //Serial.println(data1);//★不要print data1至Serial，否則會重復出現，反覆傳送↔接送，誤以為data1值沒有清空
    //Serial.println("接收到資料");
    data1 = "";
  }
  Serial.flush();
  while (Serial.read() >= 0) {};


  //啟動RFID
  listenRFID();
  //螢幕顯示卡號
  /*
    do {
    drawCardID(stringID);
    } while ( u8g.nextPage() );
    delay(1000);
  */

  //上傳溫度
  theStep[STEP_CARD] = bool(stringID.length() > 0);
  theStep[STEP_TEMPERATURE] = bool(tmax > ambientTemperature + A_T_OFFSET);
  if (theStep[STEP_CARD] && theStep[STEP_TEMPERATURE]) {
    //Serial.println("ready");
    digitalWrite(LED_SEND_TO_REMOTE, HIGH);
    //傳資料至遠端DB
    sendToServer();
  } else {
    //Serial.println("not ready");
    digitalWrite(LED_SEND_TO_REMOTE, LOW);
  }


  /*
    //Btn傳資料至遠端db
    byte value = digitalRead(BTN_SEND);
    // Serial.println(value);
    if (value == 1) {
      digitalWrite(LED_SEND_TO_REMOTE, HIGH);
      delay(500);
      sendToServer();
    } else {
      digitalWrite(LED_SEND_TO_REMOTE, LOW);
      delay(500);
    }
  */

  //每隔30秒發一次心跳包 (閒置一段時間會離線，要重新subscribe)
  timeInterval(30000);

}

void sendToServer() {
  Serial.print("cmd=upload&device_name=arduino&data=");
  //data格式：5碼溫度(23.56度)+8碼RFID碼
  //    Serial.print(random(1000));
  Serial.print(tmax);
  Serial.print(stringID);
  //Serial.print(random(100000));
  //Serial.print(random(100000));
  Serial.print("&uid=");
  Serial.print(uid);
  Serial.print("&key=");
  Serial.println(key);
  Serial.flush();
  delay(100);

  buzzer(80);

  Initialization();//變數回復初始值，等待下一個學生
}

void Initialization() {
  bool theStep[] = {false, false, false, false};
  stringID = "";
  tmax = 0.00;
  IS_GET_A_T  = false;
  delay(5);
  getAmbientTemperature();
}

void subscribe() {
  //byte subs = "cmd=subscribe&topic="+uid;
  //delay(100);
  Serial.print("cmd=subscribe&topic=");
  Serial.println(uid);
  delay(1000);
}

void getAmbientTemperature() {
  ambientTemperature = 0.00;
  if (!IS_GET_A_T) {
    delay(A_T_SECOND);
    ambientTemperature = mlx.readObjectTempC();
    IS_GET_A_T = true;
  }
}

void myTemperature() {
  timeInterval2(3000);
}

//cmd keep計時
void timeInterval(int interval) {
  currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    //Serial.println("cmd=keep");
    previousMillis = currentMillis;
  }
}

//量體溫計時
void timeInterval2(int interval) {
  currentMillis2 = millis();
  if (currentMillis2 - previousMillis2 >= interval) {
    float tempC = mlx.readObjectTempC();
    if (tmax < tempC) {
      tmax = tempC;
    }

    //真正量到體溫才顯示
    theStep[STEP_TEMPERATURE] = bool(tmax > ambientTemperature + A_T_OFFSET);
    if (theStep[STEP_TEMPERATURE]) {
      //buzzer(80);
      Serial.print("體溫:");
      Serial.println(tmax);
      //高溫警告
      highTempertureWarning(tempC, WARNING_TEMPERATURE);
    }
    //init
    previousMillis2 = currentMillis2;

  }
}

void listenRFID() {
  unsigned char status;
  unsigned char str[MAX_LEN];

  // Search card, return card types
  status = MFRC522_Request(PICC_REQIDL, str);
  if (status == MI_OK)      //读取到ID卡时候
  {
    
    // Show card type
    //ShowCardType(str);

    //Prevent conflict, return the 4 bytes Serial number of the card
    status = MFRC522_Anticoll(str);

    // str[0..3]: serial number of the card
    // str[4]: XOR checksum of the SN.
    if (status == MI_OK)
    {
      memcpy(serNum, str, 5);
      Serial.print("ID:");
      ShowCardID(serNum);

      unsigned char* id = serNum;
      //卡號轉在8碼字串(方便傳至DB)
      stringID = "";
      for (byte i = 0; i < 4; i++) {
        if (id[i] < 10) {
          stringID += "0";
          stringID += String(id[i]);
        } else {
          stringID += String(id[i], HEX);
        }
      }
      stringID.toUpperCase();
      //Serial.println(stringID);
      buzzer(80);

      /*
        // Check people associated with card ID
        //unsigned char* id = serNum;
        if ( id[0] == 0x7A && id[1] == 0xED && id[2] == 0xED && id[3] == 0x6E )
        {
          Serial.println("The Host 1!");
        }
        else if (id[0] == 0x33 && id[1] == 0x1A && id[2] == 0xD7 && id[3] == 0x04)
        {
          Serial.println("The Host 2!");
        }
        else
        {
          Serial.println("Stranger!");
        }
      */
    }
  }
  MFRC522_Halt(); //command the card into sleep mode
  delay(100);
}

void draw(void) {
  u8g.setFont(u8g_font_fur25);
  u8g.setPrintPos(10, 29);
  u8g.print(mlx.readObjectTempC(), 1);
  u8g.drawStr( 80, 29, "\260C");
  u8g.setPrintPos(10, 63);
  u8g.print(tmax, 1);
  u8g.drawStr( 80, 63, "\260C");
}


void drawCardID(String strID) {
  u8g.setFont(u8g_font_fur25);
  u8g.drawStr( 10, 46, strID.c_str());//String 轉 char *s
}

void highTempertureWarning(float tempC, float highTemp) {
  if (tempC > highTemp)/*到達溫度蜂鳴器鳴叫*/
  {
    buzzer(80);
  }
  else
  {
    digitalWrite(BUZZER, HIGH);
  }
}

void buzzer(int secs) {
  for (int i = 0; i < secs; i++)
  {
    digitalWrite(BUZZER, LOW);
    delay(1);
    digitalWrite(BUZZER, HIGH);
    delay(1);
  }
  digitalWrite(BUZZER, HIGH);
}
