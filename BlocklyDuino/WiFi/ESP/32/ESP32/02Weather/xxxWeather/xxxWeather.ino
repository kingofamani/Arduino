//Generated Date: Thu, 14 Sep 2023 00:29:39 GMT

#include <WiFi.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>

char _lwifi_ssid[] = "AMANI-4G-Home";
char _lwifi_pass[] = "xxxxxxxxxxxxxxx";
String Weather0012[8] = {"","","","","","","",""};
String Weather1224[8] = {"","","","","","","",""};
String Weather2436[8] = {"","","","","","","",""};

void opendataWeather(String location, String Authorization) {
  WiFiClientSecure client_tcp;
  client_tcp.setInsecure();
  if (client_tcp.connect("opendata.cwb.gov.tw", 443)) {
    String request = "/api/v1/rest/datastore/F-C0032-001?Authorization="+Authorization+"&locationName="+urlencode(location);
    client_tcp.println("GET " + request + " HTTP/1.1");
    client_tcp.println("Host: opendata.cwb.gov.tw");
    client_tcp.println("Connection: close");
    client_tcp.println();
    String getResponse="",Feedback="";
    boolean state = false;
    int waitTime = 10000;
    long startTime = millis();
    char c;
    String temp = "";
    int i = 0;
    while ((startTime + waitTime) > millis()) {
      while (client_tcp.available()) {
        if (state==true) {
          temp = client_tcp.readStringUntil('\r');
          i++;
          if (i%2==0) {
            Feedback += temp;
          }
        }
        else
          c = client_tcp.read();
        if (c == '\n') {
          if (getResponse.length()==0) state=true;
          getResponse = "";
        }
        else if (c != '\r')
          getResponse += String(c);
        startTime = millis();
      }
      if (Feedback.length()!= 0) break;
    }
    client_tcp.stop();
    temp = "";
    for (i=0;i<Feedback.length();i++) {
      c = Feedback[i];
      if (c!='\r'&&c!='\n')
      temp += Feedback[i];
    }
    Feedback = temp;
    Weather0012[0] = location;
    Weather1224[0] = location;
    Weather2436[0] = location;
    JsonObject obj;
  DynamicJsonDocument doc(1024);
    Feedback = Feedback.substring(Feedback.indexOf("\"weatherElement\":[")+18,Feedback.length()-5);
    temp = Feedback.substring(Feedback.indexOf("\"Wx\",")+5,Feedback.indexOf("}}]}")+3);
    deserializeJson(doc, "{"+temp+"}");
    obj = doc.as<JsonObject>();
    Weather0012[1] = obj["time"][0]["startTime"].as<String>();
    Weather0012[2] = obj["time"][0]["endTime"].as<String>();
    Weather1224[1] = obj["time"][1]["startTime"].as<String>();
    Weather1224[2] = obj["time"][1]["endTime"].as<String>();
    Weather2436[1] = obj["time"][2]["startTime"].as<String>();
    Weather2436[2] = obj["time"][2]["endTime"].as<String>();
    Weather0012[3] = obj["time"][0]["parameter"]["parameterName"].as<String>();
    Weather1224[3] = obj["time"][1]["parameter"]["parameterName"].as<String>();
    Weather2436[3] = obj["time"][2]["parameter"]["parameterName"].as<String>();
    Feedback.replace(temp,"");
    temp = Feedback.substring(Feedback.indexOf("\"PoP\",")+6,Feedback.indexOf("}}]}")+3);
    deserializeJson(doc, "{"+temp+"}");
    obj = doc.as<JsonObject>();
    Weather0012[4] = obj["time"][0]["parameter"]["parameterName"].as<String>();
    Weather1224[4] = obj["time"][1]["parameter"]["parameterName"].as<String>();
    Weather2436[4] = obj["time"][2]["parameter"]["parameterName"].as<String>();
    Feedback.replace(temp,"");
    temp = Feedback.substring(Feedback.indexOf("\"MinT\",")+7,Feedback.indexOf("}}]}")+3);
    deserializeJson(doc, "{"+temp+"}");
    obj = doc.as<JsonObject>();
    Weather0012[5] = obj["time"][0]["parameter"]["parameterName"].as<String>();
    Weather1224[5] = obj["time"][1]["parameter"]["parameterName"].as<String>();
    Weather2436[5] = obj["time"][2]["parameter"]["parameterName"].as<String>();
    Feedback.replace(temp,"");
    temp = Feedback.substring(Feedback.indexOf("\"CI\",")+5,Feedback.indexOf("}}]}")+3);
    deserializeJson(doc, "{"+temp+"}");
    obj = doc.as<JsonObject>();
    Weather0012[6] = obj["time"][0]["parameter"]["parameterName"].as<String>();
    Weather1224[6] = obj["time"][1]["parameter"]["parameterName"].as<String>();
    Weather2436[6] = obj["time"][2]["parameter"]["parameterName"].as<String>();
    Feedback.replace(temp,"");
    temp = Feedback.substring(Feedback.indexOf("\"MaxT\",")+7,Feedback.indexOf("}}]}")+3);
    deserializeJson(doc, "{"+temp+"}");
    obj = doc.as<JsonObject>();
    Weather0012[7] = obj["time"][0]["parameter"]["parameterName"].as<String>();
    Weather1224[7] = obj["time"][1]["parameter"]["parameterName"].as<String>();
    Weather2436[7] = obj["time"][2]["parameter"]["parameterName"].as<String>();
  }
}
String getWeather(int period,int index) {
  if (period==0) {
    return Weather0012[index];
  } else if (period==1) {
    return Weather1224[index];
  } else if (period==2) {
    return Weather2436[index];
  }
  return "";
}
String urlencode(String str) {
    String encodedString="";
    char c;
    char code0;
    char code1;
    for (int i =0; i < str.length(); i++) {
      c=str.charAt(i);
      if (c == ' '){
        encodedString+= '+';
      } else if (isalnum(c)){
        encodedString+=c;
      } else{
        code1=(c & 0xf)+'0';
        if ((c & 0xf) >9){
            code1=(c & 0xf) - 10 + 'A';
        }
        c=(c>>4)&0xf;
        code0=c+'0';
        if (c > 9){
            code0=c - 10 + 'A';
        }
        encodedString+="%";
        encodedString+=code0;
        encodedString+=code1;
      }
      yield();
    }
    return encodedString;
}

void setup()
{
  Serial.begin(9600);

  WiFi.disconnect();
  WiFi.softAPdisconnect(true);
  WiFi.mode(WIFI_STA);
  WiFi.begin(_lwifi_ssid, _lwifi_pass);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }
  delay(300);
  Serial.println(WiFi.localIP().toString());
  opendataWeather("新北市","xxxxxxxxxxxxxxxxxx");
}

void loop()
{
  Serial.println((getWeather(0,0)));
  Serial.println((getWeather(0,3)));
  Serial.println((getWeather(0,4)));
  Serial.println((getWeather(0,5)));
  Serial.println((getWeather(0,7)));
  Serial.println("");
  delay(5000);
}
