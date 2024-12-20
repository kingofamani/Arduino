//Generated Date: Fri, 18 Oct 2024 02:06:05 GMT

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

void myCheckEspNow(){
  if (String(sourceMacChar) == "08:d1:f9:14:ad:a0") {
    Serial.println(recBroadcastStr);
  }
}

void checkBroadcastEspNow(){
  if (receivedBroadcast){
    myCheckEspNow();
    receivedBroadcast=false;
  }
}

void setup()
{
  Serial.begin(9600);

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
  checkBroadcastEspNow();

}
