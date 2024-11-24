#include <AdafruitIO_WiFi.h>
#include <WiFi.h>

// Adafruit IO 帳號資訊
#define IO_USERNAME "kingofamani"
#define IO_KEY "xxxxxxxxx"

// WiFi 設定
#define WIFI_SSID "AMANI-4G-Home"
#define WIFI_PASS "xxxxxxxxxxxx"

// 建立 Adafruit IO 物件
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// 定義訂閱的 Feed
AdafruitIO_Feed *ledControl = io.feed("led-status");

// LED GPIO
#define LED_PIN 2

void setup() {
  // 初始化序列埠
  Serial.begin(115200);

  // 初始化 LED
  pinMode(LED_PIN, OUTPUT);

  // 連接至 Adafruit IO
  Serial.print("連接至 Adafruit IO...");
  io.connect();

  // 設定訂閱回調函式
  ledControl->onMessage(handleMessage);

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
}

// 處理訂閱訊息的回調函式
void handleMessage(AdafruitIO_Data *data) {
  Serial.print("接收到的 LED 狀態: ");
  Serial.println(data->value());

  // 控制 LED
  if (data->value() == "1") {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("LED 已開啟");
  } else if (data->value() == "0") {
    digitalWrite(LED_PIN, LOW);
    Serial.println("LED 已關閉");
  }
}
