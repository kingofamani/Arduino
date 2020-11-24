/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 26 Oct 2020 02:44:54 GMT
 */



int i;

int num;

int  j;

void setup()
{
  Serial.begin(9600);

  for (i = 1; i <= 5; i++) {
    num = i * 2;
    num = num - 1;
    for (j = 1;
        (1 <= num) ? j <= num : j >= num;
        j += (1 <= num) ? 1 : -1) {
      Serial.print("★");
    }
    Serial.println("");
  }
}


void loop()
{
  // ★
// ★★★
// ★★★★★
// ★★★★★★★
// ★★★★★★★★★

}