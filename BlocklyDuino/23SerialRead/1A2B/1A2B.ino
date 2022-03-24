/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Thu, 24 Mar 2022 13:57:18 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


int Ans[4] = {-1, -1, -1, -1};

int Num[4] = {0, 0, 0, 0};

int A = 0;

int B = 0;

int Count = 0;

boolean checkIsAns0() {
  int sum = 0;
  for (int i = 0; i <= 3; i++) {
    sum = sum + (Ans[i + 0]);
  }
  if (sum == -4) {
    return (true);
  } else {
    return (false);
  }
}

void setAns() {
  for (int i = 0; i <= 3; i++) {
    int n = 0;
    if (i == 0) {
      n = random(1, 10);
      Ans[i] = n;
    } else {
      boolean isOk = false;
      while (!(isOk == true)) {
        n = random(0, 10);
        int c = 0;
        for (int j = 0; j <= 3; j++) {
          if (n == Ans[j]) {
            c = c + 1;
          }
        }
        if (c == 0) {
          isOk = true;
          Ans[i] = n;
        } else {
          isOk = false;
        }
      }
    }
  }
}

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
  if (checkIsAns0()) {
    //亂數產生答案
    setAns();
    Serial.print("產生的Ans：");
    for (int i = 0; i <= 3; i++) {
      Serial.print((Ans[i]));
    }
    Serial.println("");
  }
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
      A = 0;
      B = 0;
      Serial.println("");
      Serial.println("===============新的一局===============");
      Count = 0;
      for (int i = 0; i <= 3; i++) {
        Ans[i] = -1;
      }
    } else {
      Serial.println((String(InputNum)+String("：")+String(A)+String("A")+String(B)+String("B")+String("，請輸入4位數字(數字不能重複)：")+String("3825")));
      A = 0;
      B = 0;
    }
  }
}