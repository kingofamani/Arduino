//Generated Date: Thu, 14 Sep 2023 02:16:55 GMT

#include <WiFi.h>
#include <WiFiClientSecure.h>

String lineToken="";

char _lwifi_ssid[] = "AMANI-4G-Home";
char _lwifi_pass[] = "c41585c41585";
void sendLineMsg(String myMsg) {
  static WiFiClientSecure line_client;
  line_client.setInsecure();
  myMsg.replace("%","%25");
  myMsg.replace("&","%26");
  myMsg.replace("§","&");
  myMsg.replace("\\n","\n");
  if (line_client.connect("notify-api.line.me", 443)) {
    line_client.println("POST /api/notify HTTP/1.1");
    line_client.println("Connection: close");
    line_client.println("Host: notify-api.line.me");
    line_client.println("Authorization: Bearer " + lineToken);
    line_client.println("Content-Type: application/x-www-form-urlencoded");
    line_client.println("Content-Length: " + String(myMsg.length()));
    line_client.println();
    line_client.println(myMsg);
    line_client.println();
    line_client.stop();
  }
  else {
    Serial.println("Line Notify failed");
  }
}

void setup()
{
  Serial.begin(9600);

  lineToken="LwsLOAq+3nAeK/77hMLPJnqv0WBpOO1/Vj+3F1rjrq0IAgNY+BydhBUm7UXYOEzF8ztpm7wwiCGv015sLALe9bWxqyQx7St58KdfGXYdvZte8wXqoeEUACPicOrGJgSuGuhtmw5KH1wBjHycskhWDAdB04t89/1O/w1cDnyilFU=";
  WiFi.disconnect();
  WiFi.softAPdisconnect(true);
  WiFi.mode(WIFI_STA);
  WiFi.begin(_lwifi_ssid, _lwifi_pass);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }
  delay(300);
  Serial.println(WiFi.localIP().toString());
  sendLineMsg(String("message=\n")+"test");
  Serial.println("\n");
  Serial.println("OK");
}

void loop()
{

}
