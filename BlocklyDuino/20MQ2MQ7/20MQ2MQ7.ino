/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Thu, 05 Nov 2020 00:04:10 GMT
 */



int i;

void setup()
{
  Serial.begin(9600);

  Serial.println("暖機20秒，請稍候…");
  for (i = 1; i <= 20; i++) {
    delay(1000);
    Serial.print(i);
    Serial.print(",");
  }
  Serial.println("暖機完畢！");
}


void loop()
{
  Serial.println(analogRead(A0));
  delay(1000);
}