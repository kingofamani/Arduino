/*
 * =================================================================
 *   ESP32 MQTT to LINE Message Gateway - 完整版
 * =================================================================
 * 
 * 功能:
 * 1. 連接到指定的 WiFi 網路。
 * 2. 連接到公共 MQTT Broker (broker.emqx.io)。
 * 3. 訂閱 'amani_line_msg' 主題以接收訊息。
 * 4. 當收到訊息時，解析其 JSON 內容 (email, userId, token, message)。
 * 5. 執行業務邏輯：
 *    - 驗證發送者 email 的網域必須是 '@apps.ntpc.edu.tw'。
 *    - 如果 email 是 ADMIN_EMAIL，則強制使用預設的 ADMIN_LINE_USERID 和 ADMIN_LINE_TOKEN 
 *      來發送訊息，忽略 payload 中的 userId 和 token。
 *    - 如果是其他合法 email，則使用 payload 中提供的 userId 和 token。
 * 6. 透過 HTTPS POST 請求呼叫 LINE Messaging API，將訊息推播出去。
 * 
 * ---
 * 
 * 準備工作:
 * 1. 在 Arduino IDE 中安裝函式庫:
 *    - PubSubClient
 *    - ArduinoJson (v6 或更高)
 * 2. 在專案中建立一個 `secrets.h` 檔案，並填入以下內容:
 *    #define WIFI_SSID "your-wifi-ssid"
 *    #define WIFI_PWD "your-wifi-pwd"
 *    #define ADMIN_EMAIL "your-admin-email@apps.ntpc.edu.tw"
 *    #define ADMIN_LINE_USERID "YOUR_ADMIN_LINE_USER_ID"
 *    #define ADMIN_LINE_TOKEN "YOUR_ADMIN_LINE_ACCESS_TOKEN"
 */

// 引入必要的函式庫
#include <WiFi.h>
#include <WiFiClientSecure.h> // 用於 HTTPS 連線
#include <PubSubClient.h>      // 用於 MQTT
#include <ArduinoJson.h>       // 用於處理 JSON
#include <HTTPClient.h>        // 用於發送 HTTP 請求
#include "secrets.h"           // 引入您的私密資訊檔案

// --- MQTT 設定 ---
const char* mqtt_server = "broker.emqx.io";
const int   mqtt_port = 1883;
const char* mqtt_topic_sub = "amani_line_msg";

// --- LINE API 設定 ---
const char* line_host = "api.line.me";
const int   line_https_port = 443;
const char* line_push_url = "/v2/bot/message/push";

// --- 全域物件 ---
WiFiClient espClient;
PubSubClient client(espClient);

// --- 函式原型宣告 ---
void callback(char* topic, byte* payload, unsigned int length);
void sendLineMessage(const char* userId, const char* accessToken, const char* message);
void reconnect();

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; // 等待 Serial 連線建立
  }
  delay(1000);

  // --- 連接 WiFi ---
  Serial.println();
  Serial.print("Connecting to WiFi: ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PWD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // --- 設定 MQTT 客戶端 ---
  client.setServer(mqtt_server, mqtt_port);
  client.setBufferSize(1024);
  client.setCallback(callback);
}

void loop() {
  // 如果 MQTT 未連線，則嘗試重新連線
  if (!client.connected()) {
    reconnect();
  }
  // 維持 MQTT 連線並處理傳入的訊息
  client.loop(); 
}

// MQTT 重新連線函式
void reconnect() {
  // 循環直到重新連線成功
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // 建立一個隨機的客戶端 ID
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // 重新連線後，立即訂閱主題
      client.subscribe(mqtt_topic_sub);
      Serial.print("Subscribed to topic: ");
      Serial.println(mqtt_topic_sub);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // 等待 5 秒後重試
      delay(5000);
    }
  }
}

