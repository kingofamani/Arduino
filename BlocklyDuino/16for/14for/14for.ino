/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 26 Oct 2020 03:31:09 GMT
 */



int i;

int space;

int  k;

int num;

int  j;

void setup()
{
  Serial.begin(9600);

  for (i = 1; i <= 5; i++) {
    //印出空格
    space = 5 - i;
    if (space != 0) {
      for (k = 1;
          (1 <= space) ? k <= space : k >= space;
          k += (1 <= space) ? 1 : -1) {
        // 全型空格
        Serial.print("　");
      }

    }
    //印出星星
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
  //             ★
//          ★★★
//       ★★★★★
//    ★★★★★★★
// ★★★★★★★★★

}