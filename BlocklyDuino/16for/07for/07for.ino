/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 11 Oct 2021 06:41:18 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


void setup()
{
  Serial.begin(9600);

  for (int i = 2; i <= 9; i++) {
    for (int j = 1; j <= 9; j++) {
      Serial.print((i * j));
      Serial.print("\\t");
    }
  }
}


void loop()
{
  // 印出九九乘法，所有的答案

}