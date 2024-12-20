#include <SoftwareSerial.h>
#include <AdafruitIO_WiFi.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "time.h"

//網路時間
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 8 * 3600;  // UTC+8
const int daylightOffset_sec = 0;

//當天是否已經觸發過拍照
bool plantTriggeredToday = false;  //08:00(植物拍照)
bool trashTriggeredToday = false;  //15:00(垃圾桶拍照)

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

  // 初始化 NTP
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  Serial.println("NTP網路時間同步中...");

  struct tm timeinfo;
  while (!getLocalTime(&timeinfo)) {
    Serial.println("失敗:Failed to obtain time, retry...");
    delay(2000);
  }
  Serial.println("時間同步完成!");
}

void loop() {
  // 維持 Adafruit IO 連線
  io.run();

  //接收訊息：Uno→ESP32
  while (UnoSerial.available()) {
    //UNO軌道移動到垃圾桶or植物前面，傳來開始拍照訊息
    //訊息內容:START_TRASH_CAM,START_PLANT_CAM
    String startCam = UnoSerial.readString();
    Serial.println("From UNO:" + startCam);
    //發佈MQTT通知:ESP32-CAM開始拍照
    controlCam->save(startCam);
  }

  //網路時間
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    delay(1000);
    return;
  }
  int currentHour = timeinfo.tm_hour;
  int currentMinute = timeinfo.tm_min;
  int currentSecond = timeinfo.tm_sec;
  // 處理植物拍照(08:00:00~08:00:05)
  handleTrigger(currentHour, currentMinute, currentSecond, 8, 0, plantTriggeredToday, "plant");
  // 處理垃圾桶拍照(15:00:00~15:00:05)
  handleTrigger(currentHour, currentMinute, currentSecond, 15, 0, trashTriggeredToday, "trash");
  delay(1000);
}

/**
 * handleTrigger: 處理特定時間段(XX:00:00~XX:00:05)的觸發邏輯
 * @param currentHour, currentMinute, currentSecond: 當前時間
 * @param targetHour, targetMinute: 目標觸發小時與分鐘 (e.g., 8, 0)
 * @param triggeredFlag: 參考傳入的flag用於標記當天是否已觸發過
 * @param message: 執行觸發動作時顯示的訊息
 */
void handleTrigger(int currentHour, int currentMinute, int currentSecond,
                   int targetHour, int targetMinute,
                   bool& triggeredFlag, const char* message) {

  // 在 targetHour:targetMinute:00 ~ targetHour:targetMinute:05範圍內，若尚未觸發則執行
  if (currentHour == targetHour && currentMinute == targetMinute && currentSecond <= 5 && !triggeredFlag) {
    Serial.printf("時間 %02d:%02d:%02d，%s\n", currentHour, currentMinute, currentSecond, message);    
    //ESP32→UNO
    //呼叫UNO移動鏡頭，stand by準備拍照
    //訊息內容:STANDBY_TRASH_CAM,STANDBY_PLANT_CAM
    if(message=="plant"){
      UnoSerial.print("STANDBY_PLANT_CAM");
    }else if(message=="trash"){
      UnoSerial.print("STANDBY_TRASH_CAM");
    }    

    triggeredFlag = true;
    // 避免短時間重複觸發
    delay(1000);
  }

  // 當時間超過 targetHour:(targetMinute+1):00 後，即可重置旗標
  // 例如 08:01:00之後重置plantTriggeredToday
  //     15:01:00之後重置trashTriggeredToday
  if (currentHour == targetHour && currentMinute >= (targetMinute + 1) && triggeredFlag) {
    triggeredFlag = false;
    Serial.printf("已過 %02d:%02d，重置flag為false\n", targetHour, targetMinute + 1);
  }
}
