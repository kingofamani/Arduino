/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Thu, 12 Nov 2020 03:59:35 GMT
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <DHT.h>

float tem;

float hum;

#ifndef STASSID
#define STASSID "HTCAMANI"
#define STAPSK  "12345678"
#endif
const char* ssid = STASSID;
const char* password = STAPSK;
ESP8266WebServer server(80);
void pageDHT() {
  server.on("/a1", []() {
  server.send(200, "text/plain", "【網頁顯示的文字】");
  //在此控制馬達、燈泡等…
  });
}

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

DHT dht11_p8(8, DHT11);
void sersorDHT() {
  tem = dht11_p8.readTemperature();
  hum = dht11_p8.readHumidity();
  Serial.print("溫度：");
  Serial.println(tem);
  Serial.print("濕度：");
  Serial.println(hum);
  delay(5000);
}

void _E3_80_90_E8_87_AA_E5_B7_B1_E6_89_93_E5_87_BD_E6_95_B8_E5_90_8D_E7_A8_B1_E3_80_912() {
  server.on("/【自己命名英文網址】", []() {
  server.send(200, "text/plain", "【網頁顯示的文字】");
  //在此控制馬達、燈泡等…
  });
}

void setup()
{
  Serial.begin(115200);

  WiFiStart();
  dht11_p8.begin();
}


void loop()
{
  server.handleClient();
  MDNS.update();
sersorDHT();

}