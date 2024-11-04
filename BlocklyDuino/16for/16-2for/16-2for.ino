/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 14 Mar 2022 12:27:04 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


boolean prime = true;

int num = 0;

void setup()
{
  Serial.begin(9600);

  Serial.println("請輸入數字：");
}


void loop()
{
  if (Serial.available() == 1) {
    num = (Serial.readString()).toInt();
    for (int i = 2; i <= num - 1; i++) {
      if (num % i == 0) {
        prime = false;
        break;
      }
    }
    if (prime == true) {
      Serial.println((String(num)+String("是質數")));
    } else {
      Serial.println((String(num)+String("不是質數")));
    }
    //重新設定變數值
    prime = true;
    Serial.println("請重新輸入數字：");
  }
}