#include <Base64_tool.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <time.h>
#include "esp_camera.h"
#include "esp_timer.h"
#include "img_converters.h"
#include "esp_http_server.h"
#include "Arduino.h"
//#include <SimpleTimer.h>

// Brown-out 偵測關閉(若穩定供電可拿掉)
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

//Google Drive連線
WiFiClientSecure clientGoogleDrive;

//網路時間
const char* ntpServer = "pool.ntp.org";  // 您可以使用預設或任何可用的 NTP 伺服器
const long  gmtOffset_sec = 8 * 3600;    // 您所在時區的 GMT 偏移量，例：GMT+8為8小時 * 3600秒 = 28800秒
const int   daylightOffset_sec = 0;      // 夏令時間偏移，沒有則為0



//計時器
//SimpleTimer timer;

// ========== 使用者設定區域 ==========
//Google Drive App Script ID
#define GOOGLE_APP_SCRIPT_ID "xxxxxxxxxxxxxx"

// WiFi 設定
const char *ssid = "tyes-itc2";
const char *password = "xxxxxxxxxxxxxx";

// Adafruit IO 帳號資訊
#define IO_USERNAME "kingofamani"
#define IO_KEY "xxxxxxxxxxxxxx"
const char *mqtt_server = "io.adafruit.com";
const int mqtt_port = 1883;

// Feed 名稱
#define FEED_NAME "control-cam"

// ========== Camera Pin 設定(ESP32-CAM) ==========
#define PWDN_GPIO_NUM 32
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM 0
#define SIOD_GPIO_NUM 26
#define SIOC_GPIO_NUM 27
#define Y9_GPIO_NUM 35
#define Y8_GPIO_NUM 34
#define Y7_GPIO_NUM 39
#define Y6_GPIO_NUM 36
#define Y5_GPIO_NUM 21
#define Y4_GPIO_NUM 19
#define Y3_GPIO_NUM 18
#define Y2_GPIO_NUM 5
#define VSYNC_GPIO_NUM 25
#define HREF_GPIO_NUM 23
#define PCLK_GPIO_NUM 22

// HTTP server handle
httpd_handle_t camera_httpd = NULL;

// WiFi、MQTT 物件
WiFiClient client;
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

// 建立 MQTT Client 物件
Adafruit_MQTT_Client mqtt(&client, mqtt_server, mqtt_port, IO_USERNAME, IO_KEY);

// 訂閱 Feed
Adafruit_MQTT_Subscribe controlCam = Adafruit_MQTT_Subscribe(&mqtt, IO_USERNAME "/feeds/" FEED_NAME);

// 影像串流處理 handler
static esp_err_t stream_handler(httpd_req_t *req) {
  camera_fb_t *fb = NULL;
  esp_err_t res = ESP_OK;
  size_t _jpg_buf_len = 0;
  uint8_t *_jpg_buf = NULL;
  char part_buf[64];

  static const char *_STREAM_CONTENT_TYPE = "multipart/x-mixed-replace;boundary=frame";
  static const char *_STREAM_BOUNDARY = "\r\n--frame\r\n";
  static const char *_STREAM_PART = "Content-Type: image/jpeg\r\nContent-Length: %u\r\n\r\n";

  res = httpd_resp_set_type(req, _STREAM_CONTENT_TYPE);
  if (res != ESP_OK) {
    return res;
  }

  while (true) {
    fb = esp_camera_fb_get();
    if (!fb) {
      Serial.println("Camera capture failed");
      httpd_resp_send_500(req);
      return ESP_FAIL;
    }

    if (fb->format != PIXFORMAT_JPEG) {
      bool jpeg_converted = frame2jpg(fb, 80, &_jpg_buf, &_jpg_buf_len);
      esp_camera_fb_return(fb);
      if (!jpeg_converted) {
        Serial.println("JPEG compression failed");
        httpd_resp_send_500(req);
        return ESP_FAIL;
      }
    } else {
      _jpg_buf_len = fb->len;
      _jpg_buf = fb->buf;
    }

    if (httpd_resp_send_chunk(req, _STREAM_BOUNDARY, strlen(_STREAM_BOUNDARY)) != ESP_OK) {
      if (fb->format != PIXFORMAT_JPEG) free(_jpg_buf);
      esp_camera_fb_return(fb);
      break;
    }

    size_t hlen = snprintf(part_buf, 64, _STREAM_PART, _jpg_buf_len);
    if (httpd_resp_send_chunk(req, part_buf, hlen) != ESP_OK) {
      if (fb->format != PIXFORMAT_JPEG) free(_jpg_buf);
      esp_camera_fb_return(fb);
      break;
    }

    if (httpd_resp_send_chunk(req, (const char *)_jpg_buf, _jpg_buf_len) != ESP_OK) {
      if (fb->format != PIXFORMAT_JPEG) free(_jpg_buf);
      esp_camera_fb_return(fb);
      break;
    }

    if (fb->format != PIXFORMAT_JPEG) free(_jpg_buf);
    esp_camera_fb_return(fb);
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
  return ESP_OK;
}

static void startCameraServer() {
  httpd_config_t config = HTTPD_DEFAULT_CONFIG();
  config.server_port = 80;  // 預設80埠
  httpd_uri_t stream_uri = {
    .uri = "/",
    .method = HTTP_GET,
    .handler = stream_handler,
    .user_ctx = NULL
  };

  if (httpd_start(&camera_httpd, &config) == ESP_OK) {
    httpd_register_uri_handler(camera_httpd, &stream_uri);
  }
}

// 自行管理 WiFi 連線
void connectToWiFi() {
  Serial.print("連接中: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  long startTime = millis();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (millis() - startTime > 20000) {
      Serial.println("\nWiFi連線逾時，重啟裝置");
      ESP.restart();
    }
  }
  Serial.println("");
  Serial.print("WiFi連線成功，IP位址: ");
  Serial.println(WiFi.localIP());
}

