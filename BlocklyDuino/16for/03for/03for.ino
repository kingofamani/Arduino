/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 26 Oct 2020 02:29:46 GMT
 */



int i;

void setup()
{
  Serial.begin(9600);

  for (i = 0; i <= 10; i++) {
    Serial.println((i * 2));
  }
}


void loop()
{
  // 印出偶數

}