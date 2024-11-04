/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 14 Mar 2022 12:38:51 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


String num = "";

String factor = "";

void setup()
{
  Serial.begin(9600);

  Serial.println("請輸入數字：");
}


void loop()
{
  if (Serial.available() == 1) {
    num = Serial.readString();
    for (int i = 1; i <= (num.toInt()); i++) {
      if ((num.toInt()) % i == 0) {
        factor = String(factor)+String(i)+String(",");
      }
    }
    Serial.println((String(num)+String("的因數有：")+String(factor)));
    //重新開始
    num = "";
    factor = "";
  }
}