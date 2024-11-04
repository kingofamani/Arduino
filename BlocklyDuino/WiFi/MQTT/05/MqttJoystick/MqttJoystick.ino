//Generated Date: Fri, 25 Oct 2024 01:43:37 GMT

#include <WiFi.h>
#include <PubSubClient.h>
#define MQTT_SERVER_IP "192.168.2.101"
#define MQTT_SERVER_PORT 1883
#define MQTT_ID "clientjoystick"
#define MQTT_USERNAME "kingofamani"
#define MQTT_PASSWORD "xxxxxxxx"

String myDir = "";
char _lwifi_ssid[] = "tyes-itc2";
char _lwifi_pass[] = "xxxxxxxx";
String receivedTopic="";
String receivedMsg="";
bool waitForE=true;
bool ended=true;
bool pubCtrl=false;

WiFiClient mqttClient;
PubSubClient myClient(mqttClient);

const int x_joy_pin1 = 32;    //VRx
const int y_joy_pin1 = 33;   //VRy
const int sw_joy_pin1 = 13;  //SW
int angle_joy1 = 0;          //旋轉角度

String directs[8] = { "u", "ur", "r", "dr", "d", "dl", "l", "ul" };
const int coord_center[2] = { 1700, 2000 };  //x,y的中心位置範圍
const int coord_max = 4095;                  //x,y的最大值

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

    analogReadResolution(12);  //4095

  pinMode(13, INPUT_PULLUP);
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
  Serial.println("MQTT連線成功");
}

void loop()
{
  myClient.loop();
  myDir = getDirect(angle_joy1, analogRead(x_joy_pin1), analogRead(y_joy_pin1));
  if ((digitalRead(sw_joy_pin1)) == 1) {
    myDir = "s";
  }
  if (myDir != "") {
    myClient.publish(String("car/direct").c_str(),String(myDir).c_str());
    Serial.println(myDir);
  }
  delay(300);
}

int getDirectIndex(int angle, int x, int y) {
  int index = 0;
  if (isCenter(x) && y == 0) {
    index = 0;  //上
  } else if (x == coord_max && y == 0) {
    index = 1;  //右上
  } else if (x == coord_max && isCenter(y)) {
    index = 2;  //右
  } else if (x == coord_max && y == coord_max) {
    index = 3;  //右下
  } else if (isCenter(x) && y == coord_max) {
    index = 4;  //下
  } else if (x == 0 && y == coord_max) {
    index = 5;  //左下
  } else if (x == 0 && isCenter(y)) {
    index = 6;  //左
  } else if (x == 0 && y == 0) {
    index = 7;  //左上
  } else if (isCenter(x) && isCenter(y)) {
    index = 99;  //中間
  }
  //取得旋轉後的index
  if (index == 99) {
    return index;
  } else {
    return index = getRotateIndex(angle, index);
  }
}
bool isCenter(int coord) {
  return (coord >= coord_center[0] && coord <= coord_center[1]);
}
int getRotateIndex(int angle, int direct_index) {
  int rotate[4] = { 0, 6, 4, 2 };  //旋轉後增加的index值
  int rotate_index = ((direct_index + 8) + rotate[angle / 90]) % 8;
  return rotate_index;
}
String getDirect(int angle, int x, int y) {
  int index = getDirectIndex(angle, x, y);
  if (index == 99) {
    return "";  //方向桿在中間
  } else {
    return directs[index];
  }
}
bool isDirect(String dir,int angle, int x, int y) {
  String direct = getDirect(angle,x,y);
  return direct == dir;
}
