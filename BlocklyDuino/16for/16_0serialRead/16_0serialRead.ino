/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Thu, 10 Mar 2022 00:26:09 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


void setup()
{
  Serial.begin(9600);


}


void loop()
{
  if (Serial.available() == 1) {
    Serial.println((Serial.readString()));
  }
}