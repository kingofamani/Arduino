//左邊歸零(先手動將X軸推至最左邊)

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
//測試CAM開始拍照按鈕
const int btnCamTestPin = 6;
const int TRASH_POSITION = 600;//垃圾桶x座標
const int PLANT_POSITION = 1320;//植物x座標
bool isTestTrashCam = false;//是否測試鏡頭移動至垃圾桶前
bool isTestPlantCam = false;//是否測試鏡頭移動至植物前
bool isMoveTrashCam = false;//是否鏡頭移動至垃圾桶前
bool isMovePlantCam = false;//是否鏡頭移動至植物前

//馬達歸零(接在Z+是pin11)
const int btnResetPin = 11;

//====插入變數End====
// 伺服馬達
Servo servoPick;
const int xMoveSteps = 1500;                  // 測試電機1運行使用的運行步數
const int xInit = 0;                        // 初始第9格x位置(右下角0)
AccelStepper stepperX(1, xstepPin, xdirPin);  // 建立步進電機物件1

void setup() {
  ESP32Serial.begin(9600);
  delay(10);
  Serial.begin(9600);

  //測試拍照鈕
  pinMode(btnCamTestPin, INPUT);
  pinMode(btnResetPin, INPUT);

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

  //goToTrashPosition(600);
  //goToPlantPosition(1320);

  //歸零按鈕
  if (digitalRead(btnResetPin) == 1) {
    resetStepper();
  }

  //按鈕模擬自動拍照
  if (digitalRead(btnCamTestPin) == 1) {
    isTestTrashCam = true;
  }
  //按鈕模擬垃圾桶測試拍照
  if (isTestTrashCam) {
    testTrashCam();
  }
  //按鈕模擬植物測試拍照
  if (isTestPlantCam) {
    testPlantCam();
  }

  //垃圾桶拍照
  if (isMoveTrashCam) {
    startTrashCam();
  }
  //植物拍照
  if (isMovePlantCam) {
    startPlantCam();
  }



  //當每日時間到的時候自動拍照
  //接收訊息：ESP32→Arduino
  while (ESP32Serial.available()) {
    //接收stand by準備拍照訊息，開始移動鏡頭
    //訊息內容:STANDBY_TRASH_CAM,STANDBY_PLANT_CAM
    String standby = ESP32Serial.readString();
    Serial.println(standby);
    if (standby == "STANDBY_TRASH_CAM") {
      isMoveTrashCam = true;
      //startMoveAndCam("START_TRASH_CAM",TRASH_POSITION);
    } else if (standby == "STANDBY_PLANT_CAM") {
      isMovePlantCam = true;
      //startMoveAndCam("START_PLANT_CAM",PLANT_POSITION);
    }

    delay(2000);
    //歸零
    //resetStepper();
  }  //end while

}//end loop

//void goToTrashPosition(int x) {
//  stepperX.moveTo(x);
//  stepperX.run();
//  if (stepperX.currentPosition() != x) {
//    Serial.println(stepperX.currentPosition());
//  } else {
//    //發送UART給ESP32
//    ESP32Serial.print("START_TRASH_CAM");
//    Serial.println("UNO→ESP32:START_TRASH_CAM");
//  }
//}

//void startMoveAndCam(String camCommand,int postion) {
//  //開始移動鏡頭
//  stepperX.moveTo(postion);
//  stepperX.run();
//  if (stepperX.currentPosition() != postion) {
//    Serial.println(stepperX.currentPosition());
//  } else {
//    delay(5000);//等待鏡頭穩定不動再拍照
//    //發送UART給ESP32
//    ESP32Serial.print(camCommand);
//    Serial.println("UNO→ESP32:" + camCommand);
//    delay(3000);//等待鏡頭拍照
//  }
//}

void resetStepper() {
  stepperX.moveTo(0);
  stepperX.run();
  if (stepperX.currentPosition() != 0) {
    Serial.println(stepperX.currentPosition());
  }
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

void startTrashCam() {
  stepperX.moveTo(TRASH_POSITION);
  stepperX.run();
  if (stepperX.currentPosition() != TRASH_POSITION) {
    Serial.println(stepperX.currentPosition());
  } else {
    delay(5000);//等待鏡頭穩定不動再拍照
    //發送UART給ESP32
    ESP32Serial.print("START_TRASH_CAM");
    Serial.println("UNO→ESP32:START_TRASH_CAM");
    isMoveTrashCam = false;
    delay(3000);//等待鏡頭拍照
  }
}

void startPlantCam() {
  stepperX.moveTo(PLANT_POSITION);
  stepperX.run();
  if (stepperX.currentPosition() != PLANT_POSITION) {
    Serial.println(stepperX.currentPosition());
  } else {
    delay(5000);//等待鏡頭穩定不動再拍照
    //發送UART給ESP32
    ESP32Serial.print("START_PLANT_CAM");
    Serial.println("UNO→ESP32:START_PLANT_CAM");
    isMovePlantCam = false;
    delay(3000);//等待鏡頭拍照
  }
}

void testTrashCam() {
  stepperX.moveTo(TRASH_POSITION);
  stepperX.run();
  if (stepperX.currentPosition() != TRASH_POSITION) {
    Serial.println(stepperX.currentPosition());
  } else {
    delay(5000);//等待鏡頭穩定不動再拍照
    //發送UART給ESP32
    ESP32Serial.print("START_TRASH_CAM");
    Serial.println("UNO→ESP32:START_TRASH_CAM");
    //結束垃圾桶拍照，換植物拍照
    isTestTrashCam = false;
    isTestPlantCam = true;
    delay(3000);//等待鏡頭拍照
  }
}

void testPlantCam() {
  stepperX.moveTo(PLANT_POSITION);
  stepperX.run();
  if (stepperX.currentPosition() != PLANT_POSITION) {
    Serial.println(stepperX.currentPosition());
  } else {
    delay(5000);//等待鏡頭穩定不動再拍照
    //發送UART給ESP32
    ESP32Serial.print("START_PLANT_CAM");
    Serial.println("UNO→ESP32:START_PLANT_CAM");
    //結束拍照
    isTestTrashCam = false;
    isTestPlantCam = false;
    delay(3000);//等待鏡頭拍照
  }
}
