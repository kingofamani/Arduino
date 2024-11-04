#include <WiFi.h>
#include <WiFiClient.h>
#include "time.h"
#include "secrets.h"
#include <SoftwareSerial.h>

#define U1RXD 18
#define U1TXD 17

SoftwareSerial UnoSerial(6, 7);
String unoMsg ="";
String unoMsgArray[4];

char timeDate[21];
const char* ntpServer = "asia.pool.ntp.org";
const long  gmtOffset_sec = 28800;
const int   daylightOffset_sec = 60000;


//IFTTT
const char* resource = "/trigger/esp32google/with/key/xxxxxxxxxxxxxxxxxxxx";
const char* resourceLINE = "/trigger/curtain_notify/with/key/xxxxxxxxxxxxxxxxxxxx";

const char* server = "maker.ifttt.com";
// Time to sleep
uint64_t uS_TO_S_FACTOR = 1000000;
uint64_t TIME_TO_SLEEP = 60;

void printLocalTime()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  strftime(timeDate, 21, "%Y-%m-%d %H:%M:%S", &timeinfo);
  Serial.println(&timeinfo);
}

void setup() {
  Serial.begin(9600);
  UnoSerial.begin(9600);//UNO
  Serial1.begin(9600, SERIAL_8N1, U1RXD, U1TXD);//ESP32藍牙

  initWifi();
  delay(1000);
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();
}

void loop() {

  //藍牙ESP32→ESP32S2，ESP32S2再自動傳至Uno
  if (Serial1.available()) {
      String btMsg = Serial1.readString();
      UnoSerial.print(btMsg);//傳至UNO
      Serial.print(btMsg);      
  }

  //UNO→ESP32S2
  if (UnoSerial.available()) {
    unoMsg = UnoSerial.readString();
    unoMsg.remove(unoMsg.length()-2);//刪除/r換行字元
    //Serial.println(unoMsg);
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
    } else if (unoMsgArray[0] == "position") {
      
      Serial.println("窗簾位置");
    }  else {
      Serial.println("無此指令");
    }
    unoMsg = "";
  }

}

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
    Serial.println("Failed to connect");
  }

  Serial.print("WiFi connected in: ");
  Serial.print(millis());
  Serial.print(", IP: ");
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
  String jsonObject = String("{\"value1\":\"") + timeDate + "\",\"value2\":\"" + unoMsg + "\"}";
  Serial.println(jsonObject);
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
