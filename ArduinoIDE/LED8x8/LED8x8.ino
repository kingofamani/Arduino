#include <LedControl.h>
// Pin 12:Data in, Pin 11: Clock,  Pin 10: CS(Load)
LedControl display = LedControl(12,11,10,1);
 
const uint64_t IMAGES[] = { 
  0x0000000100000000,
  0x0000010301000000,
  0x0001030703010000,
  0x0103070f07030100,
  0x02060f1f0f060200,
  0x040c1f3f1f0c0400,
  0x08183f7f3f180800,
  0x08183f7f3f180800,
  0x10307fff7f301000,
  0x2060fefefe602000,
  0x40c0fcfcfcc04000,
  0x8080f8f8f8808000,
  0x0000f0f0f0000000,
  0x0000e0e0e0000000,
  0x0000c0c0c0000000,
  0x0000808080000000,
  0x0000000000000000
};
const int IMAGES_LEN = sizeof(IMAGES)/8;

void setup()
{
  display.clearDisplay(0);    // 清除螢幕
  display.shutdown(0, false);  // 關閉省電模式
  display.setIntensity(0, 10); // 設定亮度為 8 (介於0~15之間)

}
void displayImage(uint64_t image) {
  for (int i = 0; i < 8; i++) {
    byte row = (image >> i * 8) & 0xFF;
    for (int j = 0; j < 8; j++) {
      display.setLed(0, i, j, bitRead(row, j));
    }
  }
}

int i = 0;

void loop() {
   displayImage(IMAGES[i]);
  if (++i >= IMAGES_LEN ) {
    i = 0;
  }
  delay(100); 
}
