/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Tue, 17 Nov 2020 05:20:40 GMT
 */



void setup()
{
  Serial.begin(9600);


}


void loop()
{
  Serial.println(analogRead(A0));
  delay(100);
}