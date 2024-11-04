//Generated Date: Mon, 16 Oct 2023 02:50:57 GMT

#include <WiFi.h>
#define ARDUINOJSON_DECODE_UNICODE 1
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>

char _lwifi_ssid[] = "tyes-itc";
char _lwifi_pass[] = "xxxxxxxxxxxxxxx";
const char* asId="AKfycbyR-Yp-uu4nIvnjvnkILaQ5AX8yFxp-UpBO-Sqs0su3ai1N_BvQsz_Q";
String sheetId="";
String sheetTag="";

DynamicJsonDocument docSheet(2048);

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

void searchSheet(const String& fname, const String& sname){
  static WiFiClientSecure sheetClient;
  sheetClient.setInsecure();
  const char* host="script.google.com";
  String newUrl="";
  sheetClient.connect(host, 443);
  while (!sheetClient.connected());
  const String url = String() +"https://"+host+"/macros/s/"+asId+"/exec?type=search&sheetId="+sheetId+"&sheetTag="+sheetTag+"&fname="+fname+"&sname="+sname;
  sheetClient.print("GET " + url + " HTTP/1.1\n"+String()+"Host: "+host+"\nAccept: */*\nConnection: close\n\n\n");
  while (!newUrl.startsWith("https:")){
    newUrl = sheetClient.readStringUntil('\n');
    if (newUrl.startsWith("Location: https://")) {
      newUrl.replace("Location: ","");
      break;
    }
  }
  sheetClient.stop();
  String jsonData ="";
  sheetClient.connect(host, 443);
  while (!sheetClient.connected());
  sheetClient.print("GET " + newUrl + " HTTP/1.1\n"+String()+"Host: "+host+"\nAccept: */*\nConnection: close\n\n\n");
  while(!jsonData.startsWith("{")){
    jsonData = sheetClient.readStringUntil('\n');
    if (jsonData.startsWith("{")) {
      DeserializationError error = deserializeJson(docSheet, jsonData);
      break;
    }
  }
  sheetClient.stop();
}

void setup()
{
  Serial.begin(9600);

  WiFi.disconnect();
  WiFi.softAPdisconnect(true);
  WiFi.mode(WIFI_STA);
  WiFi.begin(_lwifi_ssid, _lwifi_pass);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }
  delay(300);
  sheetId="xxxxxxxxxxxxxxxxxxx";
  sheetTag=URLEncode("count");
  searchSheet("B",URLEncode(String("王小明").c_str()).c_str());
  Serial.println((String("時間：")+String(docSheet["A"].as<String>())+String("。姓名：")+String(docSheet["B"].as<String>())+String("。其他：")+String(docSheet["C"].as<String>())));
}

void loop()
{

}
