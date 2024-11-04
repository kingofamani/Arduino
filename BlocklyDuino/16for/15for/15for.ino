/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 11 Oct 2021 06:59:57 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


int starPos = 5;

int starNum = 1;

void setup()
{
  Serial.begin(9600);

  for (int i = 1; i <= 45; i++) {
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
//

}