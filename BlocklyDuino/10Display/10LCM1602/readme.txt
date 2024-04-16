BlocklyDuino/arduino IDE 1.8.13
	要安裝LiquidCrystal_I2C (by Frank de Brabander)程式庫
	積木：顯示模組/液晶顯示
	
arduino 1.8.19
	要安裝LiquidCrystal_I2C (by Marco Schwartz)程式庫
	寫法不同：
	#include <Wire.h> 
	LiquidCrystal_I2C lcd(0x27,16,2);
	lcd.init();

GND	GND
VCC	5V
SDA	A4
SCL	A5

0行就是第1行；0列就是第1列。
直行橫列。

★接太多感測器，電壓會不夠。

★若是1602黑色版模組，請於上傳程式後，
　要調整藍色對比旋鈕，才會顯示文字。

工作電流：2.0mA（5.0V）
所以如果不接電腦，UNO改接外部電源時，
USB插頭5V/0.5A可以讓LCM1602工作
但5V/2A、9V都無法工作