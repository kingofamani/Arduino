/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 11 Oct 2021 07:24:37 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


int score[] = {80, 95, 100, 99, 50};

void setup()
{
  Serial.begin(9600);

  for (int i = 0; i <= 4; i++) {
    Serial.println((score[i]));
  }
}


void loop()
{

}