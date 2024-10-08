//Generated Date: Tue, 08 Oct 2024 05:28:13 GMT

#include <WiFi.h>
#include <WiFiClientSecure.h>
// Line Push API
const char* line_host = "api.line.me";
const char* line_url = "/v2/bot/message/push";
const char* line_token = "xxxxxx";
const char* line_userid = "xxxxxx";
void pushLineMessage(String line_msg) {
  WiFiClientSecure line_client;
  line_client.setInsecure();
  if (!line_client.connect(line_host, 443)) {
    Serial.println("line連接失敗");
    return;
  }
  String payload = "{\"to\": \"" + String(line_userid) + "\",\"messages\": [{\"type\": \"text\", \"text\": \"" + line_msg + "\"}]}";
  String request = String("POST ") + line_url + " HTTP/1.1\r\n" +
                   "Host: " + line_host + "\r\n" +
                   "Authorization: Bearer " + line_token + "\r\n" +
                   "Content-Type: application/json\r\n" +
                   "Content-Length: " + payload.length() + "\r\n" +
                   "\r\n" + payload;
  line_client.print(request);
}

char _lwifi_ssid[] = "xxxxxx";
char _lwifi_pass[] = "xxxxxx";

void setup()
{
  Serial.begin(9600);

  WiFi.disconnect();
  WiFi.softAPdisconnect(true);
  WiFi.mode(WIFI_STA);
  WiFi.begin(_lwifi_ssid, _lwifi_pass);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }
  delay(300);
  Serial.println("ok");
  pushLineMessage("Hello World");
  Serial.println("line ok");
}

void loop()
{

}
