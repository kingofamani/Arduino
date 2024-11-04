//Generated Date: Mon, 16 Oct 2023 02:49:26 GMT

#include <WiFi.h>
#define ARDUINOJSON_DECODE_UNICODE 1
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>

char _lwifi_ssid[] = "tyes-itc";
char _lwifi_pass[] = "xxxxxxxxx";

//UART通訊
SoftwareSerial ArduinoSerial(16,17);
const char* GOODS_LOAD = "goodsLoad";

//LED燈
int pinLed = 15;

//======google 試算表 Start======
String sheetId="1f71BEclyLg4eY5kjp_WkziDRxtcsAhCc8r_EkY0yyPo";//試算表id
String sheetTag="";
const char* sTag = "order";//工作表名稱
//asId不要變更
const char* asId="AKfycbyR-Yp-uu4nIvnjvnkILaQ5AX8yFxp-UpBO-Sqs0su3ai1N_BvQsz_Q";
DynamicJsonDocument docSheet(2048);

//收件人資料(格式:姓名,商品,倉庫X,倉庫Y,收件人X,收件人Y)
String recipient[6];
String strRecipient="";
//======google 試算表 End======

//---- HiveMQ設定 Start -----
const char* mqtt_server = "8a05a03895e647a1b352aa8823be3a68.s2.eu.hivemq.cloud";
const char* mqtt_username = "kingofamani";                                        
const char* mqtt_password = "xxxxxxxxx";                                    
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

//訂閱的主題回覆
void callback(char* topic, byte* payload, unsigned int length) {
  


  mqttGetMsg = "";
  for (int i = 0; i < length; i++) {
    mqttGetMsg += (char)payload[i];
  }
  mqttGetMsg.trim();  
  Serial.println(String(topic));
  Serial.println(mqttGetMsg);
  
  //接收Topic主題的消息Msg
  if (String(topic) == TOPIC_CAR_STANDBY) {
    //LED亮
    digitalWrite(pinLed,HIGH);

    //google表單查詢收貨人
	readGoogleSheet();
  Serial.println(String()+recipient[2]+","+recipient[3]);
	
	//傳送訊息至UNO:依商品xy座標 自動撿貨
	pickGoods(recipient[2],recipient[3]);  

//LED暗
  digitalWrite(pinLed,LOW);
  }

}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection… ");
    String clientId = "ESP32ClientGoods";
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
//---- HiveMQ設定 End -----

//======google 試算表 函數 Start======
String URLEncode(const char* msg)
{
  const char *hex = "0123456789abcdef";
  String encodedMsg = "";
  while (*msg!='\0'){
      if( ('a' <= *msg && *msg <= 'z')
              || ('A' <= *msg && *msg <= 'Z')
              || ('0' <= *msg && *msg <= '9') ) {
          encodedMsg += *msg;
      } else {
          encodedMsg += '%';
          encodedMsg += hex[*msg >> 4];
          encodedMsg += hex[*msg & 15];
      }
      msg++;
  }
  return encodedMsg;
}

void searchSheet(const String& fname, const String& sname){
  static WiFiClientSecure sheetClient;
  sheetClient.setInsecure();
  const char* host="script.google.com";
  String newUrl="";
  sheetClient.connect(host, 443);
  while (!sheetClient.connected());
  const String url = String() +"https://"+host+"/macros/s/"+asId+"/exec?type=search&sheetId="+sheetId+"&sheetTag="+sheetTag+"&fname="+fname+"&sname="+sname;
  sheetClient.print("GET " + url + " HTTP/1.1\n"+String()+"Host: "+host+"\nAccept: */*\nConnection: close\n\n\n");
  while (!newUrl.startsWith("https:")){
    newUrl = sheetClient.readStringUntil('\n');
    if (newUrl.startsWith("Location: https://")) {
      newUrl.replace("Location: ","");
      break;
    }
  }
  sheetClient.stop();
  String jsonData ="";
  sheetClient.connect(host, 443);
  while (!sheetClient.connected());
  sheetClient.print("GET " + newUrl + " HTTP/1.1\n"+String()+"Host: "+host+"\nAccept: */*\nConnection: close\n\n\n");
  while(!jsonData.startsWith("{")){
    jsonData = sheetClient.readStringUntil('\n');
    if (jsonData.startsWith("{")) {
      DeserializationError error = deserializeJson(docSheet, jsonData);
      break;
    }
  }
  sheetClient.stop();
}

void readGoogleSheet(){
	//讀取Google試算表
  sheetTag=URLEncode(sTag);//工作表名稱
  searchSheet("A",URLEncode(String("陳大春").c_str()).c_str());
  recipient[0] = String(docSheet["A"].as<String>());//姓名
  recipient[1] = String(docSheet["B"].as<String>());//商品
  recipient[2] = String(docSheet["C"].as<String>());//倉庫X
  recipient[3] = String(docSheet["D"].as<String>());//倉庫Y
  recipient[4] = String(docSheet["E"].as<String>());//收件人X
  recipient[5] = String(docSheet["F"].as<String>());//收件人Y
  
  strRecipient="";
  for(int i=0;i<6;i++){
	strRecipient += recipient[i] + ",";
    //Serial.println(recipient[i]);
  }
}
//======google 試算表 函數 End======

void setup()
{
  Serial.begin(9600);  
  ArduinoSerial.begin(9600);

  //LED
  pinMode(pinLed,OUTPUT);
  digitalWrite(pinLed,LOW);

  //Wifi初始
  WiFi.disconnect();
  WiFi.softAPdisconnect(true);
  WiFi.mode(WIFI_STA);
  WiFi.begin(_lwifi_ssid, _lwifi_pass);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }
  delay(300);
  
  //MQTT初始
  espClient.setCACert(root_ca);
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  if (!client.connected()) {
    reconnect();
  }

  //MQTT Topic訂閱
  client.subscribe(TOPIC_CAR_STANDBY);
  
 }

void loop()
{
	//MQTT啟動
	client.loop();
	
	//接收訊息：Arduino→ESP32
	UartGetFromArduino();

}

void pickGoods(String strX,String strY){
	//int x = strX.toInt();
	//int y = strY.toInt();
	UartSentToArduino(strX+strY);//格式xy(例如13)
	
}

//傳送訊息：ESP32→Arduino
void UartSentToArduino(String msg){
  ArduinoSerial.print(msg);
//  if(Serial.available()){
//    String msg=Serial.readString();
//    ArduinoSerial.print(msg);
//  }
}

//接收訊息：Arduino→ESP32
void UartGetFromArduino(){
  while(ArduinoSerial.available()){
    String val=ArduinoSerial.readString();
    Serial.print("Arduino→ESP32: ");   
    Serial.println(val);   
	if(val==GOODS_LOAD){
		//發送MQTT：TOPIC_GOODS_LOAD
    const char* msg = strRecipient.c_str();
		mqttSendMsg = const_cast<char*>(msg);		
		client.publish(TOPIC_GOODS_LOAD, mqttSendMsg);
	}
  }
}
