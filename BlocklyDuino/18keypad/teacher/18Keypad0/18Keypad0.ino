/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Tue, 15 Mar 2022 07:25:29 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


char key = ' ';

String num1 = "";

String num2 = "";

char opt = '?';

boolean checkIsNumber(char key) {
  char N[] = "1234567890";
  //一定要大寫NULL
  if ((strchr(N, key)) != (NULL)) {
    return (true);
  } else {
    return (false);
  }
}

boolean checkIsOpt() {
  return (key == '+' || key == '-' || key == '*' || key == '/');
}

void reStart() {
  opt = '?';
  num1 = "";
  num2 = "";
}

void cal() {
  long ans = 0;
  switch (opt) {
    case '+':
      ans = (num1.toInt()) + (num2.toInt());
      break;
    case '-':
      ans = (num1.toInt()) - (num2.toInt());
      break;
    case '*':
      ans = (num1.toInt()) * (num2.toInt());
      break;
    case '/':
      ans = (num1.toInt()) / (num2.toInt());
      break;
  }
  Serial.println((String(num1)+String(opt)+String(num2)+String("=")+String(ans)));
}

void setup()
{
  Serial.begin(9600);

  //key輸入的字元
  //num1第一個數字
  //num2第二個數字
  //加減乘除運算符號
  Serial.println("請開始四則運算：");
}


void loop()
{
  if (Serial.available() == 1) {
    key = Serial.read();
    if (checkIsNumber(key)) {
      if (opt == '?') {
        num1 += key;
        Serial.println(num1);
      } else {
        num2 += key;
        Serial.println(num2);
      }
    } else if (checkIsOpt()) {
      opt = key;
      Serial.println(opt);
    } else if (key == '=') {
      cal();
      reStart();
      Serial.println("請開始四則運算：");
    } else {
      Serial.println("輸入錯誤！");
    }
  }
}