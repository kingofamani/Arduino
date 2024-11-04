/*
   Generated using BlocklyDuino:

   https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt

   Date: Wed, 18 Nov 2020 01:54:59 GMT
*/

#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//鍵盤
char key;//單一按鍵值
String num = ""; //數字組合
char N[] = "1234567890";

const byte ROWS = 4; // 列數(橫的)
const byte COLS = 4; // 行數(直的)
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {11, 10, 9, 8}; //定義列的腳位
byte colPins[COLS] = {7, 6, 5, 4}; //定義行的腳位
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

//螢幕
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  Serial.begin(9600);

  //螢幕
  lcd.init();
  lcd.backlight();
}


void loop()
{
  //按鍵
  key = (keypad.getKey());
  if (key) {//有按按鍵
    lcd.clear();

    if (strchr(N, key) != NULL) { //數字
      num += key;

      lcd.setCursor((16 - num.length()), 0);
      lcd.print(num);

      Serial.println(key);
    } else if (key == '#') { //確認鍵
      Serial.println(num);
      showAnswer();

      num = "";
    } else if (key == 'D') { //清除鍵
      num = "";
    }


  }//end of 有按按鍵

}//end of loop

void showAnswer() { 
  lcd.setCursor(0, 1); 
  if (num.length() == 0) {    
    lcd.print("You don't key in");
  } else {
    calPrimeNumber();
  }
}

/*
   若要測試大質數，可至以下網址找大質數
   https://bit.ly/36aGMRO
*/
void calPrimeNumber() {
  boolean prime = true;
  unsigned long number = num.toInt();//max 4,294,967,295

  if (number == 0 || number == 1 || number == 2) {
    lcd.print("It's NOT a prime");
    return;
  }

  lcd.print("Wait a moment...");
  for (int i = 2; i < (number - 1); i++) {
    //判是是否可以整除
    if (number % i == 0) {
      prime = false;
      break;
    }
  }

  lcd.clear();
  lcd.setCursor(0, 1);
  if (prime) {
    lcd.print("It's A prime");
  } else {
    lcd.print("It's NOT a prime");
  }
}

void progress() {

}
