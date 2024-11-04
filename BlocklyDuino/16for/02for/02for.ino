/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 26 Oct 2020 02:29:30 GMT
 */



int i;

void setup()
{
  Serial.begin(9600);

  for (i = 0; i <= 9; i++) {
    Serial.print(i);
    Serial.println("德音");
  }
}


void loop()
{

}