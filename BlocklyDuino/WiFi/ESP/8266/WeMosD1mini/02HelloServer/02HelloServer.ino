/*
   Generated using BlocklyDuino:

   https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt

   Date: Thu, 12 Nov 2020 01:29:45 GMT
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

void setup()
{
  Serial.begin(115200);

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


void loop()
{
  server.handleClient();
  MDNS.update();
}
