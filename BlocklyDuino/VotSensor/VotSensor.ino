/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Thu, 14 Oct 2021 00:05:00 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


float V = 0;

void setup()
{
  Serial.begin(9600);


}


void loop()
{
  V = analogRead(A0) * 0.025039;
  Serial.println(V);
  delay(100);
}