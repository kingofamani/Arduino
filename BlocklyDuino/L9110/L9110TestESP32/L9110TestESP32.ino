//Generated Date: Sun, 24 Sep 2023 07:58:09 GMT



byte m1aL9110=16;
byte m1bL9110=17;
byte m2aL9110=21;
byte m2bL9110=22;
byte m1bCH=13;
byte m2bCH=14;

int ForwardTime = 500;
int turnTime = 300;
int stopTime = 1000;
int ForwardSpeed = 255;
int turnSpeed = 255;
void forward() {
  digitalWrite(m1aL9110,1);
  ledcWrite(m1bCH,255-ForwardSpeed);
  digitalWrite(m2aL9110,1);
  ledcWrite(m2bCH,255-ForwardSpeed);
  delay(ForwardTime);
}

void backward() {
  digitalWrite(m1aL9110,0);
  ledcWrite(m1bCH,ForwardSpeed);
  digitalWrite(m2aL9110,0);
  ledcWrite(m2bCH,ForwardSpeed);
  delay(ForwardTime);
}

void turnRight() {
  digitalWrite(m1aL9110,1);
  ledcWrite(m1bCH,255-turnSpeed);
  digitalWrite(m2aL9110,1);
  ledcWrite(m2bCH,255);
  delay(turnTime);
}

void turnLeft() {
  digitalWrite(m2aL9110,1);
  ledcWrite(m2bCH,255-turnSpeed);
  digitalWrite(m1aL9110,1);
  ledcWrite(m1bCH,255);
  delay(turnTime);
}

void stopCar() {
  digitalWrite(m1aL9110,1);
  ledcWrite(m1bCH,255);
  digitalWrite(m2aL9110,1);
  ledcWrite(m2bCH,255);
  delay(stopTime);
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
  stopCar();
  turnRight();
  stopCar();
  forward();
  stopCar();
  turnLeft();
  stopCar();
}
