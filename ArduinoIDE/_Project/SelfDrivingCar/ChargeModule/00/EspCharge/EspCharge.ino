//Generated Date: Sat, 23 Dec 2023 13:07:19 GMT

#include <WiFi.h>
 #include <WiFiClientSecure.h>
 #include <Wire.h>
 #include <Adafruit_INA219.h>
 //https://docs.google.com/spreadsheets/d/1EhpZyQILsXqWKgGFPZdoaBGQzfcb2x20n4-tTqJc-uI/edit#gid=399078205
 //====變數設定 Start====
   //WiFi
  const char* ssid = "xxxxxxx";
  const char* password = "xxxxxxx";
  //google 試算表
  String sheetId="xxxxxxx";//試算表id
  String sheetTag="";
  const char* sTag = "charge";//工作表名稱
//====變數設定 End====
 //asId不要變更
 const char* asId="AKfycbyR-Yp-uu4nIvnjvnkILaQ5AX8yFxp-UpBO-Sqs0su3ai1N_BvQsz_Q";

 //測電流電壓
 float shuntvoltage = 0;
 float busvoltage = 0;
 float current_mA = 0;
 float loadvoltage = 0;
 float power_mW = 0;
 Adafruit_INA219 ina219Bat;//太陽能→14500鋰電池
 Adafruit_INA219 ina219Car;//14500鋰電池→小車
 //紀錄上一次上傳google sheet時間
 unsigned long preMillisBat;
 unsigned long preMillisCar;


void setup()
{
    Serial.begin(9600);
  while (!Serial) {delay(1);}
  delay(500);
  setup_wifi();

  //測電流電壓初始
  if (! ina219Bat.begin()) {
    Serial.println("Failed to find ina219Bat chip");
    while (1) { delay(10); }
  }
  if (! ina219Car.begin()) {
    Serial.println("Failed to find ina219Car chip");
    while (1) { delay(10); }
  }


}

void loop()
{
  batCharging();
  carCharging();
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
void  sendToGoogleSheets(const String& dateInclude,const String& data)
{
  sheetTag=URLEncode(sTag);
  static WiFiClientSecure sheetClient;
  sheetClient.setInsecure();
  const char* host="script.google.com";
  if (sheetClient.connect(host, 443)) {
      const String url = String() +"https://"+host+"/macros/s/"+asId+"/exec?type=insert&dateInclude="+dateInclude+"&sheetId="+sheetId+"&sheetTag="+sheetTag+"&data="+data;
      sheetClient.println("GET " + url + " HTTP/1.1");
      sheetClient.println(String()+"Host: "+host);
      sheetClient.println("Accept: */*");
      sheetClient.println("Connection: close");
      sheetClient.println();
      sheetClient.println();
      sheetClient.stop();
  }
}
void batCharging(){
    int interval = 31;//每隔幾秒紀錄一次
  if(millis()-preMillisBat>=interval*1000){
      preMillisBat = millis();

      shuntvoltage = ina219Bat.getShuntVoltage_mV();
      busvoltage = ina219Bat.getBusVoltage_V();//Bus Voltage電池電壓(V)
      current_mA = ina219Bat.getCurrent_mA();//Current負載電流(mA)
      power_mW = ina219Bat.getPower_mW();//Power負載功率(mW)
      loadvoltage = busvoltage + (shuntvoltage / 1000);//Load Voltage負載電壓(V)

      //寫入google試算表
      if(power_mW>0){
        sendToGoogleSheets("1",URLEncode((String() + "太陽能板產生能量" + "," + power_mW + "," + interval).c_str()));
      }
  }
}
void carCharging(){
    int interval = 61;//每隔幾秒紀錄一次
  if(millis()-preMillisCar>=interval*1000){
      preMillisCar = millis();

      shuntvoltage = ina219Car.getShuntVoltage_mV();
      busvoltage = ina219Car.getBusVoltage_V();//Bus Voltage電池電壓(V)
      current_mA = ina219Car.getCurrent_mA();//Current負載電流(mA)
      power_mW = ina219Car.getPower_mW();//Power負載功率(mW)
      loadvoltage = busvoltage + (shuntvoltage / 1000);//Load Voltage負載電壓(V)

      //寫入google試算表
      if(power_mW>0){
        sendToGoogleSheets("1",URLEncode((String() + "小車消耗能量" + "," + power_mW + "," + interval).c_str()));
      }
  }
}
