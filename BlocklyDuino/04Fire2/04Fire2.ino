/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 11 Oct 2021 02:31:12 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


void setup()
{
  Serial.begin(9600);


  pinMode(7, INPUT);
  pinMode(4, OUTPUT);
}


void loop()
{
  Serial.println(digitalRead(7));
  // 此火焰感測器模組為低電平(有火為0)
  if (digitalRead(7) == false) {
    digitalWrite(4, HIGH);
    delay(2000);
  } else {
    digitalWrite(4, LOW);
  }
  delay(100);
}