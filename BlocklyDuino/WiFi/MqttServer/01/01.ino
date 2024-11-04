//Generated Date: Mon, 14 Oct 2024 13:13:47 GMT

#include <WiFi.h>
#include <PubSubClient.h>
#define MQTT_SERVER_IP "192.168.8.180"
#define MQTT_SERVER_PORT 1883
#define MQTT_ID "test1"
#define MQTT_USERNAME "kingofamani"
#define MQTT_PASSWORD "xxxxxxxx"

char _lwifi_ssid[] = "tyes-itc2";
char _lwifi_pass[] = "xxxxxxxxxx";
String receivedTopic="";
String receivedMsg="";
bool waitForE=true;
bool ended=true;
bool pubCtrl=false;

WiFiClient mqttClient;
PubSubClient myClient(mqttClient);

void connectMQTT(){
  while (!myClient.connected()){
    if (!myClient.connect(MQTT_ID,MQTT_USERNAME,MQTT_PASSWORD))
    {
      delay(5000);
    }
  }
}

void mqttCallback(char* topic, byte* payload, unsigned int length){
  receivedTopic=String(topic);
  receivedMsg="";
  for (unsigned int myIndex = 0; myIndex < length; myIndex++)
  {
    receivedMsg += (char)payload[myIndex];
  }
  receivedMsg.trim();
  Serial.println(receivedMsg);

}

void setup()
{
  WiFi.disconnect();
  WiFi.softAPdisconnect(true);
  WiFi.mode(WIFI_STA);
  WiFi.begin(_lwifi_ssid, _lwifi_pass);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }
  delay(300);
  myClient.setServer(MQTT_SERVER_IP, MQTT_SERVER_PORT);
  myClient.setCallback(mqttCallback);
  connectMQTT();
  myClient.subscribe(String("home/kitchen/light").c_str());
  Serial.begin(9600);

}

void loop()
{
  myClient.loop();
  myClient.publish(String("home/kitchen/light").c_str(),String("open").c_str());
  delay(5000);
}
