/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Thu, 24 Sep 2020 01:10:42 GMT
 */



int a;

void setup()
{
  Serial.begin(9600);


  pinMode(10, OUTPUT);
}


void loop()
{
  a = (map(analogRead(A0),0,1023,0,255));
  Serial.println(a);
  analogWrite(10, a);
}