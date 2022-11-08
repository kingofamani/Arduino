/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Tue, 08 Nov 2022 00:32:46 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


int secs = 0;

void setup()
{
  Serial.begin(9600);


}


void loop()
{
  Serial.println(millis());
  secs = round(millis() / 1000);
  Serial.print("目前時間：");
  Serial.println(secs);
  delay(1000);
}