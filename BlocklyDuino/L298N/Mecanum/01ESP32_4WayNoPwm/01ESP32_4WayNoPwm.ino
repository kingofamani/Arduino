//L298N腳位
#define L298N_IN1 14
#define L298N_IN2 27
#define L298N_IN3 26
#define L298N_IN4 25
#define L298N_IN5 15
#define L298N_IN6 4
#define L298N_IN7 16
#define L298N_IN8 17

//轉動時間(毫秒)
const int FTimer = 1000;
const int BTimer = 1000;
const int RTimer = 1000;
const int LTimer = 1000;
const int STimer = 3000;

void forward() {
  digitalWrite(L298N_IN1, HIGH);
  digitalWrite(L298N_IN2, LOW);
  digitalWrite(L298N_IN3, HIGH);
  digitalWrite(L298N_IN4, LOW);

  digitalWrite(L298N_IN5, HIGH);
  digitalWrite(L298N_IN6, LOW);
  digitalWrite(L298N_IN7, HIGH);
  digitalWrite(L298N_IN8, LOW);
}

void backward() {
  digitalWrite(L298N_IN1, LOW);
  digitalWrite(L298N_IN2, HIGH);
  digitalWrite(L298N_IN3, LOW);
  digitalWrite(L298N_IN4, HIGH);

  digitalWrite(L298N_IN5, LOW);
  digitalWrite(L298N_IN6, HIGH);
  digitalWrite(L298N_IN7, LOW);
  digitalWrite(L298N_IN8, HIGH);
}

void turnRight() {
  digitalWrite(L298N_IN1, HIGH);
  digitalWrite(L298N_IN2, LOW);
  digitalWrite(L298N_IN3, HIGH);
  digitalWrite(L298N_IN4, LOW);

  digitalWrite(L298N_IN5, LOW);
  digitalWrite(L298N_IN6, HIGH);
  digitalWrite(L298N_IN7, LOW);
  digitalWrite(L298N_IN8, HIGH);

}

void turnLeft() {
  digitalWrite(L298N_IN1, LOW);
  digitalWrite(L298N_IN2, HIGH);
  digitalWrite(L298N_IN3, LOW);
  digitalWrite(L298N_IN4, HIGH);

  digitalWrite(L298N_IN5, HIGH);
  digitalWrite(L298N_IN6, LOW);
  digitalWrite(L298N_IN7, HIGH);
  digitalWrite(L298N_IN8, LOW);
}

void stopCar() {
  digitalWrite(L298N_IN1, LOW);
  digitalWrite(L298N_IN2, LOW);
  digitalWrite(L298N_IN3, LOW);
  digitalWrite(L298N_IN4, LOW);

  digitalWrite(L298N_IN5, LOW);
  digitalWrite(L298N_IN6, LOW);
  digitalWrite(L298N_IN7, LOW);
  digitalWrite(L298N_IN8, LOW);
}

void setup() {
  Serial.begin(9600);

  pinMode(L298N_IN1, OUTPUT);
  pinMode(L298N_IN2, OUTPUT);
  pinMode(L298N_IN3, OUTPUT);
  pinMode(L298N_IN4, OUTPUT);
  pinMode(L298N_IN5, OUTPUT);
  pinMode(L298N_IN6, OUTPUT);
  pinMode(L298N_IN7, OUTPUT);
  pinMode(L298N_IN8, OUTPUT);

  stopCar();
  delay(2000);
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
