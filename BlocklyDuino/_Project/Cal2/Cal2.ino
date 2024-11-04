/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Tue, 01 Dec 2020 00:52:03 GMT
 */

#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

char N[] = "1234567890";

boolean prime;

char key;

unsigned long number;

String num;

boolean isNum;

int j;

int i;

int len;

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
void keypad_0() {
}

LiquidCrystal_I2C lcd(0x27,16,2);
void LCM1602_0() {
}

void LCM1602_1() {
  //螢幕不能顯示中文
  lcd.init();
  lcd.backlight();
}

void showAnswer() {
  lcd.setCursor(0, 1);
  if ((num.length()) == 0) {
    lcd.print("You don\'t key in");

  } else {
    calPrimeNumber();

  }
}

void calPrimeNumber() {
  prime = true;
  number = (num.toInt());
  if (number == 0 || (number == 1 || number == 2)) {
    lcd.print("It\'s NOT a prime");
    return;

  }
  lcd.print("Wait a moment...");
  int j_end = number - 1;
  for (j = 2;
      (2 <= j_end) ? j <= j_end : j >= j_end;
      j += (2 <= j_end) ? 1 : -1) {
    if (number % j == 0) {
      prime = false;
      break;

    }
  }
  lcd.clear();
  lcd.setCursor(0, 1);
  if (prime) {
    lcd.print("It\'s A prime");

  } else {
    lcd.print("It\'s NOT a prime");

  }
}

void setup()
{
  Serial.begin(9600);

  //num宣告在Setup()，若放在頭檔區會被初始在loop()變成""
  num = "";
  LCM1602_1();
}


void loop()
{
  key = (keypad.getKey());
  if (key) {
    lcd.clear();
    isNum = false;
    for (i = 0; i <= 9; i++) {
      if ((N[i]) == key) {
        isNum = true;

      }
    }
    if (isNum) {
      num = String() + num + key;
      len = 16 - (num.length());
      lcd.setCursor(len, 0);
      lcd.print(num);
      Serial.println(key);

    } else if (key == '#') {
      Serial.println(num);
      showAnswer();
      num = "";
    } else if (key == 'D') {
      num = "";
    }

  }
}
