/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 11 Oct 2021 02:18:55 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


void setup()
{
  Serial.begin(9600);


  pinMode(4, OUTPUT);
}


void loop()
{
  Serial.println(analogRead(A0));
  if (analogRead(A0) > 10) {
    digitalWrite(4, HIGH);
    delay(2000);
  } else {
    digitalWrite(4, LOW);
  }
  delay(100);
}