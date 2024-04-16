/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Thu, 07 Oct 2021 05:22:53 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


int P = 80;

int Q = 100;

void setup()
{
  Serial.begin(9600);


}


void loop()
{
  //設定P=Q和Q=P的差異
  P = Q;
  Serial.println(P);
  Serial.println(Q);
  delay(1000);
}