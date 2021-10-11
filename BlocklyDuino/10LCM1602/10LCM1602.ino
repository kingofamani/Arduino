/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 11 Oct 2021 05:06:01 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd_i2c(0x27);

void setup()
{
  lcd_i2c.begin(16, 2);
  lcd_i2c.backlight();
}


void loop()
{
  lcd_i2c.setCursor(0,0);
  lcd_i2c.print("HELLO");
}