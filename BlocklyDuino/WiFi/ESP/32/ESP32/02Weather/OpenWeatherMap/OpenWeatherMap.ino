//Generated Date: Tue, 02 Apr 2024 07:42:52 GMT

#define ARDUINOJSON_DECODE_UNICODE 1
#include <ArduinoJson.h>
#include <ctime>

const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 2*JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(13) + 280;
DynamicJsonDocument doc(capacity);
void fetchWeatherInfo(String cityID, char* myKey)
{
  static WiFiClient client;
  client.setTimeout(10000);
  if (!client.connect("api.openweathermap.org", 80)) {
    return;
  }
  const String url = String() + "/data/2.5/weather?id="+cityID+"&appid="+myKey;
  client.println("GET " + url + " HTTP/1.1");
  client.println(F("Host: api.openweathermap.org"));
  client.println(F("Accept: */*"));
  client.println(F("Connection: close"));
  if (client.println() == 0) {
    return;
  }
  char status[32] = {0};
  client.readBytesUntil('\r', status, sizeof(status));
  if (strcmp(status, "HTTP/1.1 200 OK") != 0) {
    return;
  }
  char endOfHeaders[] = "\r\n\r\n";
  if (!client.find(endOfHeaders)) {
    return;
  }
  DeserializationError error = deserializeJson(doc, client);
  if (error) {
    return;
  }
  client.stop();
}

String convMyTime(long myTimeStamp)
{
  static char time_text[]="YYYY-MM-DDTHH:MM:SS";
  const time_t myTime = myTimeStamp;
  strftime(time_text, sizeof(time_text), "%Y-%m-%dT%H:%M:%S", gmtime(&myTime));
  return String((const char*)time_text);
}

void setup()
{
  Serial.begin(9600);

  fetchWeatherInfo("1670029","xxxxxxxxxxx");
}

void loop()
{
  Serial.println((doc["main"]["temp_min"].as<float>()-273.15));
  Serial.println((doc["main"]["temp_max"].as<float>()-273.15));
  Serial.println(doc["main"]["humidity"].as<long>());
  delay(5000);
}
