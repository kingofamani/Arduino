//Generated Date: Sat, 21 Dec 2024 04:37:18 GMT

#include <WiFi.h>
#include <WiFiClientSecure.h>
WiFiClientSecure client;
#include <Wire.h>
#include <INA226_WE.h>

#define I2C_ADDRESS 0x40

/* There are several ways to create your INA226 object:
 * INA226_WE ina226 = INA226_WE(); -> uses I2C Address = 0x40 / Wire
 * INA226_WE ina226 = INA226_WE(I2C_ADDRESS);
 * INA226_WE ina226 = INA226_WE(&Wire); -> uses I2C_ADDRESS = 0x40, pass any Wire Object
 * INA226_WE ina226 = INA226_WE(&Wire, I2C_ADDRESS);
 */
INA226_WE ina226 = INA226_WE(I2C_ADDRESS);

#include <SimpleTimer.h>
SimpleTimer timer;
#include <WiFiClientSecure.h>

char _lwifi_ssid[] = "tyes-itc";
char _lwifi_pass[] = "xxxxxxx";
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

float sun_mWh;
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
  Wire.begin();
  if(!ina226.init()){
    Serial.println("Failed to init INA226. Check your wiring.");
    while(1){}
  }
  ina226.waitUntilConversionCompleted(); //if you comment this line the first data might be zero

  sheetId="xxxxxxxxxxxxxx";
  sheetTag=URLEncode("sun");
  ina226.powerUp();
  timer.setInterval(1000, timerFunc0);

  timer.setInterval(3600000, timerFunc1);

}

void loop()
{
  timer.run();
  //每秒偵測太陽能發電量
  //每小時上傳Google試算表:太陽能發電量
}

void timerFunc0(){
   sun_mWh = sun_mWh + (( * ) / 1000);
  }


void timerFunc1(){
   sendToGoogleSheets("1",URLEncode((String() + "國小A" + "," + "601" + "," + sun_mWh).c_str()));
  sun_mWh = 0;
  }
