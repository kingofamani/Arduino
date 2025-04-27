/*
  網頁輸入 http://192.168.0.240
  啟動：
    /on 預設啟動第1個馬達5秒
    /on?s=10 啟動預設第1個馬達10秒
    /on?m=2 啟動第2個馬達預設5秒
    /on?m=3&s=15 啟動第3個馬達15秒
    /on?s=15&m=3 ↑同上
  關閉：
    /off 預設關閉第1個馬達
    /off?m=2 關閉第2個馬達
*/

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

int selectMoto = 1;//要「開啟」的馬達。RaspberryPi以http get傳來的值，xxxx?m=1,2,3，預設第1個馬達

//網路時鐘
//String formattedTime, TimeStamp;
//int splitT, y_dt, m_dt, d_dt, h_tm, m_tm, s_tm, DoW ;
//WiFiUDP ntpUDP;
//NTPClient timeClient(ntpUDP, "asia.pool.ntp.org", 28800, 60000);

//手動按下開始澆水鈕、停止澆水鈕
SimpleTimer timer;
int CountDownToStopTimeId;//關水的time id
int CountDownToStopTimeId2;
int CountDownToStopTimeId3;
int CountDownSecs = 5;//沒設秒數5秒後自動關閉
int CountDownSecs2 = 5;
int CountDownSecs3 = 5;
bool isBootCountDown = false;//啟用or停用 開始倒數關水
bool isBootCountDown2 = false;
bool isBootCountDown3 = false;

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
  selectMoto = 1;  
  if (server.args() > 0) {
    for (uint8_t i = 0; i < server.args(); i++) {
      if (server.argName(i) == "m") {
        selectMoto = server.arg(i).toInt();
      }
    }

    for (uint8_t i = 0; i < server.args(); i++) {
      if (server.argName(i) == "s") {
        if (selectMoto == 2) {
          CountDownSecs2 = server.arg(i).toInt();
        } else if (selectMoto == 3) {
          CountDownSecs3 = server.arg(i).toInt();
        } else {
          CountDownSecs = server.arg(i).toInt();//default Moto1
        }
      }
    }
  }

  if (selectMoto == 2) {
    isBootCountDown2 = true;
  } else if (selectMoto == 3) {
    isBootCountDown3 = true;
  } else {
    isBootCountDown = true;//default Moto1
  }

  int showSecs;
  if (selectMoto == 2) {
    showSecs = CountDownSecs2;
  } else if (selectMoto == 3) {
    showSecs = CountDownSecs3;
  } else {
    showSecs = CountDownSecs;
  }

  server.sendHeader("Access-Control-Allow-Origin", "*");//★要放在send之前
  server.send(200, "text/plain", MotoName(selectMoto) +  "開始澆水 " + String(showSecs) + "秒");
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

/*
回傳馬達名稱有2種情形：
  1./on啟動的馬達(selectMoto)名稱
  2./off強制手動關閉的馬達(selctOffMoto)名稱
*/
String MotoName(int m) {
  if (m == 1) {
    return MotoName1;
  } else if (m == 2) {
    return MotoName2;
  } else if (m == 3) {
    return MotoName3;
  } else {
    return MotoName1;//Default Moto
  }
}


void turnOff() {
  int selectOffMoto = 1;//關閉的馬達(要關的馬達不一定等於啟動馬達(selectMoto)，有可能2台馬達同時操作
  
  if (server.args() > 0) {
    for (uint8_t i = 0; i < server.args(); i++) {
      if (server.argName(i) == "m") {
        selectOffMoto = server.arg(i).toInt();
      }
    }
  }
  
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "Turn Off 水");
  Serial.println(MotoName(selectOffMoto) + "強制關水");
  turnOffMoto(selectOffMoto);
}

/*
關馬達2種方式：
  1./on啟動的馬達(selectMoto)，會在定時結束後自動關閉
  2./off強制手動關閉的馬達(selctOffMoto)
*/
void turnOffMoto(int m) {
  if (m == 1 || m == 2 || m == 3) {
    digitalWrite(selectPin(m), LOW);
  } else {
    digitalWrite(PIN_MOTO1, LOW);//Default Moto
  }
}

void countDownToStop() {
  if (isBootCountDown) {
    Serial.println(String(CountDownSecs) + "秒後" + MotoName(selectMoto) + "關水");
    CountDownToStopTimeId = timer.setTimeout(CountDownSecs * 1000, stopWater); //n秒後關水
    timer.enable(CountDownToStopTimeId);
    isBootCountDown = false;
  }

  if (isBootCountDown2) {
    Serial.println(String(CountDownSecs2) + "秒後" + MotoName(selectMoto) + "關水");
    CountDownToStopTimeId2 = timer.setTimeout(CountDownSecs2 * 1000, stopWater2);
    timer.enable(CountDownToStopTimeId2);
    isBootCountDown2 = false;
  }

  if (isBootCountDown3) {
    Serial.println(String(CountDownSecs3) + "秒後" + MotoName(selectMoto) + "關水");
    CountDownToStopTimeId3 = timer.setTimeout(CountDownSecs3 * 1000, stopWater3);
    timer.enable(CountDownToStopTimeId3);
    isBootCountDown3 = false;
  }
}

void stopWater() {
  Serial.println("==========stopWater=== once");
  turnOffMoto(1);

  //init
  CountDownSecs = 5;
}

void stopWater2() {
  Serial.println("==========stopWater2=== once");
  turnOffMoto(2);

  //init
  CountDownSecs2 = 5;
}

void stopWater3() {
  Serial.println("==========stopWater3=== once");
  turnOffMoto(3);

  //init
  CountDownSecs3 = 5;
}
