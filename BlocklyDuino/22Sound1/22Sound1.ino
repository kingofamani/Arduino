/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Wed, 13 Oct 2021 00:17:35 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


void setup()
{
  Serial.begin(9600);


  pinMode(5, OUTPUT);
}


void loop()
{
  Serial.println(analogRead(A0));
  if (analogRead(A0) >= 800) {
    digitalWrite(5, HIGH);
    delay(2000);
  } else {
    digitalWrite(5, LOW);
  }
  delay(100);
}