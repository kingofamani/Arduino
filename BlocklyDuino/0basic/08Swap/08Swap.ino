/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Thu, 07 Oct 2021 05:24:09 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


int P = 80;

int Q = 100;

int R = 0;

void setup()
{
  Serial.begin(9600);

  //將P和Q的值互換
  R = P;
  P = Q;
  Q = R;
  Serial.println(P);
  Serial.println(Q);
  delay(1000);
}


void loop()
{

}