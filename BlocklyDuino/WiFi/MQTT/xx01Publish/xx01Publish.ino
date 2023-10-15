//Generated Date: Sun, 15 Oct 2023 09:47:57 GMT

#include <WiFi.h>
#include <PubSubClient.h>
#define MQTT_SERVER_IP "broker.hivemq.com"
#define MQTT_SERVER_PORT 1883
#define MQTT_ID "xxxxxxxxxxxxxx.s2.eu.hivemq.cloud"
#define MQTT_USERNAME "kingofamani"
#define MQTT_PASSWORD "xxxxxxxxxxxxxx"

char _lwifi_ssid[] = "AMANI-4G-Home";
char _lwifi_pass[] = "xxxxxxxxxxxxxx";
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

}

void setup()
{
  Serial.begin(9600);

  myClient.setServer(MQTT_SERVER_IP, MQTT_SERVER_PORT);
  myClient.setCallback(mqttCallback);

  WiFi.disconnect();
  WiFi.softAPdisconnect(true);
  WiFi.mode(WIFI_STA);
  WiFi.begin(_lwifi_ssid, _lwifi_pass);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }
  delay(300);
  Serial.println("wifi OK");
  delay(1000);
  connectMQTT();
  myClient.publish(String("car/map").c_str(),String("{1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1}").c_str());
  myClient.publish(String("car/goods").c_str(),String("finish,john,3,5").c_str());
  Serial.println("MQTT OK");
}

void loop()
{
  myClient.loop();

}
