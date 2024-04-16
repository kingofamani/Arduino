#include <LedControl.h>
#include <Wire.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>

//佈置
#define BUTTON_PIN 5

//地圖表示，0表示障礙物，1表示可通行
int grid[4][6] = {
  { 1, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1 },
};
String strGrid = "1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1";

//鍵盤值
char i2cKey = '\0';  //不能是null

//按下鍵盤，回傳此按鈕位於二維陣列的索引值(ex:按下C,回傳x=2,y=3)
int keyX = 0;
int keyY = 0;

//每次按下按鍵間隔時間(避免按鍵repeat)
unsigned long preMillisKeyPress;

//16顆大燈
int bigLeds[4][4][2];
//8x8LED腳位配置: DIN, CLK, CS, 1
LedControl lc = LedControl(13, 14, 27, 1);



//---- WiFi settings
const char* ssid = "tyes-itc";
const char* password = "xxxxxxxxx";

//---- HiveMQ Cloud Broker settings
const char* mqtt_server = "8a05a03895e647a1b352aa8823be3a68.s2.eu.hivemq.cloud";//"imi-1oj8cr.a02.usw2.aws.hivemq.cloud";  // replace with your HiveMQ Cluster URL
const char* mqtt_username = "kingofamani";                                        // replace with your Username
const char* mqtt_password = "xxxxxxxxx";                                    // replace with your Password
const int mqtt_port = 8883;

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


// HiveMQ Cloud Let's Encrypt CA certificate
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

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
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

//訂閱的主題回覆
void callback(char* topic, byte* payload, unsigned int length) {
  String strMsg = "";
  Serial.print("接收訊息 [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    strMsg += (char)payload[i];
  }
  strMsg.trim();
  Serial.println(strMsg);
}

void reconnect() {
  // Loop until we’re reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection… ");
    String clientId = "ESP32ClientMap";
    // Attempt to connect
    if (client.connect(clientId.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("connected!");
      //client.publish(TOPIC_MAP_SET, "Hello World!");
    } else {
      Serial.print("failed, rc = ");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setBigLed(int ary[], bool sw) {
  //地圖0為障礙物要亮，所以改成!sw
  lc.setLed(0, ary[0], ary[1], !sw);
  lc.setLed(0, ary[0] + 1, ary[1], !sw);
  lc.setLed(0, ary[0], ary[1] + 1, !sw);
  lc.setLed(0, ary[0] + 1, ary[1] + 1, !sw);
}

void keypadLoop() {
  volatile int code;
  Wire.beginTransmission(0x27);
  Wire.write(3);
  Wire.endTransmission();
  Wire.requestFrom(0x27, 1);
  while (Wire.available()) {
    if (millis() - preMillisKeyPress >= 200) {
      code = Wire.read();
      if (code != 16) {
        i2cKey = getKey(code);  //將按鍵code轉成鍵盤值
        codeToArray(code);      //將按鍵code轉成xy座標
      }

      preMillisKeyPress = millis();
    }
  }
}
char getKey(int code) {
  char keys[16] = {
    '0', '1', '2', '3',
    '4', '5', '6', '7',
    '8', '9', 'A', 'B',
    'C', 'D', '*', '#'
  };
  return keys[code];
}

boolean checkIsNumber(char key) {
  char N[] = "1234567890";
  //一定要大寫NULL
  if ((strchr(N, key)) != (NULL)) {
    return (true);
  } else {
    return (false);
  }
}

//將按鍵位置轉換成二維陣列
void codeToArray(int code) {
  int arrayPos[16] = {
    13, 0, 1, 2,
    4, 5, 6, 8,
    9, 10, 3, 7,
    11, 15, 12, 14
  };

  int index = arrayPos[code];  //一維陣列的索引值
  keyX = index / 4;            //二維陣列的索引值
  keyY = index % 4;            //二維陣列的索引值
}

void twoToOneArray() {
  strGrid = "";
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 6; j++) {
      strGrid += String(grid[i][j]) + ",";
    }
  }
  //Serial.println(strGrid);
}

void resetAll() {
  strGrid = "1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1";
  i2cKey = '\0';
  keyX = 0;
  keyY = 0;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 6; j++) {
      grid[i][j] = 1;
    }
  }

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      setBigLed(bigLeds[i][j], grid[i][j + 1]);
    }
  }
}

void setup() {
  delay(500);
  // When opening the Serial Monitor, select 9600 Baud
  Serial.begin(9600);
  delay(500);

  setup_wifi();

  espClient.setCACert(root_ca);
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  //I2C初始
  Wire.begin();

  preMillisKeyPress = millis();

  //LED初始
  lc.shutdown(0, false);  // 醒來
  lc.setIntensity(0, 8);  // 設置亮度 (0~15)
  lc.clearDisplay(0);     // 清除顯示

  //設定LED燈位置
  for (int i = 0; i <= 3; i++) {
    for (int j = 0; j <= 3; j++) {
      bigLeds[i][j][0] = i * 2;
      bigLeds[i][j][1] = j * 2;
    }
  }

  //按鈕I/O
  pinMode(BUTTON_PIN, INPUT);

}

void loop() {
  //MQTT啟動
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  //偵測鍵盤
  keypadLoop();
  if (i2cKey != '\0') {
    grid[keyX][keyY + 1] = grid[keyX][keyY + 1] ^ 1;  //gird前4、後4不能擺障礙物，所以Y值要加1

    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        setBigLed(bigLeds[i][j], grid[i][j + 1]);
      }
    }

    //二維轉一維
    twoToOneArray();

    i2cKey = '\0';
  }

  //按佈置鈕
  if (digitalRead(BUTTON_PIN) == 1) {
    //發送MQTT：TOPIC_MAP_SET
    const char* msg = strGrid.c_str();
    mqttSendMsg = const_cast<char*>(msg);
    client.publish(TOPIC_MAP_SET, mqttSendMsg);
    delay(100);

    //歸零
    resetAll();
    delay(2000);
  }
}