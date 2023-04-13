#include <TM1637Display.h>

// 定義TM1637顯示器連接的引腳
#define CLK 2
#define DIO 3

// 初始化TM1637顯示器對象
TM1637Display display(CLK, DIO);

void setup() {
  // 設置亮度，範圍為0（最暗）到7（最亮）
  display.setBrightness(7);
}

void loop() {
  for (int minutes = 0; minutes < 60; minutes++) {
    for (int seconds = 0; seconds < 60; seconds++) {
      // 計算要顯示的數字
      int displayTime = minutes * 100 + seconds;
      
      // 顯示時間
      display.showNumberDec(displayTime, false);

      // 等待1秒
      delay(1000);
    }
  }
}
