/*
isAlphaNumeric()  // 判断是否为字母数字

isAlpha()        // 判断是否为字母

isAscii()        // 判断是否为 ASCII 码

isWhitespace()    // 判断是否为空格符

isControl()          // 判断是否为控制字符

isDigit()              // 判断是否为数字

isGraph()            // 判断是否为可打印的字符，不是空格

isLowerCase()       // 判断是否为小写

isPrintable()        // 判断是否为可打印的字符

isPunct()            // 判断是否为标点符号

isSpace()            // 判断是否为空格

isUpperCase()     // 判断是否为大写

isHexadecimalDigit()  // 判断是否为十六进制数字(i.e. 0 - 9, a - F, or A - F)
*/
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  int x = 10;
  char y = '10';
  Serial.println(isDigit(5));//0
  Serial.println(isDigit('5'));//1
  Serial.println(isDigit("5"));//0
  Serial.println(isDigit('a'));//0
  Serial.println(isDigit("a"));//0
  Serial.println(isDigit(x));//0
  Serial.println(isDigit(y));//1
  Serial.println();
  Serial.println(isAlphaNumeric(5));//0
  Serial.println(isAlphaNumeric('5'));//1
  Serial.println(isAlphaNumeric("5"));//0
  Serial.println(isAlphaNumeric('a'));//1
  Serial.println(isAlphaNumeric("a"));//0
  Serial.println(isAlphaNumeric(x));//0
  Serial.println(isAlphaNumeric(y));//1
}

void loop() {
  // put your main code here, to run repeatedly:

}
