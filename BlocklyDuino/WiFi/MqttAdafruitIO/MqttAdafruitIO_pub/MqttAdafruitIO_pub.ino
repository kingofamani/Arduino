#include <AdafruitIO_WiFi.h> 
#include <WiFi.h>

// Adafruit IO 帳號資訊
#define IO_USERNAME "kingofamani"
#define IO_KEY "xxxxxxxxxx"

// WiFi 設定
#define WIFI_SSID "AMANI-4G-Home"
#define WIFI_PASS "xxxxxxxxxx"

// 建立 Adafruit IO 物件
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// Feed 定義
AdafruitIO_Feed *temperature = io.feed("temperature");

void setup() {
  Serial.begin(115200);

  // 啟動 Adafruit IO
  Serial.print("連接至 Adafruit IO...");
  io.connect();

  // 等待連接成功
  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("連接成功！");
}

void loop() {
  io.run(); // 維持連接

  // 發佈溫度數據
  float tempValue = 25.0 + random(0, 100) / 10.0; // 模擬數據
  temperature->save(tempValue);

  Serial.print("發佈溫度: ");
  Serial.println(tempValue);

  delay(5000); // 每 5 秒發佈一次
}

