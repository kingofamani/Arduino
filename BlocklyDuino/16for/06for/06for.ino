/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 26 Oct 2020 02:31:52 GMT
 */



int i;

void setup()
{
  Serial.begin(9600);

  for (i = 1; i <= 9; i++) {
    Serial.println((i * 5));
  }
}


void loop()
{
  // 印出九九乘法，5的答案

}