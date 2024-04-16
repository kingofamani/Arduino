#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <SimpleTimer.h>

#include "secrets.h"//自訂頁面(用""，不能用<>)


#define RELAY 0


//手動按下開始澆水鈕、停止澆水鈕
SimpleTimer timer;
int CountDownToStopTimeId;//關水的time id
int CountDownSecs = 0;//關水倒數秒數
bool isBootCountDown = false;//啟用or停用 開始倒數關水


//建WiFi Server
ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  
  //繼電器
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, LOW);

  

  //啟用WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PWD);
  WiFi.config(STATIC_IP, GATEWAY, SUBNET);
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
  Serial.println(WiFi.localIP());



  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);

  server.on("/on", turnOn);
  server.on("/off", turnOff);

  server.begin();
  Serial.println("Server開啟");

}//end of setup

void loop() {
  //WiFi
  server.handleClient();
  MDNS.update();

  //幾秒後關水
  timer.run();//初始timer
  countDownToStop();

}//loop

void handleNotFound() {
    String message = "找不到網頁\n\n";
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";
    for (uint8_t i = 0; i < server.args(); i++) {
      message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }
    server.send(404, "text/plain", message);
}

void handleRoot() {
  server.send(200, "text/html", "home");
}

void turnOn() {
  if (server.args() > 0) {
    CountDownSecs = server.arg(0).toInt();
  } else {
    //CountDownSecs = 5;//沒設秒數5秒後自動關閉
  }
  isBootCountDown = true;

  server.sendHeader("Access-Control-Allow-Origin", "*");//★要放在send之前
  server.send(200, "text/plain",  "開始澆水 "+ String(CountDownSecs)+"秒");
  digitalWrite(RELAY, HIGH);

}

void turnOff() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "Turn Off 水");
  Serial.println("強制關水");
  digitalWrite(RELAY, LOW);
}

void countDownToStop() {
  if (isBootCountDown) {
    Serial.println(String(CountDownSecs) + "秒後關水");
    CountDownToStopTimeId = timer.setTimeout(CountDownSecs * 1000, stopWater); //n秒後關水
    timer.enable(CountDownToStopTimeId);

    isBootCountDown = false;
  }
}

void stopWater() {
  Serial.println("==========stopWater=== once");
  digitalWrite(RELAY, LOW);

  CountDownSecs = 0;
}
