/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 11 Oct 2021 03:47:41 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include <Ultrasonic.h>

Ultrasonic ultrasonic_(5, 6);

void setup()
{
  Serial.begin(9600);


}


void loop()
{
  // 公分
  Serial.println(ultrasonic_.convert(ultrasonic_.timing(), Ultrasonic::CM));
  delay(200);
}