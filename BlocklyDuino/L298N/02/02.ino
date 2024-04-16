//要拔掉ENA,ENB的兩個jumper
#define L298N_IN1 2
#define L298N_IN2 4
#define L298N_IN3 6
#define L298N_IN4 7
#define L298N_ENA 3//PWM
#define L298N_ENB 5//PWM

//轉速(80~255)
const int FSpeed = 255;
const int BSpeed = 150;
const int RSpeed = 150;
const int LSpeed = 150;

//轉動時間(毫秒)
const int FTimer = 1000;
const int BTimer = 1000;
const int RTimer = 1000;
const int LTimer = 1000;
const int STimer = 3000;

void forward() {
  digitalWrite(L298N_IN1, HIGH);
  digitalWrite(L298N_IN2, LOW);
  analogWrite(L298N_ENA, FSpeed);

  digitalWrite(L298N_IN3, LOW);
  digitalWrite(L298N_IN4, HIGH);
  analogWrite(L298N_ENB, FSpeed);
}

void backward() {
  digitalWrite(L298N_IN1, LOW);
  digitalWrite(L298N_IN2, HIGH);
  analogWrite(L298N_ENA, BSpeed);

  digitalWrite(L298N_IN3, HIGH);
  digitalWrite(L298N_IN4, LOW);
  analogWrite(L298N_ENB, BSpeed);
}

void turnLeft() {
  digitalWrite(L298N_IN1, LOW);
  digitalWrite(L298N_IN2, HIGH);
  analogWrite(L298N_ENA, LSpeed);

  digitalWrite(L298N_IN3, LOW);
  digitalWrite(L298N_IN4, HIGH);
  analogWrite(L298N_ENB, LSpeed);
}

void turnRight() {
  digitalWrite(L298N_IN1, HIGH);
  digitalWrite(L298N_IN2, LOW);
  analogWrite(L298N_ENA, RSpeed);

  digitalWrite(L298N_IN3, HIGH);
  digitalWrite(L298N_IN4, LOW);
  analogWrite(L298N_ENB, RSpeed);
}

void stopCar() {
  digitalWrite(L298N_IN1, LOW);
  digitalWrite(L298N_IN2, LOW);
  analogWrite(L298N_ENA, FSpeed);

  digitalWrite(L298N_IN3, LOW);
  digitalWrite(L298N_IN4, LOW);
  analogWrite(L298N_ENB, BSpeed);
}

void setup() {
  Serial.begin(9600);

  pinMode(L298N_IN1, OUTPUT);
  pinMode(L298N_IN2, OUTPUT);
  pinMode(L298N_IN3, OUTPUT);
  pinMode(L298N_IN4, OUTPUT);
  pinMode(L298N_ENA, OUTPUT);
  pinMode(L298N_ENB, OUTPUT);

  digitalWrite(L298N_IN1, LOW);
  digitalWrite(L298N_IN2, LOW);
  digitalWrite(L298N_IN3, LOW);
  digitalWrite(L298N_IN4, LOW);
  digitalWrite(L298N_ENA, LOW);
  digitalWrite(L298N_ENB, LOW);

  stopCar();
  delay(500);
}

void loop() {
  forward();
  delay(FTimer);
  stopCar();
  delay(FTimer);

  backward();
  delay(BTimer);
  stopCar();
  delay(BTimer);

  turnRight();
  delay(RTimer);
  stopCar();
  delay(RTimer);

  turnLeft();
  delay(LTimer);
  stopCar();
  delay(LTimer);

  delay(STimer);
}
