//Generated Date: Tue, 10 Dec 2024 09:46:23 GMT

#include <WiFi.h>
#include <WiFiClientSecure.h>
WiFiClientSecure client;
#include <WiFiClientSecure.h>

char _lwifi_ssid[] = "tyes-itc2";
char _lwifi_pass[] = "xxxxxxxxxx";
void initWiFi() {

  for (int i=0;i<2;i++) {
    WiFi.begin(_lwifi_ssid, _lwifi_pass);

    delay(1000);
    Serial.println("");
    Serial.print("Connecting to ");
    Serial.println(_lwifi_ssid);

    long int StartTime=millis();
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        if ((StartTime+5000) < millis()) break;
    }

    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("");
      Serial.println("STAIP address: ");
      Serial.println(WiFi.localIP());
      Serial.println("");

      break;
    }
  }
}

const char* asId="AKfycbyR-Yp-uu4nIvnjvnkILaQ5AX8yFxp-UpBO-Sqs0su3ai1N_BvQsz_Q";
String sheetId="";
String sheetTag="";

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
  sheetClient.setInsecure();
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
  initWiFi();
  Serial.begin(9600);

  sheetId="xxxxxxxxxxxxx";
  sheetTag=URLEncode("count");
  delay(1000);
  for (int i = 1; i <= 10; i++) {
    sendToGoogleSheets("1",URLEncode((String() + i + "," + "測試" + "," + "abc").c_str()));
    Serial.println(i);
    delay(1000);
  }
  Serial.println("完成");
}

void loop()
{

}
