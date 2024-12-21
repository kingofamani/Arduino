//Generated Date: Sat, 21 Dec 2024 01:42:05 GMT

#define WIFI_SSID "tyes-itc2"

#define WIFI_PASS "xxxxxxxx"

#define IO_USERNAME "kingofamani"

#define IO_KEY "xxxxxxxx"

#include <AdafruitIO_WiFi.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <SoftwareSerial.h>
SoftwareSerial softSerial(16, 17);

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
const char* asId="AKfycbyR-Yp-uu4nIvnjvnkILaQ5AX8yFxp-UpBO-Sqs0su3ai1N_BvQsz_Q";
String sheetId="";
String sheetTag="";

String name[3] = String("風扇")+String("電燈")+String("冷氣");
AdafruitIO_Feed *feedName_1734744157718 = io.feed("control-device");
void handleMessage_1734744157718(AdafruitIO_Data *data) {
  //收到MQTT電器控制（例如fan,1）→訊息傳至UNO版
  softSerial.print(data->value());
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
  softSerial.begin(9600);
  delay(10);
  Serial.begin(9600);

  io.connect();
while (io.status() < AIO_CONNECTED) {
  delay(500);
}
  sheetId="1HJXiuubfE-B5BDcYbafIpWQZklJnijVfdYzurXO4LDc";
  sheetTag=URLEncode("sensor");
  feedName_1734744157718->onMessage(handleMessage_1734744157718);
}

void loop()
{

    io.run();
    //收到UNO資料
  if (softSerial.available()) {
    String serialMsg = "";
    while (softSerial.available()) {
      serialMsg = softSerial.readString();
      //收到風扇,電燈,冷氣的耗電量
    String mWhs[3] = {(serialMsg)};
    for (int i = 1; i <= 3; i++) {
      sendToGoogleSheets("1",URLEncode((String() + "國小A" + "," + "601" + "," + (name[i]) + "," + 1 + "," + (mWhs[i])).c_str()));
    }
    }
  }
}
