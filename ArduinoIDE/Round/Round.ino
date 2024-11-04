int x;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("begin");
//  x = 139.49999999 + 0.5;
//  Serial.println(x);
  x = 139.5 + 0.5;
  Serial.println(x);
//  x = 139.99999999 + 0.5;
//  Serial.println(x);
  x = 140.0 + 0.5;
  Serial.println(x);
  x = 140.4 + 0.5;
  Serial.println(x);
//  x = 140.49999999 + 0.5;
//  Serial.println(x);
  delay(10000);
}
