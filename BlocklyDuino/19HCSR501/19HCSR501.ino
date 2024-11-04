/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Wed, 04 Nov 2020 23:17:57 GMT
 */



void setup()
{
  Serial.begin(9600);


  pinMode(3, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}


void loop()
{
  if (digitalRead(3) == HIGH) {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("開");
    delay(5000);

  } else {
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("關");

  }
}