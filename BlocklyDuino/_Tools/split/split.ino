/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Wed, 09 Dec 2020 02:33:14 GMT
 */



String num;

String number1;

String number2;

String split(String data, char separator, int index)
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
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
void abc2() {
}

void setup()
{
  Serial.begin(9600);

  num = "15*20";
  number1 = "";
  number2 = "";
  number1 = split(num, \'*\', 0);
  number2 = split(num, \'*\', 1);
  Serial.println((number1.toInt()));
  Serial.println((number2.toInt()));
}


void loop()
{

}