#include <WiFi.h>
#include <WiFiClientSecure.h>

// 定義地圖大小
const int numRows = 4;
const int numCols = 6;
String strMaps="";

//WIFI
char _lwifi_ssid[] = "AMANI-4G-Home";
char _lwifi_pass[] = "xxxxxxxxxxxxxxxxxxx";
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

void setup() {
  //WIFI
  WiFi.disconnect();
  WiFi.softAPdisconnect(true);
  WiFi.mode(WIFI_STA);
  WiFi.begin(_lwifi_ssid, _lwifi_pass);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }
  delay(300);

  //按佈置完成鈕
  int pushBtn = 1;
  if(pushBtn==1){
    getMaps();
    googlgSheet();
  }

}

void loop() {
  

}

void getMaps(){
  //磁簧開關
  int switchs[numRows*numCols]={1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1};
  int count = 0;
  for (int i = 0; i < numRows+numCols; i++) {
    strMaps += switchs[i]+",";
  }
}

void googlgSheet{}{
 
  sheetId="xxxxxxxxxxxxxxxxxxxxxxxx";
  sheetTag=URLEncode("count");//工作表
  delay(1000);
  sendToGoogleSheets("1",URLEncode((String() + strMaps).c_str()));
  Serial.println("完成");
}

