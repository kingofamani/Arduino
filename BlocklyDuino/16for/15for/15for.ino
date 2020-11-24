/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 26 Oct 2020 03:28:37 GMT
 */



int starPos;

int starNum;

int i;

void setup()
{
  Serial.begin(9600);

  starPos = 5;
  starNum = 1;
  for (i = 1; i <= 45; i++) {
    if (i >= starPos && i < starPos + starNum) {
      Serial.print("★");

    } else {
      Serial.print("　");

    }
    if (i == (starPos + starNum) - 1) {
      starPos = starPos + 8;
      starNum = starNum + 2;

    }
    if (i % 9 == 0) {
      Serial.println("");

    }
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