/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Thu, 29 Sep 2022 02:50:53 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


int pot = 0;

void setup()
{

  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}


void loop()
{
  pot = analogRead(A0) / 4;
  analogWrite(3, (255 - (abs((0 - pot)))));
  analogWrite(5, (255 - (abs((51 - pot)))));
  analogWrite(6, (255 - (abs((102 - pot)))));
  analogWrite(9, (255 - (abs((153 - pot)))));
  analogWrite(10, (255 - (abs((204 - pot)))));
  analogWrite(11, (255 - (abs((255 - pot)))));
}