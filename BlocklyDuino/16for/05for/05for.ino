/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 26 Oct 2020 02:31:13 GMT
 */



int i;

void setup()
{
  Serial.begin(9600);

  for (i = 1; i <= 100; i++) {
    Serial.print(i);
    Serial.print(",");
    if (i % 10 == 0) {
      Serial.println("");

    }
  }
}


void loop()
{
  // 1、印出1~100
// 2、每10個數字換行

}