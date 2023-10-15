//Generated Date: Sun, 15 Oct 2023 08:45:18 GMT

#include <WiFi.h>
#include <PubSubClient.h>
#define MQTT_SERVER_IP "broker.hivemq.com"
#define MQTT_SERVER_PORT 8883
#define MQTT_ID "8a05a03895e647a1b352aa8823be3a68.s2.eu.hivemq.cloud"
#define MQTT_USERNAME "kingofamani"
#define MQTT_PASSWORD "9.Vvi@RMp2gqR5m"

char _lwifi_ssid[] = "AMANI-4G-Home";
char _lwifi_pass[] = "c41585c41585";
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
  Serial.begin(9600);

  myClient.setServer(MQTT_SERVER_IP, MQTT_SERVER_PORT);
  myClient.setCallback(mqttCallback);

  WiFi.disconnect();
  WiFi.softAPdisconnect(true);
  WiFi.mode(WIFI_STA);
  WiFi.begin(_lwifi_ssid, _lwifi_pass);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }
  delay(300);
  Serial.println("WIFI OK");
  delay(1000);
  connectMQTT();
  myClient.subscribe(String("car/map").c_str());
}

void loop()
{
  myClient.loop();

}
