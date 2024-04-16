#include <NTPClient.h>
// change next line to use with another board/shield
#include <ESP8266WiFi.h>
//#include <WiFi.h> // for WiFi shield
//#include <WiFi101.h> // for WiFi 101 shield or MKR1000
#include <WiFiUdp.h>

const char *ssid     = "AMANI-4G-Home";
const char *password = "xxxxxxxxxxx";

WiFiUDP ntpUDP;

// By default 'pool.ntp.org' is used with 60 seconds update interval and
// no offset
//NTPClient timeClient(ntpUDP);

// You can specify the time server pool and the offset, (in seconds)
// additionaly you can specify the update interval (in milliseconds).
NTPClient timeClient(ntpUDP, "asia.pool.ntp.org", 28800, 60000);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();
}

void loop() {
  timeClient.update();

  Serial.println(timeClient.getFormattedTime());

  String formattedTime, TimeStamp;
  int splitT, y_dt, m_dt, d_dt,h_tm, m_tm, s_tm, DoW ;

  formattedTime = timeClient.getFormattedTime();
  splitT = formattedTime.indexOf(":");
  TimeStamp = formattedTime.substring(0, splitT);
  h_tm = TimeStamp.toInt();
  splitT = splitT + 1;
  formattedTime.remove(0, splitT);
  splitT = formattedTime.indexOf(":");
  TimeStamp = formattedTime.substring(0, splitT);
  m_tm = TimeStamp.toInt();
  splitT = splitT + 1;
  formattedTime.remove(0, splitT);
  splitT = formattedTime.indexOf(":");
  TimeStamp = formattedTime.substring(0, splitT);
  s_tm = TimeStamp.toInt();
  //DoW = dayOfWeek(y_dt, m_dt, d_dt);

  Serial.println(h_tm);
  Serial.println(m_tm);
  Serial.println(s_tm);
  //Serial.println(DoW);
  Serial.println("----");

  delay(1000);
}
