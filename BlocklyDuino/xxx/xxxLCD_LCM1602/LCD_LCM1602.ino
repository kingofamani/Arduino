/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Wed, 18 Nov 2020 01:37:51 GMT
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
void LCM1602_0() {
}

void LCM1602_1() {
  //螢幕不能顯示中文
  lcd.init();
  lcd.backlight();
}

void setup()
{
  LCM1602_1();
  //(往右,往下)16格*2行，從編號0開始算
  lcd.setCursor(2,0);
  lcd.print("Hello, world!");
  lcd.setCursor(0,1);
  lcd.print("Ywrobot Arduino!");
  delay(5000);
  lcd.clear();
  lcd.print("DEIN School");
}


void loop()
{

}
