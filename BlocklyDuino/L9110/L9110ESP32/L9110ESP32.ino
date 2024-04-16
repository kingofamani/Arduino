//Generated Date: Mon, 18 Sep 2023 01:44:27 GMT



byte m1aL9110=16;
byte m1bL9110=17;
byte m2aL9110=21;
byte m2bL9110=22;
byte m1bCH=13;
byte m2bCH=14;

void forward() {
  digitalWrite(m1aL9110,1);
  ledcWrite(m1bCH,255-255);
  digitalWrite(m2aL9110,1);
  ledcWrite(m2bCH,255-255);
}

void backward() {
  digitalWrite(m1aL9110,0);
  ledcWrite(m1bCH,255);
  digitalWrite(m2aL9110,0);
  ledcWrite(m2bCH,255);
}

void turnRight() {
  digitalWrite(m1aL9110,1);
  ledcWrite(m1bCH,255-255);
  digitalWrite(m2aL9110,1);
  ledcWrite(m2bCH,255);
}

void turnLeft() {
  digitalWrite(m2aL9110,1);
  ledcWrite(m2bCH,255-255);
  digitalWrite(m1aL9110,1);
  ledcWrite(m1bCH,255);
}

void stopCar() {
  digitalWrite(m1aL9110,1);
  ledcWrite(m1bCH,255);
  digitalWrite(m2aL9110,1);
  ledcWrite(m2bCH,255);
}

void setup()
{
  pinMode(m1aL9110,OUTPUT);
  pinMode(m2aL9110,OUTPUT);
  ledcSetup(m1bCH, 5000, 8);
  ledcAttachPin(m1bL9110,m1bCH);
  ledcSetup(m2bCH, 5000, 8);
  ledcAttachPin(m2bL9110,m2bCH);
  digitalWrite(m1aL9110,1);
  ledcWrite(m1bCH,255);
  digitalWrite(m2aL9110,1);
  ledcWrite(m2bCH,255);


}

void loop()
{
  forward();
  delay(500);
  backward();
  delay(500);
  turnLeft();
  delay(500);
  turnRight();
  delay(500);
  stopCar();
  delay(2000);
}
