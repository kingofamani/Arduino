/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 14 Mar 2022 04:00:36 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


String B = "";

void setup()
{
  Serial.begin(9600);


}


void loop()
{
  if (Serial.available() == 1) {
    B = Serial.readString();
    Serial.println(B);
  }
}