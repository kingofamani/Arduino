#include <WiFi.h>
#include <HTTPClient.h>
#include <TimeLib.h>
#include <ArduinoJson.h>

float minT;
float maxT;
String startTime = "";

String key = "CWA-5EDB1832-0C24-42A6-9FFD-E0B5DB26CDBC";
//地區參考https://opendata.cwa.gov.tw/opendatadoc/Opendata_City.pdf
String location = "五股區";

void setup() {
  Serial.begin(9600);

  // 連接WiFi
  WiFi.begin("tyes-itc2", "22924152", 6);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
}

void loop() {
  fetchData();
  delay(10000);
}

void fetchData() {
  HTTPClient http;
  // 五股區天氣
  String url = "https://opendata.cwa.gov.tw/api/v1/rest/datastore/F-D0047-071?Authorization="+key+"&format=JSON&locationName="+location+"&elementName=MinT,MaxT";
  
  // 開始 HTTP 連線
  http.begin(url);
  http.addHeader("Content-Type", "application/json");

  // 發送 POST 請求
  int httpCode = http.GET();

  if (httpCode == HTTP_CODE_OK) {
    DynamicJsonDocument doc(5024);
    DeserializationError error = deserializeJson(doc, http.getString(), DeserializationOption::NestingLimit(20));

    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return;
    }
    
    minT = (doc["records"]["locations"][0]["location"][0]["weatherElement"][0]["time"][0]["elementValue"][0]["value"]);
    maxT = (doc["records"]["locations"][0]["location"][0]["weatherElement"][1]["time"][0]["elementValue"][0]["value"]);
    String s = (doc["records"]["locations"][0]["location"][0]["weatherElement"][0]["time"][0]["startTime"]);
    startTime = s;
    
    Serial.print(startTime);
    Serial.print(F(" MinT: "));
    Serial.print(minT);
    Serial.print(F(",MaxT: "));
    Serial.println(maxT);

  } else {
    Serial.println("HTTP Request failed");
    Serial.println("HTTP Response Code: " + String(httpCode));
    Serial.println("Error: " + http.getString());
  }

  http.end();
}

