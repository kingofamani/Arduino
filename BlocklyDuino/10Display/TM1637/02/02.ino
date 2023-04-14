#include <TM1637Display.h>

// 設定連接到TM1637的CLK和DIO腳
#define CLK 2
#define DIO 3

// 初始化TM1637顯示器
TM1637Display display(CLK, DIO);

// 設定顯示亮度，範圍為0到7
const uint8_t brightness = 4;

void setup() {
  // 初始化顯示器並設定亮度
  display.setBrightness(brightness);
  display.clear();
}

void loop() {
  // 獲取當前時間
  unsigned long currentTime = millis();

  // 計算小時和分鐘
  int hours = (currentTime / 3600000) % 24;
  int minutes = (currentTime / 60000) % 60;

  // 顯示時間
  display.showNumberDecEx(hours * 100 + minutes, 0b11100000, true);

  // 每秒更新一次
  delay(1000);
}
