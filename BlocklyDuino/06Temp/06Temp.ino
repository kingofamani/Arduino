/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 11 Oct 2021 02:52:13 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


float Temp = 0;

void setup()
{
  Serial.begin(9600);


}


void loop()
{
  Temp = analogRead(A0) * 0.4882812;
  Serial.println(Temp);
  delay(100);
}