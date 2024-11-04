#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

//L298N腳位
#define L298N_IN1 14
#define L298N_IN2 27
#define L298N_IN3 16
#define L298N_IN4 17
#define L298N_ENA 13  //PWM
#define L298N_ENB 15  //PWM

//ESP32設定PWM Channel
const int ENA_CHL = 0;
const int ENB_CHL = 1;

//轉速(80~255)
int FSpeed = 255;//255
int BSpeed = 255;//255
int RSpeed = 200;//200
int LSpeed = 200;//200

//轉動時間(毫秒)
int FTimer = 670; //670
int BTimer = 670; //670
int RTimer = 1350;//1350
int LTimer = 1650;//1650
int STimer = 3000;//3000

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
  delay(10);
  SerialBT.begin("CarTest");
  delay(10);

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
  ledcSetup(ENA_CHL, 1000, 8);  //channel,frequence,resolution(8表示0~255)
  ledcAttachPin(L298N_ENA, ENA_CHL);
  ledcSetup(ENB_CHL, 1000, 8);
  ledcAttachPin(L298N_ENB, ENB_CHL);

  stopCar();
  delay(500);
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
