/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Wed, 16 Mar 2022 00:24:14 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


char key = ' ';

String number1 = "";

String number2 = "";

int whichNum = 1;

boolean checkIsNumber(char key) {
  char N[] = "1234567890";
  //一定要大寫NULL
  if ((strchr(N, key)) != (NULL)) {
    return (true);
  } else {
    return (false);
  }
}

boolean checkIsCoprime(String number1, String number2) {
}

void setup()
{
  Serial.begin(9600);

  //目前正在輸入哪一個數
  Serial.println("判斷互質，請輸入第1個數字(按,換下一個數字，按=開始計算)：");
}


void loop()
{
  if (Serial.available() == 1) {
    key = Serial.read();
    if (checkIsNumber(key)) {
      if (whichNum == 1) {
        number1 += key;
      } else if (whichNum == 2) {
        number2 += key;
      }
    } else if (key == ',') {
      whichNum = 2;
    } else if (key == '=') {
      int factors1[] = {};
      int factors2[] = {};
      for (int i = 1; i <= String(number1).toInt(); i++) {
        if (String(number1).toInt() % i == 0) {
          factors1[factors1[(sizeof(factors1)/sizeof(factors1[0])-1)-0]] = i;
        }
      }
      for (int i = 0; i <= (sizeof(factors1)/sizeof(factors1[0])) - 1; i++) {
        Serial.println((factors1[i]));
      }
    }
  }
}