#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
//#include <vector>
#include <TimeLib.h>
#include <TM1637Display.h>

// std::vector<float> MinTs;
// std::vector<float> MaxTs;
// std::vector<String> StartTimes;

float minT;
float maxT;
String startTime = "";

String key = "xxxxxxxxxxxxxxxxxxxxxxxx";

unsigned long preMillis;

TM1637Display tm_display23(4, 15);

void setup() {
  Serial.begin(115200);

  tm_display23.setBrightness(7);
  tm_display23.clear();

  preMillis = millis();

  // 連接WiFi
  WiFi.begin("AMANI-4G-Home", "xxxxxxxxxx", 6);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");

  fetchData();
  //釋放記憶體
  //vectorclear();
}

void loop() {
  if (millis() - preMillis > 1740000) {//29分鐘 * 60 * 1000 
    fetchData();
    //vectorclear();
    preMillis = millis();
  }

  tm_display23.showNumberDecEx(minT, 0x40, true, 2, 0);
  tm_display23.showNumberDecEx(maxT, 0, true, 2, 2);
  delay(10000);

  int month = startTime.substring(5, 7).toInt();
  int day = startTime.substring(8, 10).toInt();
  tm_display23.showNumberDecEx(month, 0x40, true, 2, 0);
  tm_display23.showNumberDecEx(day, 0, true, 2, 2);
  delay(1000);
}

void vectorclear() {
  // MinTs.clear();
  // MaxTs.clear();
  // StartTimes.clear();
}

void fetchData() {
  HTTPClient http;
  // 五股區天氣
  String url = "https://opendata.cwa.gov.tw/api/v1/rest/datastore/F-D0047-071?Authorization="+key+"&limit=1&format=JSON&locationName=%E4%BA%94%E8%82%A1%E5%8D%80&elementName=MinT,MaxT";
  
  // 開始 HTTP 連線
  http.begin(url);
  http.addHeader("Content-Type", "application/json");

  // 發送 POST 請求
  int httpCode = http.GET();

  if (httpCode == HTTP_CODE_OK) {
    String payload = http.getString();

    DynamicJsonDocument doc(5024);
    DeserializationError error = deserializeJson(doc, payload, DeserializationOption::NestingLimit(20));

    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return;
    }

    //2024/12官網JSON格式更新
    minT =     doc["records"]["Locations"][0]["Location"][0]["WeatherElement"][2]["Time"][0]["ElementValue"][0]["MinTemperature"];
    maxT =     doc["records"]["Locations"][0]["Location"][0]["WeatherElement"][1]["Time"][0]["ElementValue"][0]["MaxTemperature"];
    String s = doc["records"]["Locations"][0]["Location"][0]["WeatherElement"][0]["Time"][0]["StartTime"];
    startTime = s;

    //minT =     (doc["records"]["locations"][0]["location"][0]["weatherElement"][0]["time"][0]["elementValue"][0]["value"]);
    //maxT =     (doc["records"]["locations"][0]["location"][0]["weatherElement"][1]["time"][0]["elementValue"][0]["value"]);
    //String s = (doc["records"]["locations"][0]["location"][0]["weatherElement"][0]["time"][0]["startTime"]);
    //startTime = s;

    String month = startTime.substring(5, 7);
    String day = startTime.substring(8, 10);
    Serial.print(month + "/" + day);
    Serial.print(F(" MinT: "));
    Serial.print(minT);
    Serial.print(F(",MaxT: "));
    Serial.println(maxT);

    tm_display23.showNumberDecEx(minT, 0x40, true, 2, 0);
    tm_display23.showNumberDecEx(maxT, 0, true, 2, 2);

    Serial.println("HTTP_CODE_OK");


  } else {
    // 如果請求失敗，則顯示錯誤信息
    Serial.println("HTTP Request failed");
    Serial.println("HTTP Response Code: " + String(httpCode));
    Serial.println("Error: " + http.getString());
  }

  // 關閉連線
  http.end();
}

