//Generated Date: Mon, 16 Dec 2024 06:54:56 GMT

#include <WiFi.h>
#include <WiFiClientSecure.h>
WiFiClientSecure client;
#include "esp_camera.h"
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
char _lwifi_ssid[] = "tyes-itc2";
char _lwifi_pass[] = "xxxxxxxxxxxxxx";
const char* apssid = "esp32-cam";
const char* appassword = "12345678";

#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

#include "Base64.h"

//Flash mode
boolean cameraState = false;
WiFiServer server81(81);

  void initWiFi() {
    WiFi.mode(WIFI_AP_STA);

    for (int i=0;i<2;i++) {
      if (String(_lwifi_ssid)=="") break;
      WiFi.begin(_lwifi_ssid, _lwifi_pass);

      delay(1000);
      Serial.println("");
      Serial.print("Connecting to ");
      Serial.println(_lwifi_ssid);

      long int StartTime=millis();
      while (WiFi.status() != WL_CONNECTED) {
          delay(500);
          if ((StartTime+5000) < millis()) break;
      }

      if (WiFi.status() == WL_CONNECTED) {
        WiFi.softAP((WiFi.localIP().toString()+"_"+(String)apssid).c_str(), appassword);
        Serial.println("");
        Serial.println("STAIP address: ");
        Serial.println(WiFi.localIP());
        Serial.println("");

  		 ledcAttachPin(4, 4);
  		 ledcSetup(4, 5000, 8);
        for (int i=0;i<5;i++) {
          ledcWrite(4,10);
          delay(200);
          ledcWrite(4,0);
          delay(200);
        }
        break;
      }
    }

    if (WiFi.status() != WL_CONNECTED) {
      WiFi.softAP((WiFi.softAPIP().toString()+"_"+(String)apssid).c_str(), appassword);

    }

    Serial.println("");
    Serial.println("APIP address: ");
    Serial.println(WiFi.softAPIP());

    server81.begin();
  }

		void getRequest81() {
		  WiFiClient client = server81.available();
		  if (client) {
		    String currentLine = "";
		    while (client.connected()) {
		      if (client.available()) {
		        char c = client.read();
		        if (c == '\n') {
		          if (currentLine.length() == 0) {
		            String head = "--Taiwan\r\nContent-Type: image/jpeg\r\n\r\n";
		            client.println("HTTP/1.1 200 OK");
		            client.println("Access-Control-Allow-Origin: *");
		            client.println("Content-Type: multipart/x-mixed-replace; boundary=Taiwan");
		            client.println();
		            while(client.connected()) {
		              while (cameraState) {vTaskDelay(10);}
		              cameraState=true;
		              camera_fb_t * fb = NULL;
		              fb = esp_camera_fb_get();
		              if(!fb) {
		                Serial.println("Camera capture failed");
		                delay(1000);
		                ESP.restart();
		              }
		              client.print(head);
		              uint8_t *fbBuf = fb->buf;
		              size_t fbLen = fb->len;
		              for (size_t n=0;n<fbLen;n=n+1024) {
		                if (n+1024<fbLen) {
		                  client.write(fbBuf, 1024);
		                  fbBuf += 1024;
		                }
		                else if (fbLen%1024>0) {
		                  size_t remainder = fbLen%1024;
		                  client.write(fbBuf, remainder);
		                }
		              }
		              esp_camera_fb_return(fb);
		              client.print("\r\n");
		              cameraState=false;
		              vTaskDelay(10);
		            }
		            cameraState=0;
		            break;
		          } else {
		            currentLine = "";
		          }
		        }
		        else if (c != '\r') {
		          currentLine += c;
		        }
		      }
		    }
		    client.stop();
		  }
		}

		TaskHandle_t Task0;
		void codeForTask0( void * parameter ) {
		  while (true) {
		    getRequest81();
		    vTaskDelay(10);
		  }
		}

String SendStillToGoogleDrive(String myScript, String myFoldername, String myFilename, String myLineType, String myLineToken, String myLineUserID, String myImage) {
  const char* myDomain = "script.google.com";
  String getAll="", getBody = "";

  camera_fb_t * fb = NULL;
  fb = esp_camera_fb_get();
  if(!fb) {
    Serial.println("Camera capture failed");
    delay(1000);
    ESP.restart();
    return "Camera capture failed";
  }

  Serial.println("Connect to " + String(myDomain));
  client.setInsecure();
  if (client.connect(myDomain, 443)) {
    Serial.println("Connection successful");

    char *input = (char *)fb->buf;
    char output[base64_enc_len(3)];
    String imageFile = "data:image/jpeg;base64,";
    for (int i=0;i<fb->len;i++) {
      base64_encode(output, (input++), 3);
      if (i%3==0) imageFile += urlencode(String(output));
    }
    String Data = myFoldername+myFilename+myLineType+myLineToken+myLineUserID+myImage;

    client.println("POST " + myScript + " HTTP/1.1");
    client.println("Host: " + String(myDomain));
    client.println("Content-Length: " + String(Data.length()+imageFile.length()));
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Connection: close");
    client.println();

    client.print(Data);
    int Index;
    for (Index = 0; Index < imageFile.length(); Index = Index+1024) {
      client.print(imageFile.substring(Index, Index+1024));
    }
    esp_camera_fb_return(fb);

    int waitTime = 10000;
    long startTime = millis();
    boolean state = false;

    while ((startTime + waitTime) > millis())
    {
      Serial.print(".");
      delay(100);
      while (client.available())
      {
          char c = client.read();
          if (state==true) getBody += String(c);
          if (c == '\n')
          {
            if (getAll.length()==0) state=true;
            getAll = "";
          }
          else if (c != '\r')
            getAll += String(c);
          startTime = millis();
       }
       if (getBody.length()>0) break;
    }
    client.stop();
    Serial.println(getBody);
  }
  else {
    getBody="Connected to " + String(myDomain) + " failed.";
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

void setup()
{
  Serial.begin(115200);
  delay(10);WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
    Serial.setDebugOutput(true);
  Serial.println();
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
  if(psramFound()){
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    delay(1000);
    ESP.restart();
  }
  sensor_t * s = esp_camera_sensor_get();
  if (s->id.PID == OV3660_PID) {
    s->set_vflip(s, 1);
    s->set_brightness(s, 1);
    s->set_saturation(s, -2);
  }
  s->set_framesize(s, FRAMESIZE_VGA);
  Serial.println();
  initWiFi();

  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
    xTaskCreatePinnedToCore(
      codeForTask0,
      "Task 0",
      8192,
      NULL,
      1,
      &Task0,
      0
    );
    vTaskDelay(100);

  s->set_vflip(s, 1);//鏡頭垂直翻轉
  s->set_hmirror(s, 1);//鏡頭水平翻轉
  s->set_framesize(s, FRAMESIZE_SVGA);
}

void loop()
{
  SendStillToGoogleDrive(String("/macros/s/")+"xxxxxxxxxxxxxxx"+String("/exec"), String("&myFoldername=")+urlencode("AiClassroom/images"), String("&myFilename=")+urlencode("plant"), String("&myLineType=")+"", String("&myToken=")+urlencode(""), String("&myUserID=")+urlencode(""), "&myFile=");
  delay(60000);
}
