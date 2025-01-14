#include <SoftwareSerial.h>
#include <AdafruitIO_WiFi.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>

//連接Arduino Mega
SoftwareSerial MegaSerial(16, 17);

// Adafruit IO 帳號資訊
#define IO_USERNAME "kingofamani"
#define IO_KEY "xxxxxxxx"

// WiFi 設定
#define WIFI_SSID "tyes-itc2"
#define WIFI_PASS "xxxxxxxx"

// 建立 Adafruit IO 物件
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// 定義訂閱的 Feed
AdafruitIO_Feed* controlDevice = io.feed("control-device");

//Google試算表
const char* asId = "AKfycbyR-Yp-uu4nIvnjvnkILaQ5AX8yFxp-UpBO-Sqs0su3ai1N_BvQsz_Q";
String sheetId = "xxxxxxxxxxxxxxxxxxxxx";
String sheetTag = "sensor";

void setup() {
  Serial.begin(9600);
  MegaSerial.begin(9600);

  // 連接至 Adafruit IO
  Serial.print("連接至 Adafruit IO...");
  io.connect();

  // 設定訂閱回調函式
  controlDevice->onMessage(handleMessage);

  // 等待連接成功
  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("連接成功！");
}

void loop() {
  // 維持 Adafruit IO 連線
  io.run();

  //接收訊息：Mega→ESP32
  while (MegaSerial.available()) {
    //收到fan,led,airctrl耗電量mWh
    //例如"0.03,0.01,10.78"
    String mWhs = MegaSerial.readString();
    Serial.println(mWhs);
    String tmpArray[3];
    char* token = strtok((char*)mWhs.c_str(), ",");
    int tokenLen = 0;
    while (token != NULL && tokenLen < 3) {
      tmpArray[tokenLen] = token;
      token = strtok(NULL, ",");
      tokenLen++;
    }

    //將數據上傳至Google試算表
    sendToGoogleSheets("1", URLEncode((String() + "國小A" + "," + "601" + "," + "風扇" + "," + "1" + "," + tmpArray[0]).c_str()));
    delay(2000);
    sendToGoogleSheets("1", URLEncode((String() + "國小A" + "," + "601" + "," + "電燈" + "," + "1" + "," + tmpArray[1]).c_str()));
    delay(2000);
    sendToGoogleSheets("1", URLEncode((String() + "國小A" + "," + "601" + "," + "冷氣" + "," + "1" + "," + tmpArray[2]).c_str()));
  }
}

// 處理訂閱訊息的回調函式
void handleMessage(AdafruitIO_Data* data) {
  //說明：電器只有冷氣airctrl、風扇fan、電燈led這3種而已。控制代碼(開=1、關=0)
  //例如：fan,1
  Serial.println(data->value());

  //傳送訊息：ESP32→Mega
  MegaSerial.print(data->value());
}

void sendToGoogleSheets(const String& dateInclude, const String& data) {
  static WiFiClientSecure sheetClient;
  sheetClient.setInsecure();
  const char* host = "script.google.com";
  if (sheetClient.connect(host, 443)) {
    const String url = String() + "https://" + host + "/macros/s/" + asId + "/exec?type=insert&dateInclude=" + dateInclude + "&sheetId=" + sheetId + "&sheetTag=" + sheetTag + "&data=" + data;
    sheetClient.println("GET " + url + " HTTP/1.1");
    sheetClient.println(String() + "Host: " + host);
    sheetClient.println("Accept: */*");
    sheetClient.println("Connection: close");
    sheetClient.println();
    sheetClient.println();
    sheetClient.stop();
  }
}

String URLEncode(const char* msg) {
  const char* hex = "0123456789abcdef";
  String encodedMsg = "";
  while (*msg != '\0') {
    if (('a' <= *msg && *msg <= 'z')
        || ('A' <= *msg && *msg <= 'Z')
        || ('0' <= *msg && *msg <= '9')) {
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
