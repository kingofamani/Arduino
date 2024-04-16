/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 14 Mar 2022 23:21:34 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


char key = ' ';

String num = "";

void setup()
{
  Serial.begin(9600);


}


void loop()
{
  if (Serial.available() == 1) {
    key = Serial.read();
    num += key;
    Serial.println(num);
  }
}