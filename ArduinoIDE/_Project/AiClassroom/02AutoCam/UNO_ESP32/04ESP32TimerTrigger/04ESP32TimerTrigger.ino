#include <WiFi.h>
#include "time.h"

const char* ssid     = "tyes-itc2";
const char* password = "xxxxxxxxxxxxxx";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 8 * 3600; // UTC+8
const int   daylightOffset_sec = 0;

const int LED_PIN = 2;  

// 兩個旗標：
// plantTriggeredToday：08:00是否已經觸發過(植物拍照)
// trashTriggeredToday：15:00是否已經觸發過(垃圾桶拍照)
bool plantTriggeredToday = false;
bool trashTriggeredToday = false;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  
  // 連接 WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");

  // 初始化 NTP
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  Serial.println("NTP time sync in progress...");
  
  struct tm timeinfo;
  while (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time, retry...");
    delay(2000);
  }
  Serial.println("Time synced!");
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
                   bool &triggeredFlag, const char* message) {
  
  // 在 targetHour:targetMinute:00 ~ targetHour:targetMinute:05範圍內，若尚未觸發則執行
  if (currentHour == targetHour && currentMinute == targetMinute && currentSecond <= 5 && !triggeredFlag) {
    Serial.printf("時間 %02d:%02d:%02d，%s\n", currentHour, currentMinute, currentSecond, message);
    digitalWrite(LED_PIN, HIGH);
    // 在此可呼叫拍照程式，如: takePhotoForPlant() or takePhotoForTrash()
    triggeredFlag = true;
    // 避免短時間重複觸發
    delay(1000); 
  }

  // 當時間超過 targetHour:(targetMinute+1):00 後，即可重置旗標
  // 例如 08:01:00之後重置plantTriggeredToday
  //     15:01:00之後重置trashTriggeredToday
  if (currentHour == targetHour && currentMinute >= (targetMinute+1) && triggeredFlag) {
    triggeredFlag = false;
    Serial.printf("已過 %02d:%02d，重置flag為false\n", targetHour, targetMinute+1);
  }
}

void loop() {
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
  handleTrigger(currentHour, currentMinute, currentSecond, 8, 16, plantTriggeredToday, "觸發植物拍照");
  
  // 處理垃圾桶拍照(15:00:00~15:00:05)
  handleTrigger(currentHour, currentMinute, currentSecond, 8, 18, trashTriggeredToday, "觸發垃圾桶拍照");

  delay(1000);
}
