/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Thu, 24 Sep 2020 01:44:55 GMT
 */



void setup()
{
  Serial.begin(9600);


  pinMode(11, OUTPUT);
}


void loop()
{
  Serial.println(analogRead(A0));
  if (analogRead(A0) > 20) {
    // 可改成蜂嗚器
    digitalWrite(11, HIGH);
    delay(1000);

  } else {
    digitalWrite(11, LOW);
    delay(1000);

  }
}
