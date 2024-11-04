/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 09 Nov 2020 02:10:38 GMT
 */



void setup()
{
  Serial.begin(9600);


  pinMode(3, OUTPUT);
}


void loop()
{
  digitalWrite(3, HIGH);
  delay(3000);
  digitalWrite(3, LOW);
  delay(1000);
}
