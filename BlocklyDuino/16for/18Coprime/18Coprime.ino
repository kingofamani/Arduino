/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 14 Mar 2022 13:32:17 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


String nums = "";

int number1 = 0;

int number2 = 0;

int splitToNum(String data, char separator, int index) {
  int found = 0;
  int strIndex[2] = {0, -1};
  int maxIndex = (data.length()) - 1;
  int i = 0;
  for (i = 0; i <= maxIndex && found <= index; i++) {
  if (data.charAt((i + 1 - 1)) == separator || i == maxIndex) {
    found = found + 1;
    strIndex[0] = (strIndex[1]) + 1;
    if (i == maxIndex) {
      strIndex[1] = i + 1;
    } else {
      strIndex[1] = i;
    }
  }
  }
  String numStr = (data.substring(strIndex[0], strIndex[1]));
  int nu = (numStr.toInt());
  if (found > index) {
    return (nu);
  } else {
    return (0);
  }
}

void setup()
{
  Serial.begin(9600);

  Serial.println("請輸入兩個數字，用逗號隔開(例如12,20)：");
}


void loop()
{
  if (Serial.available() == 1) {
    nums = Serial.readString();
    number1 = splitToNum(nums, ',', 0);
    number2 = splitToNum(nums, ',', 1);
    Serial.println(number1);
    Serial.println(number2);
    Serial.println("請重新輸入兩個數字：");
  }
}
