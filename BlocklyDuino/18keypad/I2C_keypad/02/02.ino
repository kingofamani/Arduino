#include <Wire.h>

char key = '.';  //不能是空

void setup() {
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  keypadLoop();
}

void keypadLoop() {
  volatile int code;
  Wire.beginTransmission(0x27);
  Wire.write(3);
  Wire.endTransmission();
  Wire.requestFrom(0x27, 1);
  while (Wire.available()) {
    code = Wire.read();
    if (code != 16) {  //沒按按鈕傳回16
      if (code <= 9) {
        int num = charToInt(codeToChar(code));
        Serial.println(num);
      } else {
        key = codeToChar(code);
        Serial.println(key);
      }
    }
  }
  delay(100);
}

char codeToChar(int code) {
  char key[16] = {
    '0', '1', '2', '3',
    '4', '5', '6', '7',
    '8', '9', 'A', 'B',
    'C', 'D', '*', '#'
  };
  return key[code];
}

int charToInt(char c) {
  int num = c - '0';
  return num;
}