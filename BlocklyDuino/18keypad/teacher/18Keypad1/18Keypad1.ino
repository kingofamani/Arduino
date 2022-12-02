/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Tue, 15 Mar 2022 07:26:54 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include <Keypad.h>

char key;

char keys[4] = {{'1', '2', '3', 'A'}, {'4', '5', '6', 'B'}, {'7', '8', '9', 'C'}, {'*', '0', '#', 'D'}};

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
    Serial.println(key);
  }
}