/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Thu, 07 Apr 2022 00:37:36 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


int Ans[4] = {-1, -1, -1, -1};

int Num[4] = {0, 0, 0, 0};

int A = 0;

int B = 0;

int Count = 0;

int Best = 999;

boolean isWin = false;

void judgeAB() {
}

boolean checkIs4Num(int InputNum) {
  if (InputNum >= 1000 && InputNum <= 9999) {
    return (true);
  } else {
    Serial.println("錯誤，你輸入的不是4位數，請重新輸入：");
    return (false);
  }
}

boolean checkIsNumRepeat() {
  for (int i = 0; i <= 3; i++) {
    for (int j = 0; j <= 3; j++) {
      if (i != j) {
        if (Num[i] == Num[j]) {
          Serial.println("錯誤，你輸入的數字有重複，請重新輸入：");
          return (true);
        }
      }
    }
  }
  return (false);
}

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

void checkIsBest() {
  if (isWin) {
    if (Count < Best) {
      Serial.println((String("恭喜！你破紀錄了，你只用")+String(Count)+String("次，就猜中了！")));
      Best = Count;
    } else {
      Serial.println((String("可惜！你沒有破最佳紀錄，目前最快紀錄是")+String(Best)+String("次。")));
    }
  }
}

void checkIsWin(int InputNum) {
  if (A == 4) {
    isWin = true;
    Serial.println((String("恭喜你答對了！答案是：")+String(InputNum)));
    Serial.println((String("你總共猜了")+String(Count)+String("次")));
  } else {
    Serial.println((String(InputNum)+String("，")+String(A)+String("A")+String(B)+String("B")+String("，請輸入4位數字(數字不能重複)：")));
  }
}

void reStart() {
  if (isWin) {
    Serial.println("");
    Serial.println("===============新的一局===============");
    for (int i = 0; i <= 3; i++) {
      Ans[i] = -1;
    }
    Count = 0;
    isWin = false;
    Serial.println("請猜4位數字(數字不能重複)：");
  }
}

void setNum(int InputNum) {
  for (int i = 0; i <= 3; i++) {
    //https://blog.csdn.net/phenixyf/article/details/77993417
    int n = InputNum / (pow(10,(3 - i)));
    Num[i] = n % 10;
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

void setup()
{
  Serial.begin(9600);

  randomSeed(analogRead(0));
  Serial.println("請猜4位數字(數字不能重複)：");
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
    //檢查是否為4位數
    if (!(checkIs4Num(InputNum))) {
      return (0);
    }
    //將數字1個1個存入Num陣列裡
    setNum(InputNum);
    //判斷輸入的4位數是否重複
    if (checkIsNumRepeat()) {
      return (0);
    }
    //判斷幾A幾B
    judgeAB();
    //判斷是否成功
    checkIsWin(InputNum);
    //是否破紀錄
    checkIsBest();
    //是否重新開始
    reStart();
    A = 0;
    B = 0;
  }
}