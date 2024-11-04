String inputString = "F,F,F,F,F,F,F,R,F,R,F,R,R,F,R,R,F,R,R,F,R,R,F,R,R,F,R,R,F,R,R,F,R,F,R,F,F,F,F,F,F,F,F,"; // 你的输入字符串
String values[200]; // 用于存储分割后的字符串的数组，根据逗号的数量设置数组大小

void setup() {
  Serial.begin(9600);

  // 使用 strtok() 函数分割字符串
  char *token = strtok((char *)inputString.c_str(), ",");
  int i = 0;

  while (token != NULL && i < 200) {
    values[i] = token;
    token = strtok(NULL, ",");
    i++;
  }

  // 打印分割后的字符串
  for (int j = 0; j < i; j++) {
    Serial.print("Value ");
    Serial.print(j);
    Serial.print(": ");
    Serial.println(values[j]);
  }
}

void loop() {
  // 你的循环代码
}
