/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Wed, 09 Mar 2022 23:55:58 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


void setup()
{
  Serial.begin(9600);

  for (int i = 1; i <= 9; i++) {
    for (int j = 1; j <= 9; j++) {
      if (i == j) {
        Serial.print("★");
      } else {
        Serial.print("○");
      }
    }
    Serial.println("");
  }
}


void loop()
{

}