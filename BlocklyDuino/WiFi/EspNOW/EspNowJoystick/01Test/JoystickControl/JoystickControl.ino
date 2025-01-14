//Generated Date: Tue, 22 Oct 2024 01:47:40 GMT

#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>
#define PRINTSCANRESULTS 0
#define DELETEBEFOREPAIR 0

esp_now_peer_info_t slave;
String recBroadcastStr="";
boolean receivedBroadcast=false;
uint8_t broadcastChannel=1;
char sourceMacChar[18]={ };
char selfMacChar[18]={ };

String myDir = "";
const int x_joy_pin1 = 32;    //VRx
const int y_joy_pin1 = 33;   //VRy
const int sw_joy_pin1 = 13;  //SW
int angle_joy1 = 0;          //旋轉角度

String directs[8] = { "u", "ur", "r", "dr", "d", "dl", "l", "ul" };
const int coord_center[2] = { 1700, 2000 };  //x,y的中心位置範圍
const int coord_max = 4095;                  //x,y的最大值

void InitESPNow() {
  if (esp_now_init() == ESP_OK) {
    Serial.println("ESPNow Init Success");
  }
  else {
    Serial.println("ESPNow Init Failed");
    ESP.restart();
  }
}

void initBroadcastSlave() {
  memset(&slave, 0, sizeof(slave));
  for (int ii = 0; ii < 6; ++ii)
    slave.peer_addr[ii] = (uint8_t)0xff;
  slave.channel = broadcastChannel;
  slave.encrypt = 0;
  manageSlave();
}

bool manageSlave() {
  if (slave.channel == broadcastChannel) {
    if (DELETEBEFOREPAIR) {
      deletePeer();
    }
    const esp_now_peer_info_t *peer = &slave;
    const uint8_t *peer_addr = slave.peer_addr;
    bool exists = esp_now_is_peer_exist(peer_addr);
    if (exists) {
      return true;
    }
    else {
      esp_err_t addStatus = esp_now_add_peer(peer);
      if (addStatus == ESP_OK) {
        return true;
     }
      else if (addStatus == ESP_ERR_ESPNOW_NOT_INIT) {
        return false;
      }
      else if (addStatus == ESP_ERR_ESPNOW_ARG) {
        return false;
     }
      else if (addStatus == ESP_ERR_ESPNOW_FULL) {
        return false;
      }
      else if (addStatus == ESP_ERR_ESPNOW_NO_MEM) {
        return false;
      }
      else if (addStatus == ESP_ERR_ESPNOW_EXIST) {
        return true;
      }
      else {
        return false;
      }
   }
  }
  else {
    return false;
  }
}

void deletePeer() {
  const esp_now_peer_info_t *peer = &slave;
  const uint8_t *peer_addr = slave.peer_addr;
  esp_err_t delStatus = esp_now_del_peer(peer_addr);
}

void sendBroadcastData(String broadcastSendStr) {
  const char* tempChar=broadcastSendStr.c_str();
  uint8_t dataToSend[broadcastSendStr.length()+1];
  memcpy(dataToSend, tempChar, broadcastSendStr.length()+1);
  const uint8_t *peer_addr = slave.peer_addr;
  Serial.print("Sending: "); Serial.println((const char*)dataToSend);
  esp_err_t result = esp_now_send(peer_addr, dataToSend, broadcastSendStr.length()+1);
}

void onBroadcastDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len){
  snprintf(sourceMacChar, sizeof(sourceMacChar),"%02x:%02x:%02x:%02x:%02x:%02x",mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  recBroadcastStr=String((const char*)data);
  receivedBroadcast=true;
}

void getMyMacAddr(){
  uint8_t mac_addr[6];
  WiFi.macAddress(mac_addr);
  snprintf(selfMacChar, sizeof(selfMacChar),"%02x:%02x:%02x:%02x:%02x:%02x",mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
}

void setup()
{
  Serial.begin(9600);

    analogReadResolution(12);  //4095

  pinMode(13, INPUT_PULLUP);
  //要溝通的開發板必須設定同一個頻道
  broadcastChannel=1;
  WiFi.mode(WIFI_STA);
  InitESPNow();
  esp_wifi_set_promiscuous(true);
  esp_wifi_set_channel(broadcastChannel, WIFI_SECOND_CHAN_NONE);
  esp_wifi_set_promiscuous(false);
  esp_now_register_recv_cb(onBroadcastDataRecv);
  initBroadcastSlave();
  getMyMacAddr();
  Serial.print("自己的MAC:");
  Serial.println(selfMacChar);
}

void loop()
{
  myDir = getDirect(angle_joy1, analogRead(x_joy_pin1), analogRead(y_joy_pin1));
  if (myDir != "") {
    sendBroadcastData(String(myDir));
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
