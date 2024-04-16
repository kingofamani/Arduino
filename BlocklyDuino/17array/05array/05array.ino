/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 07 Mar 2022 03:28:25 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


int scores[] = {11, 22, 33, 44, 55};

void setup()
{
  Serial.begin(9600);

  for (int i = 0; i <= (sizeof(scores)/sizeof(scores[0])) - 1; i++) {
    Serial.println((scores[i]));
  }
}


void loop()
{

}