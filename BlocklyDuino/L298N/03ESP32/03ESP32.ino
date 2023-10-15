//L298N腳位
#define L298N_IN1 14
#define L298N_IN2 27
#define L298N_IN3 16
#define L298N_IN4 17
#define L298N_ENA 13//PWM
#define L298N_ENB 15//PWM

//ESP32設定PWM Channel
const int ENA_CHL = 0;
const int ENB_CHL = 1;

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
  ledcWrite(ENA_CHL, FSpeed);

  digitalWrite(L298N_IN3, LOW);
  digitalWrite(L298N_IN4, HIGH);
  ledcWrite(ENB_CHL, FSpeed);
}

void backward() {
  digitalWrite(L298N_IN1, LOW);
  digitalWrite(L298N_IN2, HIGH);
  ledcWrite(ENA_CHL, BSpeed);

  digitalWrite(L298N_IN3, HIGH);
  digitalWrite(L298N_IN4, LOW);
  ledcWrite(ENB_CHL, BSpeed);
}

void turnRight() {
  digitalWrite(L298N_IN1, LOW);
  digitalWrite(L298N_IN2, HIGH);
  ledcWrite(ENA_CHL, LSpeed);

  digitalWrite(L298N_IN3, LOW);
  digitalWrite(L298N_IN4, HIGH);
  ledcWrite(ENB_CHL, LSpeed);
}

void turnLeft() {
  digitalWrite(L298N_IN1, HIGH);
  digitalWrite(L298N_IN2, LOW);
  ledcWrite(ENA_CHL, RSpeed);

  digitalWrite(L298N_IN3, HIGH);
  digitalWrite(L298N_IN4, LOW);
  ledcWrite(ENB_CHL, RSpeed);
}

void stopCar() {
  digitalWrite(L298N_IN1, LOW);
  digitalWrite(L298N_IN2, LOW);
  ledcWrite(ENA_CHL, FSpeed);

  digitalWrite(L298N_IN3, LOW);
  digitalWrite(L298N_IN4, LOW);
  ledcWrite(ENB_CHL, BSpeed);
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

  //PWM設定
  ledcSetup(ENA_CHL, 1000, 8);//channel,frequence,resolution(8表示0~255)
  ledcAttachPin(L298N_ENA, ENA_CHL);
  ledcSetup(ENB_CHL, 1000, 8);
  ledcAttachPin(L298N_ENB, ENB_CHL);
  

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
