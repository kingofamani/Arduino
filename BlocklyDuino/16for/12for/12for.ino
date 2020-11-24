/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 26 Oct 2020 02:39:46 GMT
 */



int i;

int  j;

void setup()
{
  Serial.begin(9600);

  for (i = 1; i <= 5; i++) {
    for (j = 1;
        (1 <= i) ? j <= i : j >= i;
        j += (1 <= i) ? 1 : -1) {
      Serial.print("★");
    }
    Serial.println("");
  }
}


void loop()
{
  // ★
// ★★
// ★★★
// ★★★★
// ★★★★★

}