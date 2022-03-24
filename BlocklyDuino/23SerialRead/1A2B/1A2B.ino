/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Thu, 24 Mar 2022 07:44:27 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


int Ans[4] = {3, 8, 2, 5};

int Num[4] = {0, 0, 0, 0};

int A = 0;

int B = 0;

int Count = 0;

void judgeAB() {
}

void setup()
{
  Serial.begin(9600);

  randomSeed(analogRead(0));
  Serial.println("請輸入4位數字(數字不能重複)：");
}


void loop()
{
  if (Serial.available() == 1) {
    Count = Count + 1;
    int InputNum = (Serial.parseInt());
    //將數字1個1個存入Num陣列裡
    for (int i = 0; i <= 3; i++) {
      //https://blog.csdn.net/phenixyf/article/details/77993417
      int n = InputNum / (pow(10,(3 - i)));
      Num[i] = n % 10;
    }
    //判斷幾A幾B
    for (int i = 0; i <= 3; i++) {
      for (int j = 0; j <= 3; j++) {
        if (Ans[i] == Num[j]) {
          if (i == j) {
            A = A + 1;
          } else {
            B = B + 1;
          }
        }
      }
    }
    //判斷是否成功
    if (A == 4) {
      Serial.println((String("恭喜你答對了！答案是：")+String(InputNum)));
      Serial.println((String("你總共猜了")+String(Count)+String("次")));
      Count = 0;
      A = 0;
      B = 0;
    } else {
      Serial.println((String(InputNum)+String("：")+String(A)+String("A")+String(B)+String("B")+String("，請輸入4位數字(數字不能重複)：")+String("3825")));
      A = 0;
      B = 0;
    }
  }
}