//L298N腳位
#define L298N_IN1 14
#define L298N_IN2 27
#define L298N_IN3 26
#define L298N_IN4 25
#define L298N_IN5 23
#define L298N_IN6 4
#define L298N_IN7 15
#define L298N_IN8 32

#define L298N_EN1 13//PWM
#define L298N_EN2 33//PWM
#define L298N_EN3 5 //PWM
#define L298N_EN4 19//PWM

//ESP32設定PWM Channel
const int EN1_CHL = 0;
const int EN2_CHL = 1;
const int EN3_CHL = 2;
const int EN4_CHL = 3;

//轉速(80~255)
const int FSpeed = 120;
const int BSpeed = 120;
const int RSpeed = 120;
const int LSpeed = 120;

//轉動時間(毫秒)
const int FTimer = 1000;
const int BTimer = 1000;
const int RTimer = 1000;
const int LTimer = 1000;
const int STimer = 3000;

//對角線前進右
void diagonalRight(){
  digitalWrite(L298N_IN1, HIGH);
  digitalWrite(L298N_IN2, LOW);
  ledcWrite(EN1_CHL, FSpeed);

  digitalWrite(L298N_IN3, LOW);
  digitalWrite(L298N_IN4, LOW);
  ledcWrite(EN2_CHL, FSpeed);

  digitalWrite(L298N_IN5, LOW);
  digitalWrite(L298N_IN6, LOW);
  ledcWrite(EN3_CHL, FSpeed);

  digitalWrite(L298N_IN7, HIGH);
  digitalWrite(L298N_IN8, LOW);
  ledcWrite(EN4_CHL, FSpeed);
}

//對角線前進左
void diagonalLeft(){
  digitalWrite(L298N_IN1, LOW);
  digitalWrite(L298N_IN2, LOW);
  ledcWrite(EN1_CHL, FSpeed);

  digitalWrite(L298N_IN3, HIGH);
  digitalWrite(L298N_IN4, LOW);
  ledcWrite(EN2_CHL, FSpeed);

  digitalWrite(L298N_IN5, HIGH);
  digitalWrite(L298N_IN6, LOW);
  ledcWrite(EN3_CHL, FSpeed);

  digitalWrite(L298N_IN7, LOW);
  digitalWrite(L298N_IN8, LOW);
  ledcWrite(EN4_CHL, FSpeed);
}

void forward() {
  digitalWrite(L298N_IN1, HIGH);
  digitalWrite(L298N_IN2, LOW);
  ledcWrite(EN1_CHL, FSpeed);

  digitalWrite(L298N_IN3, HIGH);
  digitalWrite(L298N_IN4, LOW);
  ledcWrite(EN2_CHL, FSpeed);

  digitalWrite(L298N_IN5, HIGH);
  digitalWrite(L298N_IN6, LOW);
  ledcWrite(EN3_CHL, FSpeed);

  digitalWrite(L298N_IN7, HIGH);
  digitalWrite(L298N_IN8, LOW);
  ledcWrite(EN4_CHL, FSpeed);
}

void backward() {
  digitalWrite(L298N_IN1, LOW);
  digitalWrite(L298N_IN2, HIGH);
  ledcWrite(EN1_CHL, BSpeed);

  digitalWrite(L298N_IN3, LOW);
  digitalWrite(L298N_IN4, HIGH);
  ledcWrite(EN2_CHL, BSpeed);

  digitalWrite(L298N_IN5, LOW);
  digitalWrite(L298N_IN6, HIGH);
  ledcWrite(EN3_CHL, BSpeed);

  digitalWrite(L298N_IN7, LOW);
  digitalWrite(L298N_IN8, HIGH);
  ledcWrite(EN4_CHL, BSpeed);
}

void turnRight() {
  digitalWrite(L298N_IN1, HIGH);
  digitalWrite(L298N_IN2, LOW);
  ledcWrite(EN1_CHL, RSpeed);

  digitalWrite(L298N_IN3, HIGH);
  digitalWrite(L298N_IN4, LOW);
  ledcWrite(EN2_CHL, RSpeed);

  digitalWrite(L298N_IN5, LOW);
  digitalWrite(L298N_IN6, HIGH);
  ledcWrite(EN3_CHL, RSpeed);

  digitalWrite(L298N_IN7, LOW);
  digitalWrite(L298N_IN8, HIGH);
  ledcWrite(EN4_CHL, RSpeed);  
}

void turnLeft() {
  digitalWrite(L298N_IN1, LOW);
  digitalWrite(L298N_IN2, HIGH);
  ledcWrite(EN1_CHL, LSpeed);

  digitalWrite(L298N_IN3, LOW);
  digitalWrite(L298N_IN4, HIGH);
  ledcWrite(EN2_CHL, LSpeed);


  digitalWrite(L298N_IN5, HIGH);
  digitalWrite(L298N_IN6, LOW);
  ledcWrite(EN3_CHL, LSpeed);

  digitalWrite(L298N_IN7, HIGH);
  digitalWrite(L298N_IN8, LOW);
  ledcWrite(EN4_CHL, LSpeed);
}

void stopCar() {
  digitalWrite(L298N_IN1, LOW);
  digitalWrite(L298N_IN2, LOW);
  ledcWrite(EN1_CHL, FSpeed);

  digitalWrite(L298N_IN3, LOW);
  digitalWrite(L298N_IN4, LOW);
  ledcWrite(EN2_CHL, FSpeed);

  digitalWrite(L298N_IN5, LOW);
  digitalWrite(L298N_IN6, LOW);
  ledcWrite(EN3_CHL, FSpeed);

  digitalWrite(L298N_IN7, LOW);
  digitalWrite(L298N_IN8, LOW);
  ledcWrite(EN4_CHL, FSpeed);
  
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
  pinMode(L298N_EN1, OUTPUT);
  pinMode(L298N_EN2, OUTPUT);
  pinMode(L298N_EN3, OUTPUT);
  pinMode(L298N_EN4, OUTPUT);

  digitalWrite(L298N_IN1, LOW);
  digitalWrite(L298N_IN2, LOW);
  digitalWrite(L298N_IN3, LOW);
  digitalWrite(L298N_IN4, LOW);
  digitalWrite(L298N_IN5, LOW);
  digitalWrite(L298N_IN6, LOW);
  digitalWrite(L298N_IN7, LOW);
  digitalWrite(L298N_IN8, LOW);
  digitalWrite(L298N_EN1, LOW);
  digitalWrite(L298N_EN2, LOW);
  digitalWrite(L298N_EN3, LOW);
  digitalWrite(L298N_EN4, LOW);

  //PWM設定
  ledcSetup(EN1_CHL, 1000, 8);//channel,frequence,resolution(8表示0~255)
  ledcAttachPin(L298N_EN1, EN1_CHL);
  ledcSetup(EN2_CHL, 1000, 8);
  ledcAttachPin(L298N_EN2, EN2_CHL);
  ledcSetup(EN3_CHL, 1000, 8);
  ledcAttachPin(L298N_EN3, EN3_CHL);
  ledcSetup(EN4_CHL, 1000, 8);
  ledcAttachPin(L298N_EN4, EN4_CHL);

  stopCar();
  delay(2000);
}

void loop() {
  diagonalRight();
  delay(FTimer);
  stopCar();
  delay(FTimer);

  diagonalLeft();
  delay(FTimer);
  stopCar();
  delay(FTimer);

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
