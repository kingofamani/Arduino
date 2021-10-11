/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Sat, 31 Oct 2020 07:25:57 GMT
 */

#include <Servo.h>

Servo myServo;

void setup()
{
  //避免抖動
  myServo.attach(3);//接在D3
  myServo.write(45);
  delay(2000);
  myServo.detach();//停止
}


void loop()
{
  myServo.attach(3);
  myServo.write(170);
  // 轉動需要時間
  delay(1000);
  myServo.detach();
  delay(2000);
  myServo.attach(3);
  myServo.write(45);
  delay(1000);
  myServo.detach();
  delay(2000);
}