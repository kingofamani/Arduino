/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Wed, 09 Dec 2020 04:34:27 GMT
 */



String num;

int number1;

int number2;

int maxFactor;

int big;

int i;

int splitToNum(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;
  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  String numStr = data.substring(strIndex[0], strIndex[1]);
  int num = numStr.toInt();
  return found > index ? num : 0;
}
void abc() {
}

void setup()
{
  Serial.begin(9600);

  num = "15*20";
  number1 = 0;
  number2 = 0;
  number1 = splitToNum(num, \'*\', 0);
  number2 = splitToNum(num, \'*\', 1);
  maxFactor = 0;
  big = 0;
  if (number1 > number2) {
    big = number1;

  } else {
    big = number2;

  }
  for (i = 1;
      (1 <= big) ? i <= big : i >= big;
      i += (1 <= big) ? 1 : -1) {
    if (number1 % i == 0 && number2 % i == 0) {
      maxFactor = i;

    }
  }
  Serial.println(maxFactor);
}


void loop()
{

}