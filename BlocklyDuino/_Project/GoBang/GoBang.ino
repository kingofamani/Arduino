/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Fri, 11 Mar 2022 06:58:33 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


char pos = '1';

char go = 'o';

char goBang[9] = {'-', '-', '-', '-', '-', '-', '-', '-', '-'};

String wins[8] = {"123", "456", "789", "147", "258", "369", "159", "357"};

void setup()
{
  Serial.begin(9600);


}


void loop()
{
  if (Serial.available() == 1) {
    //下一子
    pos = Serial.read();
    Serial.println(pos);
    goBang[String(pos).toInt() - 1] = go;
    //顯示五子棋所有位置
    for (int i = 0; i <= 8; i++) {
      Serial.print((goBang[i]));
      Serial.print(",");
      if ((i + 1) % 3 == 0) {
        Serial.println("");
      }
    }
    //判斷勝負
    Serial.print("從陣列取值：");
    Serial.println((wins[String(pos).toInt() - 1].charAt(0)));
    Serial.println((wins[String(pos).toInt() - 1].charAt(1)));
    Serial.println((wins[String(pos).toInt() - 1].charAt(2)));
    //圈叉互換
    if (go == 'o') {
      go = 'x';
    } else {
      go = 'o';
    }
  }
}