// MQTT 訊息回呼函式 (當收到訂閱主題的訊息時觸發)
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println("-------");
  Serial.print("Message arrived on topic: ");
  Serial.println(topic);

  // 將 payload 複製到一個有結尾符的緩衝區
  char message_buff[length + 1];
  memcpy(message_buff, payload, length);
  message_buff[length] = '\0';
  Serial.print("Payload: ");
  Serial.println(message_buff);

  // 使用 ArduinoJson 解析 JSON
  StaticJsonDocument<1024> doc; // 確保容量足夠
  DeserializationError error = deserializeJson(doc, message_buff);

  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }

  // 從 JSON 中提取資料
  const char* email = doc["email"];
  const char* userId_from_payload = doc["userId"];
  const char* token_from_payload = doc["token"];
  const char* message = doc["message"];

  // --- 開始執行業務邏輯 ---
  
  // 1. 驗證基礎欄位是否存在
  if (!email || !message) {
      Serial.println("Error: JSON is missing required 'email' or 'message' field.");
      return;
  }
  
  // 2. 驗證 email 網域
  String emailStr = String(email);
  if (!emailStr.endsWith("@apps.ntpc.edu.tw")) {
    Serial.println("Error: Email domain is not allowed.");
    return;
  }

  // 3. 根據 email 決定要使用的 userId 和 token
  const char* lineUserIdToSend;
  const char* lineTokenToSend;

  if (emailStr.equalsIgnoreCase(ADMIN_EMAIL)) {
    Serial.println("Admin detected. Using predefined ADMIN_LINE_USERID and ADMIN_LINE_TOKEN.");
    Serial.println("Note: 'userId' and 'token' from payload will be ignored.");
    
    lineUserIdToSend = ADMIN_LINE_USERID; // 強制使用預設的管理員 User ID
    lineTokenToSend = ADMIN_LINE_TOKEN;    // 強制使用預設的管理員 Token
    
  } else {
    Serial.println("Normal user detected. Using userId and token from payload.");
    
    // 對於普通用戶，userId 和 token 是必要欄位
    if (!userId_from_payload || !token_from_payload) {
        Serial.println("Error: 'userId' or 'token' is missing for non-admin user.");
        return;
    }
    lineUserIdToSend = userId_from_payload; // 使用 payload 傳來的 User ID
    lineTokenToSend = token_from_payload;   // 使用 payload 傳來的 Token
  }

  // 呼叫 LINE API 發送訊息
  Serial.println("Preparing to send LINE message...");
  Serial.printf("Target UserID: %s\n", lineUserIdToSend);
  sendLineMessage(lineUserIdToSend, lineTokenToSend, message);
}


// 發送 LINE 推播訊息的函式
void sendLineMessage(const char* userId, const char* accessToken, const char* message) {
  WiFiClientSecure clientSecure;
  HTTPClient http;

  // 在生產環境中，建議加載 LINE 的根證書以策安全
  // 為了方便測試，這裡暫時不驗證伺服器證書
  clientSecure.setInsecure(); 

  Serial.println("[HTTP] begin...");
  if (http.begin(clientSecure, line_host, line_https_port, line_push_url)) {
    
    // 設定 HTTP 標頭
    String authHeader = "Bearer " + String(accessToken);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Authorization", authHeader);

    // 建立要發送的 LINE API JSON 主體
    StaticJsonDocument<1024> bodyDoc;
    bodyDoc["to"] = userId;
    JsonArray messages = bodyDoc.createNestedArray("messages");
    JsonObject msgObj = messages.createNestedObject();
    msgObj["type"] = "text";
    msgObj["text"] = message;

    String requestBody;
    serializeJson(bodyDoc, requestBody);

    Serial.print("[HTTP] POST... Body: ");
    Serial.println(requestBody);

    // 發送 POST 請求
    int httpCode = http.POST(requestBody);

    // 檢查回應碼
    if (httpCode > 0) {
      Serial.printf("[HTTP] POST... code: %d\n", httpCode);
      String response = http.getString();
      if (httpCode == HTTP_CODE_OK) {
        Serial.println("[HTTP] Response: " + response); // LINE API 成功時會回傳 {}
      } else {
        Serial.println("[HTTP] Error Response: " + response);
      }
    } else {
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    // 釋放資源
    http.end();
  } else {
    Serial.println("[HTTP] Unable to connect to LINE API host.");
  }
}