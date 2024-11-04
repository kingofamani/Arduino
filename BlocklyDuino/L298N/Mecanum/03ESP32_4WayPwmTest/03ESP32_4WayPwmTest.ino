#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

//L298N腳位
#define L298N_IN1 14
#define L298N_IN2 27
#define L298N_IN3 26
#define L298N_IN4 25
#define L298N_IN5 23
#define L298N_IN6 4
#define L298N_IN7 16
#define L298N_IN8 17

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
int FSpeed = 150;//150
int BSpeed = 150;//150
int RSpeed = 150;//150
int LSpeed = 150;//150

//轉動時間(毫秒)
int FTimer = 740;//740
int BTimer = 740;//740
int RTimer = 580;//580
int LTimer = 600;//600
int STimer = 3000;

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
  delay(10);
  SerialBT.begin("4CarTest");
  delay(10);

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
  //序列埠輸入
  if (Serial.available()) {
    String strMsg = Serial.readString();  //格式「方向,速度,時間」。例如 f,255,1000
    go(strMsg);
  }

  //藍牙輸入
  if (SerialBT.available()) {
    String btMsg = (SerialBT.readString());
    go(btMsg);
  }
}

void go(String str) {  
  //改成陣列
  int len = 50;
  String msgs[len];
  char *token = strtok((char *)str.c_str(), ",");

  msgs[0] = token;
  token = strtok(NULL, ",");
  msgs[1] = token;
  token = strtok(NULL, ",");
  msgs[2] = token;
  token = strtok(NULL, ",");

  String direct = msgs[0];
  int speed = msgs[1].toInt();
  int timer = msgs[2].toInt();
  Serial.println(direct);
  Serial.println(speed);
  Serial.println(timer);

  if (direct == "f") {
    FSpeed = speed;
    FTimer = timer;
    forward();
    delay(FTimer);
    stopCar();
  } else if (direct == "b") {
    BSpeed = speed;
    BTimer = timer;
    backward();
    delay(BTimer);
    stopCar();
  } else if (direct == "r") {
    RSpeed = speed;
    RTimer = timer;
    turnRight();
    delay(RTimer);
    stopCar();
  } else if (direct == "l") {
    LSpeed = speed;
    LTimer = timer;
    turnLeft();
    delay(LTimer);
    stopCar();
  } else if (direct == "def") {
    FSpeed = 255;
    BSpeed = 255;
    RSpeed = 150;
    LSpeed = 150;

    FTimer = 1000;
    BTimer = 1000;
    RTimer = 1000;
    LTimer = 1000;
    STimer = 3000;
    stopCar();
  }
}
