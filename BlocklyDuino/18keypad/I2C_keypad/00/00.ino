//Generated Date: Tue, 09 Jan 2024 00:08:00 GMT

#include <Wire.h>
char i2cKey = '\0';  //不能是null

void setup()
{
  Serial.begin(9600);

  Wire.begin();


}

void loop()
{
  keypadLoop();
  if (i2cKey !='\0') {
    Serial.println((i2cKey));
  }
  if (checkIsNumber((i2cKey))) {
    Serial.println("你按了數字");
  }
}

void keypadLoop() {
  volatile int code;
  Wire.beginTransmission(0x27);
  Wire.write(3);
  Wire.endTransmission();
  Wire.requestFrom(0x27, 1);
  while (Wire.available()) {
    char code = Wire.read();
    if (code != 16) {
      i2cKey = getKeyChar(code);
    }
  }
}
char getKeyChar(char code) {
  char keys[16] = {
    '0', '1', '2', '3',
    '4', '5', '6', '7',
    '8', '9', 'A', 'B',
    'C', 'D', '*', '#'
  };
  return keys[code];
}
int charToInt(char c) {
  int num = c - '0';
  return num;
}
boolean checkIsNumber(char key) {
  char N[] = "1234567890";
  //一定要大寫NULL
  if ((strchr(N, key)) != (NULL)) {
    return (true);
  } else {
    return (false);
  }
}
