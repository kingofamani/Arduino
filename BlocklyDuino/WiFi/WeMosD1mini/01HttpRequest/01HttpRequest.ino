/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Tue, 10 Nov 2020 00:07:35 GMT
 */

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

String payload;

const char* ssid = "HTCAMANI";
const char* password = "12345678";

void setup()
{
  Serial.begin(9600);

  Serial.print("連線中");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {delay(500);Serial.print("."); }
  Serial.println("OK成功");
}


void loop()
{
  if(WiFi.status()== WL_CONNECTED){
  HTTPClient http;
  http.begin("http://jsonplaceholder.typicode.com/users/1");
  int httpCode = http.GET();
  if (httpCode > 0) {
  // 刪除程式碼：
  // payload=0;
  payload = 0;
  payload = http.getString();
  Serial.println(payload);
  }
  http.end();
  } else {
  Serial.println("WiFi取得資料失敗");
  }
  delay(30000);
}