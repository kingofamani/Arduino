/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 26 Oct 2020 02:37:08 GMT
 */



int  i;

int  j;

void setup()
{
  Serial.begin(9600);

  for (i = 1; i <= 5; i++) {
    for (j = 1; j <= 3; j++) {
      Serial.print("★");
    }
    Serial.println("");
  }
}


void loop()
{
  // ★★★
// ★★★
// ★★★
// ★★★
// ★★★

}