// Camera 初始化
void initCamera() {
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  // 適度降低影像解析度與提高壓縮
  if (psramFound()) {
    config.frame_size = FRAMESIZE_SVGA;  // 中等解析度
    config.jpeg_quality = 12;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_VGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x\n", err);
    delay(2000);
    ESP.restart();
  }

  sensor_t *s = esp_camera_sensor_get();
  s->set_vflip(s, 1);    // 垂直翻轉
  s->set_hmirror(s, 1);  // 水平翻轉
}

// 當訂閱的 Feed 有新資料時的回調 (使用 MQTT 下層機制)
void handleControlCamMessage(char *data, uint16_t len) {
  Serial.print("收到控制訊息：");//START_PLANT_CAM或START_TRASH_CAM
  String message = String(data).substring(0, len);
  Serial.println(message);
  if(message == "START_PLANT_CAM"){
    message = "plant";
  }else if(message == "START_TRASH_CAM"){
    message = "trash";
  }
  
  //上傳Google Drive
  String dateStr = formatDateToYMD();
  //SendStillToGoogleDrive(String("/macros/s/")+ GOOGLE_APP_SCRIPT_ID +String("/exec"), String("&myFoldername=")+urlencode("AiClassroom/images/"), dateStr +","+urlencode(message), String("&myLineType=")+"", String("&myToken=")+urlencode(""), String("&myUserID=")+urlencode(""), "&myFile=");
  SendStillToGoogleDrive(
    String("/macros/s/") + GOOGLE_APP_SCRIPT_ID + String("/exec"),
    String("&myFoldername=") + urlencode("AiClassroom/images"),
    String("&myFilename=") + urlencode(dateStr + "," + message), // 在這裡加上 &myFilename=
    String("&myLineType=") + "",
    String("&myToken=") + urlencode(""),
    String("&myUserID=") + urlencode(""),
    "&myFile="
  );
  Serial.println("已上傳Google Drive");
}

String formatDateToYMD() {
  // 設定NTP同步
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  struct tm timeinfo;
  int retryCount = 0;
  const int maxRetries = 10; // 嘗試10次

  // 等待NTP同步完成
  while (!getLocalTime(&timeinfo) && retryCount < maxRetries) {
    Serial.println("取得時間中...");
    delay(2000);
    retryCount++;
  }

  // 若無法取得正確時間，回傳預設值
  if (retryCount >= maxRetries) {
    Serial.println("無法同步時間，返回預設日期");
    return "2024-12-01";
  }

  // 格式化日期字串
  char buffer[11]; // "yyyy-mm-dd" 共10字元 + '\0'
  strftime(buffer, sizeof(buffer), "%Y-%m-%d", &timeinfo);
  return String(buffer);
}

