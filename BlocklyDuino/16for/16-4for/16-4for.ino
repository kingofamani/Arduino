/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Wed, 16 Mar 2022 13:58:42 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


char key = ' ';

boolean prime = true;

String num = "";

int count = 0;

boolean checkIsNumber(char key) {
  char N[] = "1234567890";
  //一定要大寫NULL
  if ((strchr(N, key)) != (NULL)) {
    return (true);
  } else {
    return (false);
  }
}

void reStart() {
  prime = true;
  key = ' ';
  num = "";
  count = 0;
  Serial.println("請重新輸入數字(按=開始計算)：");
}

void checkPrime() {
  Serial.print("計算中…");
  for (int i = 2; i <= String(num).toInt() - 1; i++) {
    running(i);
    if (String(num).toInt() % i == 0) {
      prime = false;
      break;
    }
  }
  if (prime == true) {
    Serial.println((String(num)+String("是質數")));
  } else {
    Serial.println((String(num)+String("不是質數")));
  }
}

void running(int i) {
  if (String(num).toInt() > 10000) {
    int part = String(num).toInt() / 100;
    if (i % part == 0) {
      count = count + 1;
      Serial.print((String(count)+String("%")));
    }
  }
}

void setup()
{
  Serial.begin(9600);

  Serial.println("請輸入數字(按=開始計算)：");
}


void loop()
{
  if (Serial.available() == 1) {
    key = Serial.read();
    if (checkIsNumber(key)) {
      num += key;
      Serial.println(num);
    } else if (key == '=') {
      //開始判斷質數
      checkPrime();
      //重新設定變數值
      reStart();
    }
  }
}