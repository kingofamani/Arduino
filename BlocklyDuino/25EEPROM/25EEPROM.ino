/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 07 Nov 2022 03:44:51 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include <EEPROM.h>

int addr = 0;

void ifMemoryFull() {
  if (addr == EEPROM.length()) {
  addr = 0;
  }
}

void setup()
{
  Serial.begin(9600);


}


void loop()
{
  addr = 0;
  //寫入記憶體
  Serial.println("寫入中…");
  for (int i = 5; i <= 15; i++) {
    ifMemoryFull();
    EEPROM.write(addr, i);
    addr = addr + 1;
    delay(100);
  }
  Serial.println("寫入完成。");
  delay(2000);
  //讀取記憶體
  Serial.println("讀取中…");
  addr = 0;
  for (int i = 0; i <= 10; i++) {
    int val = (EEPROM.read(addr));
    Serial.println(val);
    addr = addr + 1;
    ifMemoryFull();
    delay(100);
  }
  Serial.println("讀取完成");
  delay(2000);
  //清除記憶體
  Serial.println("清除中…");
  for (int i = 0; i <= (EEPROM.length()); i++) {
    EEPROM.write(i, 0);
  }
  Serial.println("清除完成。");
  //讀取看是否已清除
  addr = 0;
  for (int i = 0; i <= 10; i++) {
    int val = (EEPROM.read(addr));
    Serial.println(val);
    addr = addr + 1;
    ifMemoryFull();
    delay(100);
  }
  Serial.println("=========================");
}