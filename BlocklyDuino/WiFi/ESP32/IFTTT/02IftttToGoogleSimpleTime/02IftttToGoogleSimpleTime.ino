#include <WiFi.h>
#include <WiFiClient.h>
#include "time.h"
//#include <Wire.h>
uint8_t readStatus = 0;

char timeDate[21];
const char* ntpServer = "asia.pool.ntp.org";
const long  gmtOffset_sec = 28800;
const int   daylightOffset_sec = 60000;

// Replace with your SSID and Password
const char* ssid     = "AMANI-4G-Home2";
const char* password = "c41585c41585";

// Replace with your unique IFTTT URL resource
const char* resource = "/trigger/esp32google/with/key/xxxxxxxxxxxxxxxxxxxxx"; 
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
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  //Serial.println(&timeinfo, "%B %d %Y %H:%M:%S");
  
  strftime(timeDate,21, "%b %d %Y %H:%M:%S", &timeinfo);
  //Serial.println(timeDate);
  
  Serial.println(&timeinfo);
}

void setup() {
  Serial.begin(115200);
  initWifi();
  delay(1000);  
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();
}

void loop() {
  printLocalTime();
  
  makeIFTTTRequest();
  
  delay(10000);
  // enable timer deep sleep
    //esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);    
    //Serial.println("Going to sleep now");
    // start deep sleep for 3600 seconds (60 minutes)
    //esp_deep_sleep_start();
}

// Establish a Wi-Fi connection with your router
void initWifi() {
  Serial.print("Connecting to: "); 
  Serial.print(ssid);
  WiFi.begin(ssid, password);  

  int timeout = 10 * 4; // 10 seconds
  while(WiFi.status() != WL_CONNECTED  && (timeout-- > 0)) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");

  if(WiFi.status() != WL_CONNECTED) {
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
  while(!!!client.connect(server, 80) && (retries-- > 0)) {
    Serial.print(".");
  }
  Serial.println();
  if(!!!client.connected()) {
    Serial.println("Failed to connect...");
  }
    Serial.print("Request resource: "); 
  Serial.println(resource);
  // Temperature in Celsius
  String jsonObject = String("{\"value1\":\"") +timeDate + "\",\"value2\":\"" + 1 + "\"}";
  client.println(String("POST ") + resource + " HTTP/1.1");
  client.println(String("Host: ") + server); 
  client.println("Connection: close\r\nContent-Type: application/json");
  client.print("Content-Length: ");
  client.println(jsonObject.length());
  client.println();
  client.println(jsonObject);
        
  int timeout = 5 * 10; // 5 seconds             
  while(!!!client.available() && (timeout-- > 0)){
    delay(100);
  }
  if(!!!client.available()) {
    Serial.println("No response...");
  }
  while(client.available()){
    Serial.write(client.read());
  }
    Serial.println("\nclosing connection");
  client.stop(); 
}
