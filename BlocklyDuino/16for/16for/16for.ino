/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 14 Mar 2022 12:29:05 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


int prime = true;

int num = 11;

void setup()
{
  Serial.begin(9600);

  for (int i = 2; i <= num - 1; i++) {
    if (num % i == 0) {
      prime = false;
      break;
    }
  }
  if (prime == true) {
    Serial.println("質數");
  } else {
    Serial.println("不是質數");
  }
}


void loop()
{

}