#include <WiFi.h>
#include <PubSubClient.h>

// WiFi 設定
const char* ssid = "AMANI-4G-Home";
const char* password = "xxxxxxxx";

// ThingsBoard.Cloud MQTT 設定
const char* mqtt_server = "mqtt.thingsboard.cloud";  // ThingsBoard.Cloud 的 MQTT Broker 地址
const int mqtt_port = 1883;                       // MQTT 通訊埠
const char* access_token = "xxxxxxxx";        // 從 ThingsBoard 獲取的設備 Token

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
    Serial.begin(115200);

    // 連接 Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("WiFi connected");

    // 設置 MQTT 伺服器
    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);

    // 連接到 ThingsBoard.Cloud
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
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();

    // 發送數據到 ThingsBoard.Cloud
    String payload = "{\"temperature\": 25.6, \"humidity\": 60}";
    client.publish("v1/devices/me/telemetry", payload.c_str());

    Serial.println("Data sent: " + payload);
    delay(10000);  // 每 5 秒發送一次數據
}

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived on topic: ");
    Serial.println(topic);

    for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}

void reconnect() {
    while (!client.connected()) {
        Serial.println("Reconnecting to ThingsBoard.Cloud...");
        if (client.connect("ESP32_Device", access_token, NULL)) {
            Serial.println("Reconnected to ThingsBoard.Cloud!");
        } else {
            Serial.print("Failed, rc=");
            Serial.print(client.state());
            delay(2000);
        }
    }
}
