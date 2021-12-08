/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Wed, 08 Dec 2021 23:21:35 GMT
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
  Serial.println(ultrasonic_.convert(ultrasonic_.timing(), Ultrasonic::CM));
  delay(200);
}