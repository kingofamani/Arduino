/*
   Generated using BlocklyDuino:

   https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt

   Date: Thu, 12 Nov 2020 02:01:26 GMT
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID "HTCAMANI"
#define STAPSK  "12345678"
#endif
const char* ssid = STASSID;
const char* password = STAPSK;
ESP8266WebServer server(80);
void handleNotFound() {
  server.send(404, "text/plain", "找不到網頁");
}

void handleRoot() {
  server.send(200, "text/plain", "Hello 德音國小!");
}

void WiFiStart() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  //等待WiFi連線
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  //在監控視窗顯示取得的IP
  Serial.println(WiFi.localIP());
  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("Server開啟");
}

void LedOn() {
  //網頁控制關LED
  server.on("/off", []() {
    server.send(200, "text/plain", "LED 熄滅");
    digitalWrite(LED_BUILTIN, HIGH);
  });
}

void LedOff() {
  //網頁控制開LED
  server.on("/on", []() {
    server.send(200, "text/plain", "LED 打開");
    digitalWrite(LED_BUILTIN, LOW);
  });
}

void setup()
{
  Serial.begin(115200);

  WiFiStart();
  LedOn();
  LedOff();
  pinMode(LED_BUILTIN, OUTPUT);
}


void loop()
{
  server.handleClient();
  MDNS.update();
}
