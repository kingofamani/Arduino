/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 26 Oct 2020 01:52:05 GMT
 */



int i;

int j;

void setup()
{
  Serial.begin(9600);

  for (i = 2; i <= 9; i++) {
    for (j = 1; j <= 9; j++) {
      Serial.print(i);
      Serial.print("x");
      Serial.print(j);
      Serial.print("=");
      Serial.print((i * j));
      Serial.print("\t");
    }
    Serial.println("");
  }
}


void loop()
{
  // 印出九九乘法，所有的算式和答案

}
