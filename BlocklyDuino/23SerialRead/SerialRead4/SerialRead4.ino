/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 21 Mar 2022 02:11:27 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


int B = 0;

void setup()
{
  Serial.begin(9600);


}


void loop()
{
  if (Serial.available() == 1) {
    B = Serial.parseInt();
    Serial.println(B);
  }
}