//Generated Date: Wed, 27 Dec 2023 11:41:22 GMT

#include <WiFi.h>
 #include <PubSubClient.h>
 #include <WiFiClientSecure.h>
 //===設定變數 Start===
   //WiFi設定
  const char* ssid = "xxxxxx";
  const char* password = "xxxxxx";
  //HiveMQ設定
  const char* mqtt_server = "xxxxxx";
  const char* mqtt_username = "xxxxxx";
  const char* mqtt_password = "xxxxxx";
  const int mqtt_port = 8883;
  //佈置
  #define BUTTON_PIN 3
  int grid[4][6] = {
         { 1,1,1,1,1,1},
        { 1,1,1,1,1,1},
        { 1,1,1,1,1,1},
        { 1,1,1,1,1,1},
  };
   //===設定變數 End===
 String strGrid="";
 //Topic主題
 const char* TOPIC_MAP_SET = "imiRobot/map/set";
 const char* TOPIC_CAR_STANDBY = "imiRobot/car/standby";
 const char* TOPIC_CAR_GPS = "imiRobot/car/gps";
 const char* TOPIC_GOODS_LOAD = "imiRobot/goods/load";
 const char* TOPIC_CAR_LOWPOWER = "imiRobot/car/lowPower";
 //發佈者 傳送的消息內容
 char* mqttSendMsg = "";
 //訂閱者 接收的消息內容
 String mqttGetMsg = "";
 WiFiClientSecure espClient;
 PubSubClient client(espClient);
 // HiveMQ Cloud
 static const char* root_ca PROGMEM = R"EOF(
 -----BEGIN CERTIFICATE-----
 MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw
 TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh
 cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMTUwNjA0MTEwNDM4
 WhcNMzUwNjA0MTEwNDM4WjBPMQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJu
 ZXQgU2VjdXJpdHkgUmVzZWFyY2ggR3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBY
 MTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAK3oJHP0FDfzm54rVygc
 h77ct984kIxuPOZXoHj3dcKi/vVqbvYATyjb3miGbESTtrFj/RQSa78f0uoxmyF+
 0TM8ukj13Xnfs7j/EvEhmkvBioZxaUpmZmyPfjxwv60pIgbz5MDmgK7iS4+3mX6U
 A5/TR5d8mUgjU+g4rk8Kb4Mu0UlXjIB0ttov0DiNewNwIRt18jA8+o+u3dpjq+sW
 T8KOEUt+zwvo/7V3LvSye0rgTBIlDHCNAymg4VMk7BPZ7hm/ELNKjD+Jo2FR3qyH
 B5T0Y3HsLuJvW5iB4YlcNHlsdu87kGJ55tukmi8mxdAQ4Q7e2RCOFvu396j3x+UC
 B5iPNgiV5+I3lg02dZ77DnKxHZu8A/lJBdiB3QW0KtZB6awBdpUKD9jf1b0SHzUv
 KBds0pjBqAlkd25HN7rOrFleaJ1/ctaJxQZBKT5ZPt0m9STJEadao0xAH0ahmbWn
 OlFuhjuefXKnEgV4We0+UXgVCwOPjdAvBbI+e0ocS3MFEvzG6uBQE3xDk3SzynTn
 jh8BCNAw1FtxNrQHusEwMFxIt4I7mKZ9YIqioymCzLq9gwQbooMDQaHWBfEbwrbw
 qHyGO0aoSCqI3Haadr8faqU9GY/rOPNk3sgrDQoo//fb4hVC1CLQJ13hef4Y53CI
 rU7m2Ys6xt0nUW7/vGT1M0NPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNV
 HRMBAf8EBTADAQH/MB0GA1UdDgQWBBR5tFnme7bl5AFzgAiIyBpY9umbbjANBgkq
 hkiG9w0BAQsFAAOCAgEAVR9YqbyyqFDQDLHYGmkgJykIrGF1XIpu+ILlaS/V9lZL
 ubhzEFnTIZd+50xx+7LSYK05qAvqFyFWhfFQDlnrzuBZ6brJFe+GnY+EgPbk6ZGQ
 3BebYhtF8GaV0nxvwuo77x/Py9auJ/GpsMiu/X1+mvoiBOv/2X/qkSsisRcOj/KK
 NFtY2PwByVS5uCbMiogziUwthDyC3+6WVwW6LLv3xLfHTjuCvjHIInNzktHCgKQ5
 ORAzI4JMPJ+GslWYHb4phowim57iaztXOoJwTdwJx4nLCgdNbOhdjsnvzqvHu7Ur
 TkXWStAmzOVyyghqpZXjFaH3pO3JLF+l+/+sKAIuvtd7u+Nxe5AW0wdeRlN8NwdC
 jNPElpzVmbUq4JUagEiuTDkHzsxHpFKVK7q4+63SM1N95R1NbdWhscdCb+ZAJzVc
 oyi3B43njTOQ5yOf+1CceWxG1bQVs5ZufpsMljq4Ui0/1lvh+wjChP4kqKOJ2qxq
 4RgqsahDYVvTH9w7jXbyLeiNdd8XM2w9U/t7y0Ff/9yi0GE44Za4rF2LN9d11TPA
 mRGunUHBcnWEvgJBQl9nJEiU0Zsnvgc/ubhPgXRR4Xq37Z0j4r7g1SgEEzwxA57d
 emyPxgcYxn/eR44/KJ4EBs+lVDR3veyJm+kXQ99b21/+jh5Xos1AnX5iItreGCc=
 -----END CERTIFICATE-----
 )EOF";


void setup()
{
    delay(500);
  Serial.begin(9600);
  delay(500);
  setup_wifi();
  //按鈕I/O
  pinMode(BUTTON_PIN, INPUT);
  //MQTT初始
  espClient.setCACert(root_ca);
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  if (!client.connected()) {
    reconnect();
  }
  //取得佈置地圖陣列(Seeds)
  // 地圖表示，0表示障礙物，1表示可通行
  strGrid = "";
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 6; j++) {
      strGrid += grid[i][j] +",";
    }
  }


}

void loop()
{
  //MQTT啟動
    client.loop();
  if (digitalRead(BUTTON_PIN)==1) {
    //發送MQTT：TOPIC_MAP_SET
        const char* msg = strGrid.c_str();
        mqttSendMsg = const_cast<char*>(msg);
        client.publish(TOPIC_MAP_SET, mqttSendMsg);
  }
}

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
//MQTT訂閱的主題回覆
void callback(char* topic, byte* payload, unsigned int length) {
}
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection… ");
    String clientId = "ESP32Client";
    if (client.connect(clientId.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("connected!");
    } else {
      Serial.print("failed, rc = ");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}
