/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 11 Oct 2021 01:17:15 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


void setup()
{
  Serial.begin(9600);


}


void loop()
{
  Serial.println(analogRead(A0));
  delay(100);
}