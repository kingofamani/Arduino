/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Fri, 02 Dec 2022 11:56:58 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include "Adafruit_Keypad.h"

char keyPadChar='\0';
const byte keyRowsCount = 4;
const byte keyColsCount = 4;
char keys[keyRowsCount][keyColsCount] = {{'1', '2', '3', 'A'}, {'4', '5', '6', 'B'}, {'7', '8', '9', 'C'}, {'*', '0', '#', 'D'}};
byte rowPins[keyRowsCount] = {11,10,9,8};
byte colPins[keyColsCount] = {7,6,5,4};
Adafruit_Keypad customKeypad = Adafruit_Keypad( makeKeymap(keys), rowPins, colPins, keyRowsCount, keyColsCount);

void checkPad(keypadEvent e)
{
  if (((char)e.bit.KEY!='\0')&&(e.bit.EVENT == KEY_JUST_PRESSED))
    checkPadPress();
  else if (((char)e.bit.KEY!='\0')&&(e.bit.EVENT == KEY_JUST_RELEASED))
    checkPadRelease();
}

void checkPadPress()
{
  Serial.println(String(keyPadChar));
}

void checkPadRelease()
{
}

void setup()
{
  Serial.begin(9600);

  customKeypad.begin();
}


void loop()
{
  customKeypad.tick();
  if(customKeypad.available()){
    keypadEvent e = customKeypad.read();
    keyPadChar=(char)e.bit.KEY;
    checkPad(e);
  }
}