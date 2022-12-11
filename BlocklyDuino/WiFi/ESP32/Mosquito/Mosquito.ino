/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Sun, 11 Dec 2022 13:01:27 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include <Tone32.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>

int BUZZER_PIN = 4;

int BUZZER_CHANNEL = 0;

int BUZZER_FRE = 400;

int BUZZER_TIME = 100;

char _lwifi_ssid[] = "AMANI-4G-Home2";
char _lwifi_pass[] = "xxxxxxxxxxxxxxxxx";
const char* asId="AKfycbyR-Yp-uu4nIvnjvnkILaQ5AX8yFxp-UpBO-Sqs0su3ai1N_BvQsz_Q";
String sheetId="";
String sheetTag="";

void tone32(int BUZZER_PIN, int BUZZER_FRE, int BUZZER_TIME) {
  tone(BUZZER_PIN, BUZZER_FRE, BUZZER_TIME,BUZZER_CHANNEL);
  noTone(BUZZER_PIN,BUZZER_CHANNEL);
}

String URLEncode(const char* msg)
{
  const char *hex = "0123456789abcdef";
  String encodedMsg = "";
  while (*msg!='\0'){
      if( ('a' <= *msg && *msg <= 'z')
              || ('A' <= *msg && *msg <= 'Z')
              || ('0' <= *msg && *msg <= '9') ) {
          encodedMsg += *msg;
      } else {
          encodedMsg += '%';
          encodedMsg += hex[*msg >> 4];
          encodedMsg += hex[*msg & 15];
      }
      msg++;
  }
  return encodedMsg;
}

void  sendToGoogleSheets(const String& dateInclude,const String& data)
{
  static WiFiClientSecure sheetClient;
  const char* host="script.google.com";
  if (sheetClient.connect(host, 443)) {
      const String url = String() +"https://"+host+"/macros/s/"+asId+"/exec?type=insert&dateInclude="+dateInclude+"&sheetId="+sheetId+"&sheetTag="+sheetTag+"&data="+data;
      sheetClient.println("GET " + url + " HTTP/1.1");
      sheetClient.println(String()+"Host: "+host);
      sheetClient.println("Accept: */*");
      sheetClient.println("Connection: close");
      sheetClient.println();
      sheetClient.println();
      sheetClient.stop();
  }
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
  sheetId="xxxxxxxxxxxxxxxxxxxxxxxxxx";
  sheetTag=URLEncode("count");
  delay(1000);
}


void loop()
{
  tone32(BUZZER_PIN, BUZZER_FRE, BUZZER_TIME);
  Serial.println(analogRead(39));
  if (analogRead(39) < 1500) {
    Serial.println("電擊到蚊子，上傳google試算表儲存中…");
    sendToGoogleSheets("1",URLEncode((String() + "有蚊子1隻").c_str()));
    delay(1000);
  } else {
    Serial.println("沒有蚊子");
  }
  delay(10);
}