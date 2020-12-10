#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
//#include <NTPClient.h>
#include <WiFiUdp.h>
#include <SimpleTimer.h>

#include "secrets.h"//自訂頁面(用""，不能用<>)


#define PIN_MOTO1  5
#define PIN_MOTO2  4
#define PIN_MOTO3  14

String MotoName1 = "1號開關";//----------之後可以改由firbase更名
String MotoName2 = "2號開關";
String MotoName3 = "3號開關";

int selectMoto = 1;//RaspberryPi以http get傳來的值，xxxx?m=1,2,3，預設第1個馬達

//網路時鐘
//String formattedTime, TimeStamp;
//int splitT, y_dt, m_dt, d_dt, h_tm, m_tm, s_tm, DoW ;
//WiFiUDP ntpUDP;
//NTPClient timeClient(ntpUDP, "asia.pool.ntp.org", 28800, 60000);

//手動按下開始澆水鈕、停止澆水鈕
SimpleTimer timer;
int CountDownToStopTimeId;//關水的time id
int CountDownSecs = 0;//關水倒數秒數
bool isBootCountDown = false;//啟用or停用 開始倒數關水

//設定某個時間澆花(例如設定每天06:00澆花)
//String setH, setM, setS;

//建WiFi Server
ESP8266WebServer server(80);

void setup() {
  //繼電器
  pinMode(PIN_MOTO1, OUTPUT);
  pinMode(PIN_MOTO2, OUTPUT);
  pinMode(PIN_MOTO3, OUTPUT);

  Serial.begin(115200);

  //啟用WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PWD);
  WiFi.config(STATIC_IP, GATEWAY, SUBNET);
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
  Serial.println("");
  Serial.println(WiFi.localIP());



  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);

  server.on("/on", turnOn);
  server.on("/off", turnOff);

  server.begin();
  Serial.println("Server開啟");

  //啟用網路時鐘
  //  timeClient.begin();



}//end of setup

void loop() {
  //WiFi
  server.handleClient();
  MDNS.update();

  //網路時鐘
  //  networkClock();

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
  server.send(200, "text/html", "WifiClockWater3Relay Home");
}

void turnOn() {
  if (server.args() > 0) {
    if (server.argName(0) == "s") {
      CountDownSecs = server.arg(0).toInt();
    }
    if (server.args() > 1) {
      if (server.argName(1) == "m") {
        selectMoto = server.arg(1).toInt();
      }
    }

  } else {
    CountDownSecs = 5;//沒設秒數5秒後自動關閉
  }
  isBootCountDown = true;

  server.sendHeader("Access-Control-Allow-Origin", "*");//★要放在send之前
  server.send(200, "text/plain", MotoName() +  "開始澆水 " + String(CountDownSecs) + "秒");
  turnOnMoto();


}

void turnOnMoto() {
  if (selectMoto == 1 || selectMoto == 2 || selectMoto == 3) {
    digitalWrite(selectPin(selectMoto), HIGH);

  } else {
    digitalWrite(PIN_MOTO1, HIGH);//Default Moto
  }
}

int selectPin(int m) {
  if (m == 1) {
    return PIN_MOTO1;
  } else if (m == 2) {
    return PIN_MOTO2;
  } else if (m == 3) {
    return PIN_MOTO3;
  } else {
    return PIN_MOTO1;//Default Moto
  }
}

String MotoName() {
  if (selectMoto == 1) {
    return MotoName1;
  } else if (selectMoto == 2) {
    return MotoName2;
  } else if (selectMoto == 3) {
    return MotoName3;
  } else {
    return MotoName1;//Default Moto
  }
}


void turnOff() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "Turn Off 水");
  Serial.println(MotoName() + "強制關水");
  turnOffMoto();
}

void turnOffMoto() {
  if (selectMoto == 1 || selectMoto == 2 || selectMoto == 3) {
    digitalWrite(selectPin(selectMoto), LOW);
  } else {
    digitalWrite(PIN_MOTO1, LOW);//Default Moto
  }
}

void countDownToStop() {
  if (isBootCountDown) {
    Serial.println(String(CountDownSecs) + "秒後" + MotoName() + "關水");
    CountDownToStopTimeId = timer.setTimeout(CountDownSecs * 1000, stopWater); //n秒後關水
    timer.enable(CountDownToStopTimeId);

    isBootCountDown = false;
  }
}

void stopWater() {
  Serial.println("==========stopWater=== once");
  turnOffMoto();

  CountDownSecs = 0;
  selectMoto = 1;
}


//void timing() {
//  String msg = "<h1 style='color:red;'>設定澆花時間</h1>";
//  msg += "<a href='/settime?h=22&m=13&s=00'  >開始設定</a>";
//  server.send(200, "text/html", msg);
//}
//
//void settime() {
//  String t[] = {"00", "00", "00"};
//  for (uint8_t i = 0; i < server.args(); i++) {
//    t[i] = server.arg(i);
//  }
//  setH = t[0];
//  setM = t[1];
//  setS = t[2];
//  server.send(200, "text/plain", "將於 " + setH + ":" + setM + ":" + setS + " 開始澆花");
//}

//void networkClock() {
//  timeClient.update();
//  //Serial.println(timeClient.getFormattedTime());
//
//  formattedTime = timeClient.getFormattedTime();
//  splitT = formattedTime.indexOf(":");
//  TimeStamp = formattedTime.substring(0, splitT);
//  h_tm = TimeStamp.toInt();
//  splitT = splitT + 1;
//  formattedTime.remove(0, splitT);
//  splitT = formattedTime.indexOf(":");
//  TimeStamp = formattedTime.substring(0, splitT);
//  m_tm = TimeStamp.toInt();
//  splitT = splitT + 1;
//  formattedTime.remove(0, splitT);
//  splitT = formattedTime.indexOf(":");
//  TimeStamp = formattedTime.substring(0, splitT);
//  s_tm = TimeStamp.toInt();
//  delay(1000);
//}
//
//void DigitalClockDisplay() {
//  int h, m, s;
//  s = millis() / 1000;
//  m = s / 60;
//  h = s / 3600;
//  s = s - m * 60;
//  m = m - h * 60;
//}
//void printDigits(int digits) {
//  Serial.print(":");
//  if (digits < 10)
//    Serial.print('0');
//  Serial.print(digits);
//}
