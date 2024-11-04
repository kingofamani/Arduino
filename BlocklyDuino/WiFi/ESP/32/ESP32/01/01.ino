//Generated Date: Thu, 14 Sep 2023 00:12:33 GMT

#include <WiFi.h>

char _lwifi_ssid[] = "AMANI-4G-Home";
char _lwifi_pass[] = "c41585c41585";

void setup()
{
  Serial.begin(9600);

  WiFi.disconnect();
  WiFi.softAPdisconnect(true);
  WiFi.mode(WIFI_STA);
  WiFi.begin(_lwifi_ssid, _lwifi_pass);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }
  delay(300);
  Serial.println(WiFi.localIP().toString());
}

void loop()
{
  Serial.println("ok");
  delay(1000);
}
