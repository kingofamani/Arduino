#include <LedControl.h>

// 引脚配置: DIN, CLK, CS, 1
LedControl lc = LedControl(13, 14, 27, 1);

void setup() {
  lc.shutdown(0, false);       // 醒來
  lc.setIntensity(0, 8);       // 設置亮度 (0 是最低亮度, 15 是最高亮度)
  lc.clearDisplay(0);          // 清除顯示
}

void loop() { 
  lightUp(2, 3);              // 點亮第2行，第3列的LED
  delay(1000);                // 等待1秒
  lc.clearDisplay(0);         // 清除顯示
  delay(1000);                // 等待1秒
}

void lightUp(int row, int col) {
  lc.setLed(0, row, col, true); // 點亮特定LED
}
