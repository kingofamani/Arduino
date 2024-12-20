#include <SoftwareSerial.h>
#include <AdafruitIO_WiFi.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>

//連接Arduino Uno
SoftwareSerial UnoSerial(16, 17);

// Adafruit IO 帳號資訊
#define IO_USERNAME "kingofamani"
#define IO_KEY "xxxxxxxxxxxxxx"

// WiFi 設定
#define WIFI_SSID "tyes-itc2"
#define WIFI_PASS "xxxxxxxxxxxxxx"

// 建立 Adafruit IO 物件
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// 定義訂閱的 Feed
AdafruitIO_Feed* controlCam = io.feed("control-cam");

void setup() {
  UnoSerial.begin(9600);
  delay(10);
  Serial.begin(9600);  

  // 連接至 Adafruit IO
  Serial.print("連接至 Adafruit IO...");
  io.connect();

  // 等待連接成功
  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("MQTT連接成功");
  //controlCam->save("TEST");
}

void loop() {
  // 維持 Adafruit IO 連線
  io.run();

  //接收訊息：Uno→ESP32
  while (UnoSerial.available()) {
    //UNO軌道移動到垃圾桶or植物前面，傳來開始拍照訊息
    //訊息內容:START_TRASH_CAM,START_PLANT_CAM
    String startCam = UnoSerial.readString(); 
    Serial.println("From UNO:"+startCam);    

    //發佈MQTT通知:ESP32-CAM開始拍照
    controlCam->save(startCam); 
  }
  
}


