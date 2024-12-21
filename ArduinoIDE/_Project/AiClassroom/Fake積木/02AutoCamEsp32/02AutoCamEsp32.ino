//Generated Date: Sat, 21 Dec 2024 03:19:21 GMT

#define WIFI_SSID "tyes-itc2"

#define WIFI_PASS "xxxxxxxxxx"

#define IO_USERNAME "user"

#define IO_KEY "xxxxxxxxxx"

#include <AdafruitIO_WiFi.h>
#include <WiFi.h>
#include "time.h"
#include <SoftwareSerial.h>
SoftwareSerial softSerial(16, 17);

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 28800;
const int   daylightOffset_sec = 0;
struct tm timeinfo;
int currentTimeValue[6] = {0,0,0,0,0,0};
String currentTime[3] = {"","",""};

void getNtpTime() {
  if(!getLocalTime(&timeinfo)){
    return;
  }
  currentTimeValue[0] = timeinfo.tm_year+1900;
  currentTimeValue[1] = timeinfo.tm_mon+1;
  currentTimeValue[2] = timeinfo.tm_mday;
  currentTimeValue[3] = timeinfo.tm_hour;
  currentTimeValue[4] = timeinfo.tm_min;
  currentTimeValue[5] = timeinfo.tm_sec;
  currentTime[0] = String(timeinfo.tm_year+1900)+"/"+ ((timeinfo.tm_mon+1)<10?"0":"") + String(timeinfo.tm_mon+1)+"/"+(timeinfo.tm_mday<10?"0":"")+String(timeinfo.tm_mday);
  currentTime[1] = (timeinfo.tm_hour<10?"0":"")+String(timeinfo.tm_hour)+":"+(timeinfo.tm_min<10?"0":"")+String(timeinfo.tm_min)+":"+(timeinfo.tm_sec<10?"0":"")+String(timeinfo.tm_sec);
  currentTime[2] = currentTime[0] + " "+ currentTime[1];
}

AdafruitIO_Feed *feedName1734750798765 = io.feed("control-cam");
void handleTrigger(int targetHour, boolean targetMinute, const char* message) {
  if (targetHour == (currentTimeValue[3]) && targetMinute == (currentTimeValue[4])) {
    //1、通知UNO，移動軌道，準備拍照
    if (message == "plant") {
      softSerial.print("STANDBY_PLANT_CAM");
    } else if (message == "trash") {
      softSerial.print("STANDBY_TRASH_CAM");
    }
  }
}

void setup()
{
  softSerial.begin(9600);
  delay(10);
  Serial.begin(9600);

  io.connect();
while (io.status() < AIO_CONNECTED) {
  delay(500);
}
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);


}

void loop()
{

    io.run();
    //每日定時拍照:植物(08:00:00)
  handleTrigger(8, 0, "plant");
  //每日定時拍照:垃圾桶(15:00:00)
  handleTrigger(15, 0, "trash");
  //2、UNO回傳通知:已完成軌道移動
  if (softSerial.available()) {
    String serialMsg = "";
    while (softSerial.available()) {
      serialMsg = softSerial.readString();
      //3、透過MQTT通知ESP32-CAM拍照(訊息內容:START_TRASH_CAM,START_PLANT_CAM)
    feedName1734750798765->save((serialMsg));
    }
  }
}
