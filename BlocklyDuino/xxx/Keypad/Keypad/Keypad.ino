/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 30 Nov 2020 05:44:57 GMT
 */

#include <Keypad.h>

char key;

const byte ROWS = 4; // 列數(橫的)
const byte COLS = 4; // 行數(直的)
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {11, 10, 9, 8}; //定義列的腳位
byte colPins[COLS] = {7, 6, 5, 4}; //定義行的腳位
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
void keypad_0() {
}

void setup()
{
  Serial.begin(9600);


}


void loop()
{
  /*
  ★★將要\\'取代成'
*/

key = (keypad.getKey());
  if (key) {
    Serial.println(key);

  }
}
