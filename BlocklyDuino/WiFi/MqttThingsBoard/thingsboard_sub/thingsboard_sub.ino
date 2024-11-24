#include <WiFi.h>
#include <PubSubClient.h>

// WiFi 設定
const char* ssid = "AMANI-4G-Home";
const char* password = "xxxxxxx";

// ThingsBoard.Cloud MQTT 設定
const char* mqtt_server = "mqtt.thingsboard.cloud";  // ThingsBoard.Cloud 的 MQTT Broker 地址
const int mqtt_port = 1883;                       // MQTT 通訊埠
const char* access_token = "xxxxxxxxxxxx";        // 從 ThingsBoard 獲取的設備 Token

WiFiClient espClient;
PubSubClient client(espClient);

// MQTT 回調函數，用於處理訂閱的消息
void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived on topic: ");
    Serial.println(topic);

    Serial.print("Message payload: ");
    for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}

void setup() {
    Serial.begin(115200);

    // 連接 WiFi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("WiFi connected");

    // 設置 MQTT 伺服器
    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);

    // 連接到 ThingsBoard
    while (!client.connected()) {
        Serial.println("Connecting to ThingsBoard.Cloud...");
        if (client.connect("ESP32_Device", access_token, NULL)) {
            Serial.println("Connected to ThingsBoard.Cloud!");
        } else {
            Serial.print("Failed, rc=");
            Serial.print(client.state());
            delay(2000);
        }
    }

    // 訂閱 RPC 主題
    client.subscribe("v1/devices/me/rpc/request/+");
    Serial.println("Subscribed to RPC topic");

    // 訂閱屬性更新主題
    client.subscribe("v1/devices/me/attributes");
    Serial.println("Subscribed to attributes topic");
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();
}

void reconnect() {
    while (!client.connected()) {
        Serial.println("Reconnecting to ThingsBoard.Cloud...");
        if (client.connect("ESP32_Device", access_token, NULL)) {
            Serial.println("Reconnected to ThingsBoard.Cloud!");
            // 重新訂閱主題
            client.subscribe("v1/devices/me/rpc/request/+");
            client.subscribe("v1/devices/me/attributes");
        } else {
            Serial.print("Failed, rc=");
            Serial.print(client.state());
            delay(2000);
        }
    }
}
