//右下角歸零(先手動將X軸推至最右邊)

#include <AccelStepper.h>
#include <Servo.h>
#include <SoftwareSerial.h>
//====插入變數Start====
// 定義電機控制用常數
const int enablePin = 8;  // 啟用控制引腳
const int xdirPin = 5;    // x方向控制引腳
const int xstepPin = 2;   // x步進控制引腳
// UART通訊
SoftwareSerial ESP32Serial(7, 4);
// 伺服馬達腳位(接在Z+是pin11)
const int servoPin = 11;
//====插入變數End====
// 伺服馬達
Servo servoPick;
const int xMoveSteps = 1500;                  // 測試電機1運行使用的運行步數
const int xInit = 0;                        // 初始第9格x位置(右下角0)
AccelStepper stepperX(1, xstepPin, xdirPin);  // 建立步進電機物件1
const char* GOODS_LOAD = "goodsLoad";

void setup() {
  Serial.begin(9600);
  // UART
  //ESP32Serial.begin(9600);
  pinMode(xstepPin, OUTPUT);       // Arduino控制A4988x步進引腳為輸出模式
  pinMode(xdirPin, OUTPUT);        // Arduino控制A4988x方向引腳為輸出模式
  pinMode(enablePin, OUTPUT);      // Arduino控制A4988啟用引腳為輸出模式
  digitalWrite(enablePin, LOW);    // 將啟用控制引腳設置為低電平以使電機驅動板進入工作狀態
  stepperX.setMaxSpeed(300.0);     // 設置電機最大速度300
  stepperX.setAcceleration(20.0);  // 設置電機加速度20.0
  delay(2000);

  

}

void loop() {
  //歸零(先手動將X軸推至最右邊)

  //測試
  //testStepper();
  //goToCamPosition(600);
  goToCamPosition(1320);

  //接收訊息：ESP32→Arduino
  // while (ESP32Serial.available()) {
  //   //取得貨物在倉庫xy座標
  //   String str = ESP32Serial.readString();  // 格式xy(例如13)
  //   int x = (int)(str.charAt(0) - '0');
  //   int y = (int)(str.charAt(1) - '0');
  //   //CNC開始依座標找尋貨物
  //   findGoods(x, y);
  //   // 撿貨伺服馬達
  //   servoPick.write(180);
  //   delay(2000);
  //   // 撿貨伺服馬達
  //   servoPick.write(0);
  //   delay(2000);
  //   //歸零
  //   resetStepper();
  //   // 完成撿貨通知ESP32
  //   ESP32Serial.print(GOODS_LOAD);
  // }  //end while

}

void goToCamPosition(int x) {
  stepperX.moveTo(x);
  Serial.println(stepperX.currentPosition());
  stepperX.run();
}
void resetStepper() {
  stepperX.moveTo(0);
  Serial.println(stepperX.currentPosition());
  stepperX.run();
}
void testStepper() {
  // 控制步進電機1往復運動
  if (stepperX.currentPosition() == 0) {
    stepperX.moveTo(xMoveSteps);    
  } else if (stepperX.currentPosition() == xMoveSteps) {
    stepperX.moveTo(0);
  }
  Serial.println(stepperX.currentPosition());
  
  stepperX.run();  // 1號電機運行
}
