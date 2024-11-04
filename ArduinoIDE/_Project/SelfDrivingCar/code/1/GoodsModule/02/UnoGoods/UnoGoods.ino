#include <AccelStepper.h> 
#include <Servo.h>
#include <SoftwareSerial.h>

//====插入變數Start====
// 定義電機控制用常數
const int enablePin = 8;  // 啟用控制引腳
const int xdirPin = 5;     // x方向控制引腳
const int xstepPin = 2;    // x步進控制引腳
const int ydirPin = 6;     // y方向控制引腳
const int ystepPin = 3;    // y步進控制引腳

// UART通訊
SoftwareSerial ESP32Serial(7, 4);//(接在Z.DIR、Z.STEP)

// 伺服馬達腳位（接在Z+是pin11）
const int servoPin = 11;   
//====插入變數End====

// 伺服馬達
Servo servoPick;

const int xMoveSteps = 500;    // 測試電機1運行使用的運行步數
const int yMoveSteps = 500;    // 測試電機2運行使用的運行步數

AccelStepper stepper1(1, xstepPin, xdirPin); // 建立步進電機物件1
AccelStepper stepper2(1, ystepPin, ydirPin); // 建立步進電機物件2

const char* GOODS_LOAD = "goodsLoad";

void setup() {	
  Serial.begin(9600);
  // UART
  ESP32Serial.begin(9600);

  // 伺服馬達
  servoPick.attach(servoPin);
  servoPick.write(0);

  pinMode(xstepPin, OUTPUT);    // Arduino控制A4988x步進引腳為輸出模式
  pinMode(xdirPin, OUTPUT);     // Arduino控制A4988x方向引腳為輸出模式
  pinMode(ystepPin, OUTPUT);    // Arduino控制A4988y步進引腳為輸出模式
  pinMode(ydirPin, OUTPUT);     // Arduino控制A4988y方向引腳為輸出模式

  pinMode(enablePin, OUTPUT);  // Arduino控制A4988啟用引腳為輸出模式
  digitalWrite(enablePin, LOW); // 將啟用控制引腳設置為低電平以使電機驅動板進入工作狀態

  stepper1.setMaxSpeed(300.0);     // 設置電機最大速度300
  stepper1.setAcceleration(20.0);  // 設置電機加速度20.0
  stepper2.setMaxSpeed(300.0);     // 設置電機最大速度300
  stepper2.setAcceleration(20.0);  // 設置電機加速度20.0
  
  //歸零
  resetStepper();
}

void loop() {
  // 接收訊息：ESP32→Arduino
  while (ESP32Serial.available()) {
	//取得貨物在倉庫xy座標
    String str = ESP32Serial.readString();// 格式xy(例如13)
	int x = (int)(str.charAt(0) - '0');
	int y = (int)(str.charAt(1) - '0');
	
    //CNC開始依座標找尋貨物
	findGoods(x,y);
	
	// 撿貨伺服馬達
	servoPick.write(180);
	delay(2000);
	servoPick.write(0);
	delay(2000);
	
	//歸零
	resetStepper();
	
	// 完成撿貨通知ESP32
	ESP32Serial.print(GOODS_LOAD);	
  }//end while
  
}// end loop

void findGoods(int x,int y){
	//分成3*3格倉庫的xy步數
	int xSteps=xMoveSteps/2;
	int ySteps=yMoveSteps/2;	
	//電機移動至該貨物格子
	stepper1.moveTo(xSteps*x);
	stepper2.moveTo(ySteps*y);
}

void resetStepper(){
	stepper1.moveTo(0);
	stepper2.moveTo(0);
}

void testStepper(){
	// 控制步進電機1往復運動
  if ( stepper1.currentPosition() == 0 ) {
    stepper1.moveTo(xMoveSteps);
    servoPick.write(0);// 伺服馬達轉0度
  } else if ( stepper1.currentPosition() == xMoveSteps  ) {
    stepper1.moveTo(0);
    servoPick.write(90);// 伺服馬達轉90度
  }

  // 控制步進電機2往復運動
  if ( stepper2.currentPosition() == 0 ) {
    stepper2.moveTo(yMoveSteps);
  } else if ( stepper2.currentPosition() == yMoveSteps  ) {
    stepper2.moveTo(0);
  }

  stepper1.run();   // 1號電機運行
  stepper2.run();   // 2號電機運行
}
