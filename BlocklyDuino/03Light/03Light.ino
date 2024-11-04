/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Thu, 24 Sep 2020 01:30:02 GMT
 */



void setup()
{
  Serial.begin(9600);


  pinMode(11, OUTPUT);
}


void loop()
{
  // 晚上自動開燈
Serial.println(analogRead(A0));
  if (analogRead(A0) > 0) {
    digitalWrite(11, HIGH);
    // 避免LED閃爍
    delay(1000);

  } else {
    digitalWrite(11, LOW);
    delay(1000);

  }
}