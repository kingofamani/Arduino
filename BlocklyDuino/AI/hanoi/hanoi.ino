/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Fri, 01 Apr 2022 06:37:53 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


int n = 5;

char x = 'A';

char y = 'B';

char z = 'C';

void hanoi(int n, char x, char y, char z) {
  if (n == 1) {
    Serial.println((String(x)+String("→")+String(z)));
  } else {
    ////先將較小的盤子移到輔助柱子
    hanoi(n - 1, x, z, y);
    ////移最大的盤子到目的
    Serial.println((String(x)+String("→")+String(z)));
    ////將較小的盤子移到目的
    hanoi(n - 1, y, x, z);
  }
}

void setup()
{
  Serial.begin(9600);

  //河內塔
  //圓盤數量
  //左柱(開始)
  //中柱
  //右柱
  hanoi(n, x, y, z);
}


void loop()
{

}