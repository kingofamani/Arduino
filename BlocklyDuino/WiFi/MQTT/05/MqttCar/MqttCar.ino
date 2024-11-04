//Generated Date: Fri, 25 Oct 2024 01:43:23 GMT

#include <WiFi.h>
#include <PubSubClient.h>
#define MQTT_SERVER_IP "192.168.2.100"
#define MQTT_SERVER_PORT 1883
#define MQTT_ID "clientcar"
#define MQTT_USERNAME "kingofamani"
#define MQTT_PASSWORD "xxxxxxxxxx"

String myDir = "";
byte m1aL9110=16;
byte m1bL9110=17;
byte m2aL9110=21;
byte m2bL9110=22;

byte m1bCH=8;
byte m2bCH=9;

char _lwifi_ssid[] = "tyes-itc2";
char _lwifi_pass[] = "xxxxxxxxxx";
String receivedTopic="";
String receivedMsg="";
bool waitForE=true;
bool ended=true;
bool pubCtrl=false;

WiFiClient mqttClient;
PubSubClient myClient(mqttClient);

void forward() {
  digitalWrite(m1aL9110,1);
  ledcWrite(m1bCH,255-255);
  digitalWrite(m2aL9110,1);
  ledcWrite(m2bCH,255-255);
}

void backward() {
  digitalWrite(m1aL9110,0);
  ledcWrite(m1bCH,255);
  digitalWrite(m2aL9110,0);
  ledcWrite(m2bCH,255);
}

void turnRight() {
  digitalWrite(m2aL9110,0);
  ledcWrite(m2bCH,255);
  digitalWrite(m1aL9110,1);
  ledcWrite(m1bCH,255);
}

void turnLeft() {
  digitalWrite(m1aL9110,0);
  ledcWrite(m1bCH,255);
  digitalWrite(m2aL9110,1);
  ledcWrite(m2bCH,255);
}

void stopCar() {
  digitalWrite(m1aL9110,1);
  ledcWrite(m1bCH,255);
  digitalWrite(m2aL9110,1);
  ledcWrite(m2bCH,255);
}

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
  myDir = receivedMsg;
  Serial.println(myDir);
  if (myDir == "u") {
    forward();
  } else if (myDir == "d") {
    backward();
  } else if (myDir == "l") {
    turnLeft();
  } else if (myDir == "r") {
    turnRight();
  } else if (myDir == "s") {
    stopCar();
  }
  delay(100);

}

void setup()
{
  pinMode(m1aL9110,OUTPUT);
  pinMode(m2aL9110,OUTPUT);
  ledcSetup(m1bCH, 5000, 8);
  ledcAttachPin(m1bL9110,m1bCH);
  ledcSetup(m2bCH, 5000, 8);
  ledcAttachPin(m2bL9110,m2bCH);
  digitalWrite(m1aL9110,1);
  ledcWrite(m1bCH,255);
  digitalWrite(m2aL9110,1);
  ledcWrite(m2bCH,255);

  Serial.begin(9600);

  WiFi.disconnect();
  WiFi.softAPdisconnect(true);
  WiFi.mode(WIFI_STA);
  WiFi.begin(_lwifi_ssid, _lwifi_pass);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }
  delay(300);
  Serial.println("WiFi OK");
  myClient.setServer(MQTT_SERVER_IP, MQTT_SERVER_PORT);
  myClient.setCallback(mqttCallback);
  connectMQTT();
  myClient.subscribe(String("car/direct").c_str());
  Serial.println("MQTT連線成功");
}

void loop()
{
  myClient.loop();

}
