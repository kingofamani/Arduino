//Generated Date: Sun, 15 Oct 2023 07:57:43 GMT

#include <PubSubClient.h>
#define MQTT_SERVER_IP "broker.hivemq.com"
#define MQTT_SERVER_PORT 1883
#define MQTT_ID ""
#define MQTT_USERNAME ""
#define MQTT_PASSWORD ""

char _lwifi_ssid[] = "xxxx";
char _lwifi_pass[] = "xxxxxxx";
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
  if (receivedTopic == "car/go") {
    if (receivedMsg == "f") {
      Serial.println("前進");
    }
  }
  if (receivedTopic == "carlowpower") {
    if (receivedMsg == "1") {
      Serial.println("該充電了");
    }
  }

}

void setup()
{
  Serial.begin(9600);

  myClient.setServer(MQTT_SERVER_IP, MQTT_SERVER_PORT);
  myClient.setCallback(mqttCallback);

  connectMQTT();
  myClient.subscribe(String("car/go").c_str());
  myClient.subscribe(String("carlowpower").c_str());
}

void loop()
{
  myClient.loop();

}
