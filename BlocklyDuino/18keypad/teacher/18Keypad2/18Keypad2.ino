/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Tue, 15 Mar 2022 07:28:01 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include <Keypad.h>

char key;

String msgs[9] = {"聖誕快樂", "(>_<)", "雪花黑白飄，麋鹿被狗咬", "烤肉最怕-肉跟你裝熟", "烤肉最怕-蛤仔搞自閉", "﹒°．﹒•°∴°•°∴°願摘顆星送你 °∴°﹒°．﹒•°", "-:*生*:-.-:*日*:--:*快*:-.-:*樂*:-:", "(^o^)", "(~*_*~)"};

char keys[4][4] = {{'1', '2', '3', 'A'}, {'4', '5', '6', 'B'}, {'7', '8', '9', 'C'}, {'*', '0', '#', 'D'}};

byte rowPins[4] = {11, 10, 9, 8};

byte colPins[4] = {7, 6, 5, 4};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, 4, 4 );
void keypad_0() {
}

void setup()
{
  Serial.begin(9600);

  //將keys[4]改成keys[4][4]
}


void loop()
{
  key = keypad.getKey();
  if (key) {
    if (String(key).toInt() > 0) {
      Serial.println((msgs[key - 1]));
    } else {
      Serial.println("錯誤！請按1~9數字");
    }
  }
}
