void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(7, INPUT);
}

void loop() {
  // 按下去1，放開0
  Serial.println(digitalRead(7));
  delay(1000);
}
