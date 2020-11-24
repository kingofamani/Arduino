/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Thu, 24 Sep 2020 05:25:53 GMT
 */



float Temp;

void setup()
{
  Serial.begin(9600);


}


void loop()
{
  Temp = analogRead(A0);
  Temp = Temp * 0.4882812;
  Serial.println(Temp);
}