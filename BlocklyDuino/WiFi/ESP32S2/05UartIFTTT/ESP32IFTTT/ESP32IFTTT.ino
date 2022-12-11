#include <WiFi.h>
#include <WiFiClient.h>
#include "time.h"
#include "secrets.h"
#include <SoftwareSerial.h>
uint8_t readStatus = 0;

SoftwareSerial UnoSerial(2, 3);//連接UNO
String unoMsg ="";
String unoMsgArray[4];//UNO傳來的訊息

char timeDate[21];
const char* ntpServer = "asia.pool.ntp.org";
const long  gmtOffset_sec = 28800;
const int   daylightOffset_sec = 60000;


// Replace with your unique IFTTT URL resource
//寫入google sheet
const char* resource = "/trigger/esp32google/with/key/xxxxxxxxxxxxxxxxxx";
const char* resourceLINE = "/trigger/curtain_notify/with/key/xxxxxxxxxxxxxxxxxx";
// How your resource variable should look like, but with your own API KEY (that API KEY below is just an example):
//const char* resource = "/trigger/myAHT1011_readdata/with/key/nxxxxxxL2d_XXXXXgTlNSrxMJdmqy5";

// Maker Webhooks IFTTT
const char* server = "maker.ifttt.com";
// Time to sleep
uint64_t uS_TO_S_FACTOR = 1000000;  // Conversion factor for micro seconds to seconds
// sleep for 30 minutes = 1800 seconds
uint64_t TIME_TO_SLEEP = 60;        //1 minutes


void printLocalTime()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  //Serial.println(&timeinfo, "%B %d %Y %H:%M:%S");

  //strftime(timeDate, 21, "%b %d %Y %H:%M:%S", &timeinfo);
  strftime(timeDate, 21, "%Y-%m-%d %H:%M:%S", &timeinfo);
  //Serial.println(timeDate);

  Serial.println(&timeinfo);
}

void setup() {
  Serial.begin(9600);
  UnoSerial.begin(9600);

  initWifi();
  delay(1000);
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();
}

void loop() {

  //傳送訊息：ESP32→UNO
  if (Serial.available()) {
    String msg = Serial.readString();
    UnoSerial.print(msg);
  }

  //接收訊息：UNO→ESP32
  if (UnoSerial.available()) {
    unoMsg = UnoSerial.readString();
    Serial.println(unoMsg);
    stringToArray(unoMsg,unoMsgArray);
    
    if (unoMsgArray[0] == "pet") {
      printLocalTime();
      makeIFTTTRequest();
      delay(1000);
    } else if (unoMsgArray[0] == "line") {
      printLocalTime();
      makeIFTTTRequest2();
      delay(1000);
    } else if (unoMsgArray[0] == "init") {
      initWifi();
      Serial.println("重開Wifi");
    } else {
      Serial.println("無此指令");
    }
  }



  //delay(30000);

  // enable timer deep sleep
  //esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  //Serial.println("Going to sleep now");
  // start deep sleep for 3600 seconds (60 minutes)
  //esp_deep_sleep_start();
}

// Establish a Wi-Fi connection with your router
void initWifi() {
  Serial.print("Connecting to WIFI");
  WiFi.begin(WIFI_SSID, WIFI_PWD);

  int timeout = 10 * 4; // 10 seconds
  while (WiFi.status() != WL_CONNECTED  && (timeout-- > 0)) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Failed to connect, going back to sleep");
  }

  Serial.print("WiFi connected in: ");
  Serial.print(millis());
  Serial.print(", IP address: ");
  Serial.println(WiFi.localIP());
}

// Make an HTTP request to the IFTTT web service
void makeIFTTTRequest() {
  Serial.print("Connecting to ");
  Serial.print(server);

  WiFiClient client;
  int retries = 5;
  while (!!!client.connect(server, 80) && (retries-- > 0)) {
    Serial.print(".");
  }
  Serial.println();
  if (!!!client.connected()) {
    Serial.println("Failed to connect...");
  }
  Serial.print("Request resource: ");
  Serial.println(resource);
  //訊息格式：
  //格式：pet,{room name},{pet ID},{x},{y},
  //例如：pet,客廳,5,120,100,
  String jsonObject = String("{\"value1\":\"") + timeDate + "\",\"value2\":\"" + unoMsg + "\"}";
  client.println(String("POST ") + resource + " HTTP/1.1");
  client.println(String("Host: ") + server);
  client.println("Connection: close\r\nContent-Type: application/json");
  client.print("Content-Length: ");
  client.println(jsonObject.length());
  client.println();
  client.println(jsonObject);

  int timeout = 5 * 10; // 5 seconds
  while (!!!client.available() && (timeout-- > 0)) {
    delay(100);
  }
  if (!!!client.available()) {
    Serial.println("No response...");
  }
  while (client.available()) {
    Serial.write(client.read());
  }
  Serial.println("\nclosing connection");
  client.stop();
}

void makeIFTTTRequest2() {
  Serial.print("Connecting to ");
  Serial.print(server);

  WiFiClient client;
  int retries = 5;
  while (!!!client.connect(server, 80) && (retries-- > 0)) {
    Serial.print(".");
  }
  Serial.println();
  if (!!!client.connected()) {
    Serial.println("Failed to connect...");
  }
  Serial.print("Request resource: ");
  Serial.println(resourceLINE);
  //訊息格式：
  //格式：line,{room name},{event},
  //例如：line,客廳,偵測到小偷請留意家中,
  String jsonObject = String() + "{\"value1\":\"" + timeDate + "\",\"value2\":\"" + unoMsgArray[1] + "\",\"value3\":\"" + unoMsgArray[2] + "\"}";
  client.println(String("POST ") + resourceLINE + " HTTP/1.1");
  client.println(String("Host: ") + server);
  client.println("Connection: close\r\nContent-Type: application/json");
  client.print("Content-Length: ");
  client.println(jsonObject.length());
  client.println();
  client.println(jsonObject);

  int timeout = 5 * 10; // 5 seconds
  while (!!!client.available() && (timeout-- > 0)) {
    delay(100);
  }
  if (!!!client.available()) {
    Serial.println("No response...");
  }
  while (client.available()) {
    Serial.write(client.read());
  }
  Serial.println("\nclosing connection");
  client.stop();
}

void stringToArray(String str,String (& tmpArray) [4] ) {
  int r = 0, t = 0;

  for (int i = 0; i < str.length(); i++)
  {
    if (str[i] == ',')
    {
      if (i - r > 1)
      {
        tmpArray[t] = str.substring(r, i);
        t++;
      }
      r = (i + 1);
    }
  }
}
