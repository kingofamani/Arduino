//右下角歸零(先手動將X軸推至最右邊)

#include <AccelStepper.h>
#include <Servo.h>
#include <SoftwareSerial.h>
//====插入變數Start====
// 定義電機控制用常數
const int enablePin = 8;  // 啟用控制引腳
const int xdirPin = 5;    // x方向控制引腳
const int xstepPin = 2;   // x步進控制引腳
const int ydirPin = 6;    // y方向控制引腳
const int ystepPin = 3;   // y步進控制引腳
// UART通訊
SoftwareSerial ESP32Serial(7, 4);
// 伺服馬達腳位(接在Z+是pin11)
const int servoPin = 11;
//====插入變數End====
// 伺服馬達
Servo servoPick;
const int xMoveSteps = 850;                  // 測試電機1運行使用的運行步數
const int yMoveSteps = 1050;                  // 測試電機2運行使用的運行步數
const int xInit = 280;                        // 初始第9格x位置(右下角0)
const int yInit = 0;                          // 初始第9格y位置(右下角0)
AccelStepper stepperX(1, xstepPin, xdirPin);  // 建立步進電機物件1
AccelStepper stepperY(1, ystepPin, ydirPin);  // 建立步進電機物件2
const char* GOODS_LOAD = "goodsLoad";

//是否已初始
bool isReset = false;

//貨物座標
int x = -1;
int y = -1;
//是否開始撿貨
bool isStartPick = false;

void setup() {
  Serial.begin(9600);
  // UART
  ESP32Serial.begin(9600);
  // 伺服馬達
  servoPick.attach(servoPin);
  servoPick.write(0);
  pinMode(xstepPin, OUTPUT);       // Arduino控制A4988x步進引腳為輸出模式
  pinMode(xdirPin, OUTPUT);        // Arduino控制A4988x方向引腳為輸出模式
  pinMode(ystepPin, OUTPUT);       // Arduino控制A4988y步進引腳為輸出模式
  pinMode(ydirPin, OUTPUT);        // Arduino控制A4988y方向引腳為輸出模式
  pinMode(enablePin, OUTPUT);      // Arduino控制A4988啟用引腳為輸出模式
  digitalWrite(enablePin, LOW);    // 將啟用控制引腳設置為低電平以使電機驅動板進入工作狀態
  stepperX.setMaxSpeed(300.0);     // 設置電機最大速度300
  stepperX.setAcceleration(20.0);  // 設置電機加速度20.0
  stepperY.setMaxSpeed(300.0);     // 設置電機最大速度300
  stepperY.setAcceleration(20.0);  // 設置電機加速度20.0

  delay(2000);

  //歸零
  //resetStepper();
}

void loop() {
  //歸零(先手動將X軸推至最右邊)
  //resetStepper();

  // int x = 1;
  // int y = 1;
  // findGoods(x, y);

  //testStepper();


  // // 接收訊息：ESP32→Arduino
  while (ESP32Serial.available()) {
    //取得貨物在倉庫xy座標
    String str = ESP32Serial.readString();// 格式xy(例如13)
    x = (int)(str.charAt(0) - '0');
    y = (int)(str.charAt(1) - '0');
    Serial.print(x);
    Serial.print(",");
    Serial.print(y);
    //CNC開始依座標找尋貨物
    if ((x >= 0 && x <= 2) && (y >= 0 && y <= 2)) {//★避免ESP32斷線時出現亂數
      //開始撿貨
      isStartPick = true;      
    }

    //findGoods(x, y);

    // 撿貨伺服馬達
    //servoPick.write(180);
    //delay(2000);
    // 撿貨伺服馬達
    //servoPick.write(0);
    //delay(2000);
    //歸零
    //resetStepper();
    
  }//end while

  if (!isStartPick) {
    stepperX.moveTo(0);
    stepperY.moveTo(0);
    stepperX.run();
    stepperY.run();
  }

  if (isStartPick) {
    findGoods(x, y);
  }
}

void findGoods(int x, int y) {
  //Serial.println("findGoods");
  //分成3*3格倉庫的xy步數
  int xSteps = xMoveSteps / 2;
  int ySteps = yMoveSteps / 2;
  //電機移動至該貨物格子
  int goodsX = xSteps * x + xInit;
  int goodsY = ySteps * y + yInit;
  
  stepperX.moveTo(goodsX);
  stepperY.moveTo(goodsY);
  stepperX.run();
  stepperY.run();

  // Serial.print(goodsX);
  // Serial.print(",");
  // Serial.print(goodsY);
  // Serial.print(",  ");
  // Serial.print(stepperX.currentPosition());
  // Serial.print(",");
  // Serial.print(stepperY.currentPosition());
  // Serial.println("");


  if (stepperX.currentPosition() == goodsX && stepperY.currentPosition() == goodsY) {
    servoPick.write(180);
    delay(2000);
    servoPick.write(0);
    delay(2000);

    //重設成未撿貨狀態
    isStartPick = false;

    // 完成撿貨通知ESP32
    ESP32Serial.print(GOODS_LOAD);

    // stepperX.moveTo(0);
    // stepperY.moveTo(0);
    // stepperX.run();
    // stepperY.run();
  }
}
void resetStepper() {
  //  if (stepperX.currentPosition() == 0) {
  //    stepperX.moveTo(280);  //第9格最右邊界
  //  }
  //  stepperX.run();

  // if (!isReset) {
  //   stepperX.moveTo(280);
  //   //stepperY.moveTo(0);
  //   stepperX.run();
  //   //stepperY.run();
  //   isReset = true;
  // }
}
void testStepper() {
  // 控制步進電機1往復運動
  if (stepperX.currentPosition() == 0) {
    stepperX.moveTo(xMoveSteps);
    servoPick.write(0);  // 伺服馬達轉0度
  } else if (stepperX.currentPosition() == xMoveSteps) {
    stepperX.moveTo(0);
    servoPick.write(90);  // 伺服馬達轉90度
  }
  // 控制步進電機2往復運動
  if (stepperY.currentPosition() == 0) {
    stepperY.moveTo(yMoveSteps);
  } else if (stepperY.currentPosition() == yMoveSteps) {
    stepperY.moveTo(0);
  }
  //stepperX.run();  // 1號電機運行
  stepperY.run();  // 2號電機運行
}
