/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 14 Mar 2022 12:39:30 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


String num = "15";

String factor = "";

void setup()
{
  Serial.begin(9600);

  for (int i = 1; i <= (num.toInt()); i++) {
    if ((num.toInt()) % i == 0) {
      factor = String(factor)+String(i)+String(",");
    }
  }
  Serial.println(factor);
}


void loop()
{

}