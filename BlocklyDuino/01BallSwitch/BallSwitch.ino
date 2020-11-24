/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Thu, 24 Sep 2020 00:48:09 GMT
 */



int i;

void setup()
{
  Serial.begin(9600);


  pinMode(LED_BUILTIN, OUTPUT);
}


void loop()
{
  i = analogRead(A5);
  Serial.println(i);
  if (i >= 512) {
    digitalWrite(LED_BUILTIN, HIGH);

  } else {
    digitalWrite(LED_BUILTIN, LOW);

  }
}