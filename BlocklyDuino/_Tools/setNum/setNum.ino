/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Thu, 07 Apr 2022 00:33:54 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


void setNum(int InputNum) {
  //此函數可以將4位數的整數，1個1個放入陣列裡
  for (int i = 0; i <= 3; i++) {
    //https://blog.csdn.net/phenixyf/article/details/77993417
    //InputNum就是4位數的整數，例如1357
    int n = InputNum / (pow(10,(3 - i)));
    //Num就是放4個數字的陣列，例如Num[ ]={1,3,5,7}
    Num[i] = n % 10;
  }
}

void setup()
{

}


void loop()
{

}