String SendStillToGoogleDrive(String myScript, String myFoldername, String myFilename, String myLineType, String myLineToken, String myLineUserID, String myImage) {
  const char *myDomain = "script.google.com";
  String getAll = "", getBody = "";

  camera_fb_t *fb = NULL;
  fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("Camera capture failed");
    delay(1000);
    ESP.restart();
    return "Camera capture failed";
  }

  Serial.println("Connect to " + String(myDomain));
  clientGoogleDrive.setInsecure();
  if (clientGoogleDrive.connect(myDomain, 443)) {
    Serial.println("Connection successful");

    char *input = (char *)fb->buf;
    char output[base64_enc_len(3)];
    String imageFile = "data:image/jpeg;base64,";
    for (int i = 0; i < fb->len; i++) {
      base64_encode(output, (input++), 3);
      if (i % 3 == 0) imageFile += urlencode(String(output));
    }
    String Data = myFoldername + myFilename + myLineType + myLineToken + myLineUserID + myImage;

    clientGoogleDrive.println("POST " + myScript + " HTTP/1.1");
    clientGoogleDrive.println("Host: " + String(myDomain));
    clientGoogleDrive.println("Content-Length: " + String(Data.length() + imageFile.length()));
    clientGoogleDrive.println("Content-Type: application/x-www-form-urlencoded");
    clientGoogleDrive.println("Connection: close");
    clientGoogleDrive.println();

    clientGoogleDrive.print(Data);
    int Index;
    for (Index = 0; Index < imageFile.length(); Index = Index + 1024) {
      clientGoogleDrive.print(imageFile.substring(Index, Index + 1024));
    }
    esp_camera_fb_return(fb);

    int waitTime = 10000;
    long startTime = millis();
    boolean state = false;

    while ((startTime + waitTime) > millis()) {
      Serial.print(".");
      delay(100);
      while (clientGoogleDrive.available()) {
        char c = clientGoogleDrive.read();
        if (state == true) getBody += String(c);
        if (c == '\n') {
          if (getAll.length() == 0) state = true;
          getAll = "";
        } else if (c != '\r')
          getAll += String(c);
        startTime = millis();
      }
      if (getBody.length() > 0) break;
    }
    clientGoogleDrive.stop();
    Serial.println(getBody);
  } else {
    getBody = "Connected to " + String(myDomain) + " failed.";
    Serial.println("Connected to " + String(myDomain) + " failed.");
  }

  return getBody;
}

String urlencode(String str) {
  const char *msg = str.c_str();
  const char *hex = "0123456789ABCDEF";
  String encodedMsg = "";
  while (*msg != '\0') {
    if (('a' <= *msg && *msg <= 'z') || ('A' <= *msg && *msg <= 'Z') || ('0' <= *msg && *msg <= '9') || *msg == '-' || *msg == '_' || *msg == '.' || *msg == '~') {
      encodedMsg += *msg;
    } else {
      encodedMsg += '%';
      encodedMsg += hex[(unsigned char)*msg >> 4];
      encodedMsg += hex[*msg & 0xf];
    }
    msg++;
  }
  return encodedMsg;
}


// void timerFunc0() {
//   SendStillToGoogleDrive(String("/macros/s/")+ GOOGLE_APP_SCRIPT_ID +String("/exec"), String("&myFoldername=")+urlencode("AiClassroom/images"), String("&myFilename=")+urlencode("plant"), String("&myLineType=")+"", String("&myToken=")+urlencode(""), String("&myUserID=")+urlencode(""), "&myFile=");
//   Serial.println("已上傳Google Drive");
// }

void setup() {
  Serial.begin(115200);

  //設定計時器
  //timer.setInterval(60000, timerFunc0);

  // 關閉 Brown-out 偵測(視需要)
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);

  Serial.println("啟動中...");

  // 先連 WiFi
  connectToWiFi();
  delay(2000);  // 等待系統穩定

  // 初始化 Camera
  initCamera();
  delay(1000);

  // 啟動 Camera Web Server
  startCameraServer();
  Serial.println("CameraWebServer 已啟動，請在瀏覽器中輸入 http://" + WiFi.localIP().toString() + "/");

  // 訂閱 feed
  mqtt.subscribe(&controlCam);

  Serial.println("連接至 Adafruit IO...");
  int8_t ret;
  // 嘗試連接 MQTT (Adafruit IO)
  while ((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("5 秒後重試...");
    delay(5000);
  }
  Serial.println("Adafruit IO 連線成功！");
}

void loop() {
  //計時器啟動
  //timer.run();

  // 維持 MQTT 連線
  if (!mqtt.connected()) {
    int8_t ret;
    while ((ret = mqtt.connect()) != 0) {
      Serial.println(mqtt.connectErrorString(ret));
      Serial.println("5 秒後重試...");
      delay(5000);
    }
    Serial.println("重新連線 Adafruit IO 成功！");
  }

  // 處理訂閱的訊息
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    if (subscription == &controlCam) {
      handleControlCamMessage((char *)controlCam.lastread, controlCam.datalen);
    }
  }

  mqtt.ping();
}
