/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 07 Nov 2022 07:39:26 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include <EEPROM.h>

void writeToMemory(int addr, int val) {
  EEPROM.write(addr, val);
}

int ReadFromMemory(int addr) {
  return (EEPROM.read(addr));
}

void clearOneMemory(int addr) {
  EEPROM.write(addr, 0);
}

void clearAllMemory() {
  for (int i = 0; i <= (EEPROM.length()); i++) {
    EEPROM.write(i, 0);
  }
}

void setup()
{
  Serial.begin(9600);


}


void loop()
{
  //寫入記憶體
  writeToMemory(1, 255);
  delay(2000);
  //讀取記憶體
  int val = (ReadFromMemory(1));
  Serial.println(val);
  delay(2000);
  //清除記憶體
  clearOneMemory(1);
  //讀取看是否已清除
  Serial.println((ReadFromMemory(1)));
  delay(2000);
  Serial.println("=========================");
}