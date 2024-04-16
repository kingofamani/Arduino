#include <ESP8266WiFi.h>
#include <PubSubClient.h>
// Update these with values suitable for your network.
long serial_speed = 115200;
const char* ssid = "AMANI-4G-Home";
const char* password = "xxxxxxxxxxxx";
const char* mqtt_server = "192.168.8.130";
int mqtt_port = 1883;
const char* user_name = "mqtt"; // 連接 MQTT broker 的帳號密碼
const char* user_password = "mqtt";

// ESP8266訂閱的主題：收到 0 關閉 LED，1 打開LED
const char* topic_subscribe = "ha/bedroom/light/switch"; 
const char* topic_publish = "ha/bedroom/light/status";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup_wifi() { // 連接Wifi
  delay(10);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW); 
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) 
{
  Serial.print("Command from MQTT broker is : [");
  Serial.print(topic);
  int p =(char)payload[0]-'0';
 
  if(p==0) // MQTT 傳來 0 熄滅 D2 上的 LED
  {
    digitalWrite(D2, LOW); 
    Serial.println(" Turn Off LED! " );
  } 
  
  if(p==1) // MQTT 傳來 1 點亮 D2 上的 LED
  {
    digitalWrite(D2, HIGH); 
    Serial.println(" Turn On LED! " );
  }
  Serial.println();
} //end callback

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(),user_name,user_password)) {
      Serial.println("connected");
      client.subscribe(topic_subscribe);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(serial_speed);
  pinMode(D2, OUTPUT);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  
}
void loop() {
    
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
