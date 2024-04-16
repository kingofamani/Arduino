/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 11 Oct 2021 07:25:44 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


String names[] = {"加菲貓", "蝙蝠俠", "米奇老鼠", "史努比", "忍者龜"};

void setup()
{
  Serial.begin(9600);

  for (int i = 0; i <= 4; i++) {
    Serial.println((names[i]));
  }
}


void loop()
{

}