練習：
第1列顯示HELLO、第2列顯示DEIN，每隔1秒互換顯示。

LiquidCrystal_I2C (by Frank de Brabander)程式庫
積木：顯示模組/液晶顯示

GND	GND
VCC	5V
SDA	A4
SCL	A5

0行就是第1行；0列就是第1列。
直行橫列。

工作電流：2.0mA（5.0V）
所以如果不接電腦，UNO改接外部電源時，
USB插頭5V/0.5A可以讓LCM1602工作
但5V/2A、9V都無法工作