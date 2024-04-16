/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 14 Mar 2022 03:54:58 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


char A = ' ';

void setup()
{
  Serial.begin(9600);

  //★單引號裡一定要有空格or其他字
}


void loop()
{
  if (Serial.available() == 1) {
    A = Serial.read();
    Serial.println(A);
  }
}