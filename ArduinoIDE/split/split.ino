void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  String num = "1300*2493";

  /*

    分割字串成String
f
  */
  //  String number1 = split(num, '*', 0);
  //  String number2 = split(num, '*', 1);
  //  int num1 = number1.toInt();
  //  int num2 = number2.toInt();
  //  int num3 = (num1 + num2);
  //  Serial.println("number1:" + number1);
  //  Serial.println("number2:" + number2);
  //  Serial.print("plus:");
  //  Serial.println(num3);


  /*

    分割字串成Int

  */
  int number1 = splitToNum(num, '*', 0);
  int number2 = splitToNum(num, '*', 1);
  int num3 = (number1 + number2);

  Serial.print("number1:");
  Serial.println(number1);
  Serial.print("number2:");
  Serial.println( number2);
  Serial.print("plus:");
  Serial.println(num3);

}

void loop() {
  // put your main code here, to run repeatedly:

}

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
