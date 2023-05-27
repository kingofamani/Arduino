/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Sun, 11 Dec 2022 13:03:00 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include <Tone32.h>
#include <WiFiClient.h>
#include "time.h"
#include <WiFi.h>

char timeDate[21];
const char* ntpServer = "asia.pool.ntp.org";
const long  gmtOffset_sec = 28800;
const int   daylightOffset_sec = 60000;
const char* resource = "/trigger/esp32google/with/key/xxxxxxxxxxxxxxxxxxx";
const char* server = "maker.ifttt.com";
int BUZZER_PIN = 4;

int BUZZER_CHANNEL = 0;

int BUZZER_FRE = 630;

int BUZZER_TIME = 1000;

char _lwifi_ssid[] = "AMANI-4G-Home2";
char _lwifi_pass[] = "xxxxxxxxxxxxxxxxx";
void tone32(int BUZZER_PIN, int BUZZER_FRE, int BUZZER_TIME) {
  tone(BUZZER_PIN, BUZZER_FRE, BUZZER_TIME,BUZZER_CHANNEL);
  noTone(BUZZER_PIN,BUZZER_CHANNEL);
}

void printLocalTime() {
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
  Serial.println("Failed to obtain time");
  return;
  }
  strftime(timeDate,21, "%b %d %Y %H:%M:%S", &timeinfo);
  Serial.println(&timeinfo);
}

void makeIFTTTRequest() {
  Serial.print("Connecting to ");
  Serial.print(server);
  WiFiClient client;
  int retries = 5;
  while(!!!client.connect(server, 80) && (retries-- > 0)) {
  Serial.print(".");
  }
  Serial.println();
  if(!!!client.connected()) {
  Serial.println("Failed to connect...");
  }
  //Serial.print("Request resource: ");
  //Serial.println(resource);
  //傳至IFTTT參數
  //要去掉1個反斜線
  String jsonObject = String("{\\"value1\\":\\"") +timeDate + "\\",\\"value2\\":\\"" + 1 + "\\"}";
  client.println(String("POST ") + resource + " HTTP/1.1");
  client.println(String("Host: ") + server);
  client.println("Connection: close");
  client.println("Content-Type: application/json");
  client.print("Content-Length: ");
  client.println(jsonObject.length());
  client.println();
  client.println(jsonObject);
  int timeout = 5 * 10; // 5 seconds
  while(!!!client.available() && (timeout-- > 0)){
  delay(100);
  }
  if(!!!client.available()) {
  Serial.println("No response...");
  }
  while(client.available()){
  Serial.write(client.read());
  }
  //Serial.println("closing connection");
  client.stop();
}

void setup()
{
  Serial.begin(115200);

  WiFi.disconnect();
  WiFi.softAPdisconnect(true);
  WiFi.mode(WIFI_STA);
  WiFi.begin(_lwifi_ssid, _lwifi_pass);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }
  delay(300);
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}


void loop()
{
  //IFTTT URL resource

tone32(BUZZER_PIN, BUZZER_FRE, BUZZER_TIME);
  Serial.println(analogRead(39));
  if (analogRead(39) > 4000) {
    Serial.println("電擊到蚊子，上傳google試算表儲存中…");
    printLocalTime();
    makeIFTTTRequest();
    delay(1000);
  } else {
    Serial.println("沒有蚊子");
  }
  delay(1000);
}