/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Sat, 13 Mar 2021 10:41:10 GMT
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