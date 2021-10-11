/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 11 Oct 2021 06:58:56 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


void setup()
{
  Serial.begin(9600);

  for (int i = 1; i <= 5; i++) {
    //印出空格
    int space = 5 - i;
    if (space != 0) {
      for (int k = 1; k <= space; k++) {
        // 全型空格
        Serial.print("　");
      }
    }
    //印出星星
    int num = i * 2;
    num = num - 1;
    for (int j = 1; j <= num; j++) {
      Serial.print("★");
    }
    Serial.println("");
  }
}


void loop()
{

}