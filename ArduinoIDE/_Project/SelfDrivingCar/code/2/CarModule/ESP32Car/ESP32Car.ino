//Generated Date: Tue, 26 Dec 2023 07:46:32 GMT

#include <SoftwareSerial.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
//與Mega通訊
const char* MAP_SET = "mapSet";
const char* GOODS_LOAD = "goodsLoad";
const char* LINE_NOTIFY = "lineNotify";
const char* CAR_GPS = "carGps";
const char* CAR_LOWPOWER = "carLowpower";
//===設定程式碼input Start===
//===設定程式碼input End===
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
//UART通訊
SoftwareSerial MegaSerial(16, 17);
//WiFi設定
const char* ssid = "tyes-itc";
const char* password = "xxxxxxxxx";
//LINE權杖
String lineToken = "9Z2jip3H82ntSUTPDCHjLbsDIiBWhBRvtBjkRM31scb";
//---- HiveMQ設定 Start -----
const char* mqtt_server = "8a05a03895e647a1b352aa8823be3a68.s2.eu.hivemq.cloud";//"imi-1oj8cr.a02.usw2.aws.hivemq.cloud";
const char* mqtt_username = "kingofamani";
const char* mqtt_password = "xxxxxxxxx";
const int mqtt_port = 8883;


void setup() {
  delay(500);
  Serial.begin(9600);
  delay(500);
  MegaSerial.begin(9600);
  delay(500);
  setup_wifi();
  //MQTT初始
  espClient.setCACert(root_ca);
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  if (!client.connected()) {
    reconnect();
  }


  client.subscribe(TOPIC_MAP_SET);

  client.subscribe(TOPIC_GOODS_LOAD);

  client.subscribe(TOPIC_CAR_LOWPOWER);
}

void loop() {
  //MQTT啟動
  client.loop();
  //接收訊息：Mega→ESP32
  UartGetFromMega();
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection… ");
    String clientId = "ESP32ClientCar";
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
void sendLineMsg(String myMsg) {
  static WiFiClientSecure line_client;
  line_client.setInsecure();
  myMsg.replace("%", "%25");
  myMsg.replace("&", "%26");
  myMsg.replace("§", "&");
  myMsg.replace("\\n", "\n");
  if (line_client.connect("notify-api.line.me", 443)) {
    line_client.println("POST /api/notify HTTP/1.1");
    line_client.println("Connection: close");
    line_client.println("Host: notify-api.line.me");
    line_client.println("Authorization: Bearer " + lineToken);
    line_client.println("Content-Type: application/x-www-form-urlencoded");
    line_client.println("Content-Length: " + String(myMsg.length()));
    line_client.println();
    line_client.println(myMsg);
    line_client.println();
    line_client.stop();
  } else {
    Serial.println("Line Notify failed");
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
//傳送訊息：ESP32→Mega
void UartSentToMega(String msg) {
  MegaSerial.print(msg);
}

//訂閱的主題回覆
void callback(char* topic, byte* payload, unsigned int length) {
  mqttGetMsg = "";
  for (int i = 0; i < length; i++) {
    mqttGetMsg += (char)payload[i];
  }
  mqttGetMsg.trim();
  Serial.println(String(topic));
  Serial.println(mqttGetMsg);
  if (String(topic) == TOPIC_MAP_SET) {
    //儲存地圖陣列(格式:MAP_SET,4x6地圖陣列)
    UartSentToMega(String(MAP_SET) + "," + mqttGetMsg);
    delay(1000);
    //發送MQTT：TOPIC_CAR_STANDBY
    mqttSendMsg = "1";
    client.publish(TOPIC_CAR_STANDBY, mqttSendMsg);
    Serial.println("發佈TOPIC_CAR_STANDBY");
  } else if (String(topic) == TOPIC_GOODS_LOAD) {
    //開始送貨(格式:GOODS_LOAD,姓名,商品,倉庫X,倉庫Y,收件人X,收件人Y)
    UartSentToMega(String(GOODS_LOAD) + "," + mqttGetMsg);
  } else if (String(topic) == TOPIC_CAR_LOWPOWER) {
    //模擬小車低電壓(由HiveMQ平台發出)
    UartSentToMega(String(CAR_LOWPOWER) + "," + mqttGetMsg);
  }
}


//接收訊息：Mega→ESP32
void UartGetFromMega() {
  while (MegaSerial.available()) {
    String str = MegaSerial.readString();
    Serial.println(str);
    if (str.indexOf(LINE_NOTIFY) != -1) {
      //收貨人資料字串轉陣列
      String tmpArray[3];
      char* token = strtok((char*)str.c_str(), ",");
      int tokenLen = 0;
      while (token != NULL && tokenLen < 3) {
        tmpArray[tokenLen] = token;
        token = strtok(NULL, ",");
        tokenLen++;
      }
      //發送LINE
      sendLineMsg(String("message=\n")+tmpArray[0] + "您好：您的商品「" + tmpArray[1] + "」已送達，請至門口進行人臉識別簽收。");
    } else if (str.indexOf(CAR_GPS) != -1) {
      //座標字串轉陣列
      String arryGps[3];
      char* token = strtok((char*)str.c_str(), ",");
      int tokenLen = 0;
      while (token != NULL && tokenLen < 3) {
        arryGps[tokenLen] = token;
        token = strtok(NULL, ",");
        tokenLen++;
      }
      //發送MQTT：TOPIC_CAR_GPS(格式:xy,例如13)
      //    使用String結合x和y的內容
      //String xy = "0" + arryGps[1] + "0" + arryGps[2];
	  String xy =arryGps[1] + arryGps[2];
      //    將String轉換為const char*
      const char* msg = (xy).c_str();
      //    const char*轉char*
      mqttSendMsg = const_cast<char*>(msg);
      client.publish(TOPIC_CAR_GPS, mqttSendMsg);
    }
  }  //while
}
