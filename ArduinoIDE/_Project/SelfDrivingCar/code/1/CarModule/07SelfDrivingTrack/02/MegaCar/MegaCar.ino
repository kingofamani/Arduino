#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include "HUSKYLENS.h"
#include <Wire.h>
#include <Adafruit_INA219.h>

//★★★車頭初始向下
char CAR_INIT_DIRECT = 'D';

// 定義地圖大小
const int numRows = 4;
const int numCols = 6;

//地圖陣列，0表示障礙物，1表示可通行
int grid[numRows][numCols];
//位置
const char* GOODS_POINT = "goodsStation";
const char* CHARGE_POINT = "chargeStation";
const char* Recipient_POINT = "recipientHome";

//目前位置
String currentPoint = GOODS_POINT;
//起點位置
String startPoint = GOODS_POINT;
int startRow = 0;
int startCol = 0;
//終點位置
String endPoint = Recipient_POINT;
int endRow = 3;
int endCol = 5;

//儲存座標結果
String pathXY[numRows * numCols];
//int pathXYCount = 0;

//儲存地圖方向結果URDL
char pathMapDirect[numRows * numCols];
char MAP_DIRECT[4] = { 'U', 'R', 'D', 'L' };
int pathCount = 0;

//儲存車子(順時針)轉動角度
int pathCarDegree[numRows * numCols];

//儲存車子移動方向
char* pathCarMove[numRows * numCols];
char* CAR_MOVE[4] = { "F,", "R,F,", "R,R,F,", "L,F," };

//====UART通訊(接收ESP32傳來的MQTT訊息) start====
SoftwareSerial ESP32Serial(19, 18);

//與Esp32通訊
const char* MAP_SET = "mapSet";
const char* GOODS_LOAD = "goodsLoad";
const char* LINE_NOTIFY = "lineNotify";
const char* CAR_GPS = "carGps";

//收貨人
String recipient[6];
//====UART end====

//======循跡感測器 Start======
#define TRACK_LEFT_PIN 30   //左邊 id1
#define TRACK_FRONT_PIN 31  //前面 id2
#define TRACK_BACK_PIN 32   //後面 id3
#define TRACK_RIGHT_PIN 33  //右邊 id4

//4way循跡感測器陣列
int trackSensor[4];
#define TRACK_LEFT 0
#define TRACK_FRONT 1
#define TRACK_BACK 2
#define TRACK_RIGHT 3

//是否走完一格
bool isFrontArrive = false;
//觸發到白線回傳0或1
#define TRIGGLED 1

//loop只執行一次
//bool loopHasRun = false;

//======循跡感測器 End======

//伺服馬達
#define SERVO_CAR_BOX_PIN 34
#define SERVO_AI_CAM_PIN 35

//伺服馬旋轉角度
#define ANGLE_CAR_BOX_OPEN 90  //開啟貨斗
#define ANGLE_CAR_BOX_CLOSE 0  //關閉貨斗
#define ANGLE_AI_CAM_FRONT 90  //鏡頭向前
#define ANGLE_AI_CAM_UP 45     //鏡頭朝上

Servo servoCarBox;
Servo servoAiCam;

//HsukyLens AI鏡頭
HUSKYLENS huskylens;
int readData[5] = {};
byte dataType = 0;
byte idCount = 0;
bool detection_now = 0;

int aiId = 0;
int aiX = 0;  //中心點X座標
int aiY = 0;  //中心點Y座標
int aiWidth = 0;
int aiHeight = 0;
const int PERSON_ID = 1;                             //物體識別模式:人(透過AI鏡頭訓練)
const int CAR_ID = 2;                                //物體識別模式:車子(透過AI鏡頭訓練)
const int FACE_ID1 = 1;                              //人臉識別模式:車子(透過AI鏡頭訓練)
char* CurrentAlgo = "ALGORITHM_OBJECT_RECOGNITION";  //目前的演算法

//簽收鈕
#define BUTTON_SIGN_PIN 36

//測電壓電流
Adafruit_INA219 ina219;
float busvoltage = 0;  //電池電壓
float shuntvoltage = 0;
float loadvoltage = 0;  //負載電壓
float current_mA = 0;   //負載電流
float power_mW = 0;     //負載功率

//===========實體小車和馬達 Start===========
//L298N腳位
#define L298N_IN1 22  
#define L298N_IN2 23  
#define L298N_IN3 24  
#define L298N_IN4 25  
#define L298N_IN5 26  
#define L298N_IN6 27  
#define L298N_IN7 28  
#define L298N_IN8 29  

#define L298N_EN1 2  //PWM
#define L298N_EN2 3  
#define L298N_EN3 4  
#define L298N_EN4 5  

//轉速(120~255)
const int FSpeed = 120;
const int BSpeed = 120;
const int RSpeed = 120;
const int LSpeed = 120;

//轉動時間(毫秒)
const int FTimer = 2000;
const int BTimer = 1000;
const int RTimer = 1000;
const int LTimer = 1000;
const int STimer = 3000;

void trackForward() {
  //先往前300ms,越過前方白線
  forward();
  delay(300);
  //開始前進,直循跡感測踫到前方白線
  while (!isFrontArrive) {
    //取得循跡感測值
    getTracks();

    //是否完成1格
    if (trackSensor[TRACK_FRONT] == TRIGGLED) {
      backward();
      delay(50);
      stopCar();
      //結束此格行走
      isFrontArrive = true;
      break;
    }

    //開始判斷偏左、偏右、跑完一格
    if (trackSensor[TRACK_LEFT] == TRIGGLED && trackSensor[TRACK_RIGHT] != TRIGGLED) {
      //Serial.print(">");
      diagonalRight();
      //stopCar();
    } else if (trackSensor[TRACK_LEFT] != TRIGGLED && trackSensor[TRACK_RIGHT] == TRIGGLED) {
      //Serial.print("<");
      diagonalLeft();
      //stopCar();
    } else {
      forward();
      //Serial.print("-");
      //stopCar();
    }
    //delay(trackTimer);


  }  //end while
}

void diagonalRight() {
  digitalWrite(L298N_IN1, HIGH);
  digitalWrite(L298N_IN2, LOW);
  analogWrite(L298N_EN1, FSpeed);

  digitalWrite(L298N_IN3, LOW);
  digitalWrite(L298N_IN4, LOW);
  analogWrite(L298N_EN2, FSpeed);

  digitalWrite(L298N_IN5, LOW);
  digitalWrite(L298N_IN6, LOW);
  analogWrite(L298N_EN3, FSpeed);

  digitalWrite(L298N_IN7, HIGH);
  digitalWrite(L298N_IN8, LOW);
  analogWrite(L298N_EN4, FSpeed);
}

void diagonalLeft() {
  digitalWrite(L298N_IN1, LOW);
  digitalWrite(L298N_IN2, LOW);
  analogWrite(L298N_EN1, FSpeed);

  digitalWrite(L298N_IN3, HIGH);
  digitalWrite(L298N_IN4, LOW);
  analogWrite(L298N_EN2, FSpeed);

  digitalWrite(L298N_IN5, HIGH);
  digitalWrite(L298N_IN6, LOW);
  analogWrite(L298N_EN3, FSpeed);

  digitalWrite(L298N_IN7, LOW);
  digitalWrite(L298N_IN8, LOW);
  analogWrite(L298N_EN4, FSpeed);
}

void forward() {
  digitalWrite(L298N_IN1, HIGH);
  digitalWrite(L298N_IN2, LOW);
  analogWrite(L298N_EN1, FSpeed);

  digitalWrite(L298N_IN3, HIGH);
  digitalWrite(L298N_IN4, LOW);
  analogWrite(L298N_EN2, FSpeed);

  digitalWrite(L298N_IN5, HIGH);
  digitalWrite(L298N_IN6, LOW);
  analogWrite(L298N_EN3, FSpeed);

  digitalWrite(L298N_IN7, HIGH);
  digitalWrite(L298N_IN8, LOW);
  analogWrite(L298N_EN4, FSpeed);
}

void backward() {
  digitalWrite(L298N_IN1, LOW);
  digitalWrite(L298N_IN2, HIGH);
  analogWrite(L298N_EN1, BSpeed);

  digitalWrite(L298N_IN3, LOW);
  digitalWrite(L298N_IN4, HIGH);
  analogWrite(L298N_EN2, BSpeed);

  digitalWrite(L298N_IN5, LOW);
  digitalWrite(L298N_IN6, HIGH);
  analogWrite(L298N_EN3, BSpeed);

  digitalWrite(L298N_IN7, LOW);
  digitalWrite(L298N_IN8, HIGH);
  analogWrite(L298N_EN4, BSpeed);
}

void turnRight() {
  digitalWrite(L298N_IN1, HIGH);
  digitalWrite(L298N_IN2, LOW);
  analogWrite(L298N_EN1, RSpeed);

  digitalWrite(L298N_IN3, HIGH);
  digitalWrite(L298N_IN4, LOW);
  analogWrite(L298N_EN2, RSpeed);

  digitalWrite(L298N_IN5, LOW);
  digitalWrite(L298N_IN6, HIGH);
  analogWrite(L298N_EN3, RSpeed);

  digitalWrite(L298N_IN7, LOW);
  digitalWrite(L298N_IN8, HIGH);
  analogWrite(L298N_EN4, RSpeed);
}

void turnLeft() {
  digitalWrite(L298N_IN1, LOW);
  digitalWrite(L298N_IN2, HIGH);
  analogWrite(L298N_EN1, LSpeed);

  digitalWrite(L298N_IN3, LOW);
  digitalWrite(L298N_IN4, HIGH);
  analogWrite(L298N_EN2, LSpeed);


  digitalWrite(L298N_IN5, HIGH);
  digitalWrite(L298N_IN6, LOW);
  analogWrite(L298N_EN3, LSpeed);

  digitalWrite(L298N_IN7, HIGH);
  digitalWrite(L298N_IN8, LOW);
  analogWrite(L298N_EN4, LSpeed);
}

void stopCar() {
  digitalWrite(L298N_IN1, LOW);
  digitalWrite(L298N_IN2, LOW);
  analogWrite(L298N_EN1, FSpeed);

  digitalWrite(L298N_IN3, LOW);
  digitalWrite(L298N_IN4, LOW);
  analogWrite(L298N_EN2, FSpeed);

  digitalWrite(L298N_IN5, LOW);
  digitalWrite(L298N_IN6, LOW);
  analogWrite(L298N_EN3, FSpeed);

  digitalWrite(L298N_IN7, LOW);
  digitalWrite(L298N_IN8, LOW);
  analogWrite(L298N_EN4, FSpeed);
}

void goCar() {
  //1.先將移動指令轉成字串
  String stringPathCarMotor = "";
  for (int i = 0; i < pathCount; i++) {
    stringPathCarMotor += pathCarMove[i];
  }

  //2.字串轉成陣列
  //使用 strtok() 函数分割字符串
  int cacheLength = 200;  //太小會裝不下
  String pathCarMotor[cacheLength];
  char* token = strtok((char*)stringPathCarMotor.c_str(), ",");
  int tokenLen = 0;
  //字串轉成陣列
  while (token != NULL && tokenLen < cacheLength) {
    pathCarMotor[tokenLen] = token;
    token = strtok(NULL, ",");
    tokenLen++;
  }

  //3.開始移動車子
  int countPathXY = 1;
  for (int i = 0; i < tokenLen; i++) {
    if (pathCarMotor[i] == "F") {
      //AI識別行人,車子
      AiDetect();
      //循跡感測
      trackForward();
      isFrontArrive = false;
      delay(FTimer);
      //雲端平台模擬GPS
      ESP32Serial.print(String(CAR_GPS) + "," + pathXY[countPathXY++]);

      Serial.println("前,");
    } else if (pathCarMotor[i] == "R") {
      turnRight();
      delay(RTimer);
      stopCar();
      delay(RTimer);
      Serial.println("右轉,");
    } else if (pathCarMotor[i] == "L") {
      turnLeft();
      delay(LTimer);
      stopCar();
      delay(LTimer);
      Serial.println("左轉,");
    }
  }
}

//===========實體小車和馬達 End===========

//取得循跡感測器值
void getTracks() {
  //格式：左前後右(ex:0101)
  trackSensor[TRACK_LEFT] = digitalRead(TRACK_LEFT_PIN);
  trackSensor[TRACK_FRONT] = digitalRead(TRACK_FRONT_PIN);
  trackSensor[TRACK_BACK] = digitalRead(TRACK_BACK_PIN);
  trackSensor[TRACK_RIGHT] = digitalRead(TRACK_RIGHT_PIN);

  // for (int i = 0; i < 4; i++) {
  //   Serial.print(trackSensor[i]);
  // }
}

//===========HsukyLens AI鏡頭Start===========
void AiDetect() {
  bool isDetectPerson = false;
  bool isDetectCar = false;
  //直到沒有偵側到人or車才離開迴圈
  do {
    //開始AI識別物體
    startDetectObject();

    //在範圍內偵測到人,車才算
    if ((aiX >= 100 && aiX <= 220) && (aiY >= 60 && aiY <= 180)) {
      if (aiId == PERSON_ID) {
        isDetectPerson = true;
        Serial.println("人");
      } else if (aiId == CAR_ID) {
        isDetectCar = true;
        Serial.println("車");
      }
    }
    delay(500);
  } while (isDetectPerson || isDetectCar);
}


void startDetectObject() {
  if (!huskylens.request()) {
    Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
  } else {
    if (huskylens.available()) {
      detection_now = true;
      HUSKYLENSResult result = huskylens.read();
      idCount = huskylens.countLearned();
      if (result.command == COMMAND_RETURN_BLOCK) {
        dataType = 0;
        readData[0] = result.xCenter;
        readData[1] = result.yCenter;
        readData[2] = result.width;
        readData[3] = result.height;
        readData[4] = result.ID;
      } else if (result.command == COMMAND_RETURN_ARROW) {
        dataType = 1;
        readData[0] = result.xOrigin;
        readData[1] = result.yOrigin;
        readData[2] = result.xTarget;
        readData[3] = result.yTarget;
        readData[4] = result.ID;
      } else {
        for (byte i = 0; i < 5; i++) {
          readData[i] = 0;
        }
      }
    } else {
      detection_now = false;
    }
  }
  if (detection_now) {
    aiId = readData[4];
    aiX = readData[0];
    aiY = readData[1];
    aiWidth = readData[2];
    aiHeight = readData[3];

    //id=0表示有辨識到物體，但該物體沒有被學習
    if (aiId > 0) {
      Serial.print(aiId);
      // Serial.print(',');
      // Serial.print(aiX);
      // Serial.print(',');
      // Serial.print(aiY);
      // Serial.print(',');
      // Serial.print(aiWidth);
      // Serial.print(',');
      // Serial.println(aiHeight);
    }
  } else {
    aiId = 0;
    aiX = 0;
    aiY = 0;
    aiWidth = 0;
    aiHeight = 0;
    //Serial.println("null");
  }
}

//===========HsukyLens AI鏡頭End===========

// 表示地圖上的節點的類別
class Node {
public:
  int row;
  int col;
  int f;  // f = g + h，表示節點的總代價
  int g;  // 從起點到當前節點的實際代價
  int h;  // 從當前節點到目標節點的估算代價
  Node* parent;

  Node(int r, int c)
    : row(r), col(c), f(0), g(0), h(0), parent(nullptr) {}

  // 計算當前節點到目標節點的估算代價（這裡使用曼哈頓距離）
  void calculateH(int targetRow, int targetCol) {
    h = abs(targetRow - row) + abs(targetCol - col);
  }
};

// A*演算法
bool aStar(int grid[numRows][numCols], int startRow, int startCol, int endRow, int endCol) {
  Node* openList[numRows * numCols];
  Node* closedList[numRows * numCols];
  int openListCount = 0;
  int closedListCount = 0;

  Node* startNode = new Node(startRow, startCol);
  Node* endNode = new Node(endRow, endCol);

  startNode->calculateH(endRow, endCol);
  startNode->f = startNode->g + startNode->h;

  openList[openListCount++] = startNode;

  while (openListCount > 0) {
    // 找到f值最小的節點
    int minFIndex = 0;
    for (int i = 1; i < openListCount; i++) {
      if (openList[i]->f < openList[minFIndex]->f) {
        minFIndex = i;
      }
    }

    Node* currentNode = openList[minFIndex];

    // 將當前節點移到關閉列表
    for (int i = minFIndex; i < openListCount - 1; i++) {
      openList[i] = openList[i + 1];
    }
    openListCount--;
    closedList[closedListCount++] = currentNode;

    // 如果當前節點是目標節點，找到路徑並返回
    if (currentNode->row == endRow && currentNode->col == endCol) {
      Node* current = currentNode;
      while (current->parent != nullptr) {
        pathXY[pathCount] = String(current->row) + "," + String(current->col);

        int deltaX = current->col - current->parent->col;
        int deltaY = current->row - current->parent->row;

        if (deltaX == 1) {
          //Serial.print("右");
          pathMapDirect[pathCount++] = 'R';
        } else if (deltaX == -1) {
          //Serial.print("左");
          pathMapDirect[pathCount++] = 'L';
        } else if (deltaY == 1) {
          //Serial.print("下");
          pathMapDirect[pathCount++] = 'D';
        } else if (deltaY == -1) {
          //Serial.print("上");
          pathMapDirect[pathCount++] = 'U';
        }

        current = current->parent;
      }

      return true;
    }

    // 獲取當前節點的相鄰節點
    int neighbors[4][2] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };

    for (int i = 0; i < 4; i++) {
      int newRow = currentNode->row + neighbors[i][0];
      int newCol = currentNode->col + neighbors[i][1];

      // 檢查新節點是否在地圖範圍內
      if (newRow >= 0 && newRow < numRows && newCol >= 0 && newCol < numCols) {
        // 檢查新節點是否是障礙物
        if (grid[newRow][newCol] == 0) {
          continue;
        }

        Node* neighbor = new Node(newRow, newCol);
        neighbor->calculateH(endRow, endCol);
        neighbor->g = currentNode->g + 1;  // 假設每個步驟的代價都是1
        neighbor->f = neighbor->g + neighbor->h;
        neighbor->parent = currentNode;

        // 檢查新節點是否在關閉列表中
        bool inClosedList = false;
        for (int j = 0; j < closedListCount; j++) {
          if (closedList[j]->row == neighbor->row && closedList[j]->col == neighbor->col) {
            inClosedList = true;
            break;
          }
        }

        if (inClosedList) {
          delete neighbor;
          continue;
        }

        // 檢查新節點是否已經在開放列表中
        bool inOpenList = false;
        for (int j = 0; j < openListCount; j++) {
          if (openList[j]->row == neighbor->row && openList[j]->col == neighbor->col) {
            inOpenList = true;
            if (neighbor->g < openList[j]->g) {
              openList[j]->g = neighbor->g;
              openList[j]->f = neighbor->f;
              openList[j]->parent = neighbor->parent;
            }
            delete neighbor;
            break;
          }
        }

        if (!inOpenList) {
          openList[openListCount++] = neighbor;
        }
      }
    }
  }

  // 如果開放列表為空，表示沒有找到路徑
  return false;
}

int mapDirectToCarDegree(char firstDirect, char NextDirect) {
  int firstIndex = mapDirectToIndex(firstDirect);
  int NextIndex = mapDirectToIndex(NextDirect);
  if (NextIndex < firstIndex) {
    NextIndex += 4;
  };
  int degree = (NextIndex - firstIndex) * 90;
  return degree;
}

int mapDirectToIndex(char direct) {
  for (int i = 0; i < 4; i++) {
    if (MAP_DIRECT[i] == direct) {
      return i;
    };
  }
  return 0;
}

char* carDegreeToMove(int degree) {
  int index = degree / 90;
  return CAR_MOVE[index];
}

void reverseCharArray(char arr[], int length) {
  int start = 0;
  int end = length - 1;

  while (start < end) {
    // 交換陣列中的元素
    char temp = arr[start];
    arr[start] = arr[end];
    arr[end] = temp;

    // 移動指標以繼續反轉
    start++;
    end--;
  }
}

void reverseStringArray(String arr[], int length) {
  int start = 0;
  int end = length - 1;

  while (start < end) {
    // 交換陣列中的元素
    String temp = arr[start];
    arr[start] = arr[end];
    arr[end] = temp;

    // 移動指標以繼續反轉
    start++;
    end--;
  }
}

//設起訖點
void setStartEndPoint(String start, String end) {
  startPoint = start;
  endPoint = end;

  if (startPoint == GOODS_POINT) {
    startRow = 0;
    startCol = 0;
  } else if (startPoint == CHARGE_POINT) {
    startRow = 3;
    startCol = 0;
  } else if (startPoint == Recipient_POINT) {
    startRow = 3;
    startCol = 5;
  }

  if (endPoint == GOODS_POINT) {
    endRow = 0;
    endCol = 0;
  } else if (endPoint == CHARGE_POINT) {
    endRow = 3;
    endCol = 0;
  } else if (endPoint == Recipient_POINT) {
    endRow = 3;
    endCol = 5;
  }
}

bool starAStarPlan(char* target) {
  setStartEndPoint(currentPoint, target);                             //設起訖點
  bool isFindPath = aStar(grid, startRow, startCol, endRow, endCol);  //A*演算
  return isFindPath;
}

void starNav(bool isFindPath, char* target) {
  if (isFindPath) {
    Serial.println("找到路徑!");
    //座標起點
    pathXY[pathCount] = String(startRow) + "," + String(startCol);
    //車頭初始方向
    pathMapDirect[pathCount] = CAR_INIT_DIRECT;
    //座標轉換成車子移動指令
    convertXyToCarMove();
    //印出結果
    printAStarResult();
    //開始移動實際車子(含雲端平台GPS模擬)
    goCar();
    //紀錄
    CAR_INIT_DIRECT = pathMapDirect[pathCount];  //最後車頭方向,當成下次導航車頭起始方向
    currentPoint = target;                       //目前車子位置
  } else {
    Serial.println("未找到路徑.");
  }
}

void standByAiCam() {
  //A鏡頭上
  servoAiCam.write(ANGLE_AI_CAM_UP);
  delay(1000);

  //Hsukylens人臉識別模式
  huskylens.writeAlgorithm(ALGORITHM_FACE_RECOGNITION);
  CurrentAlgo = "ALGORITHM_FACE_RECOGNITION";
}


void setup() {
  Serial.begin(9600);
  //UART
  ESP32Serial.begin(9600);

  //按鈕I/O
  pinMode(BUTTON_SIGN_PIN, INPUT);

  //伺服馬達初始
  servoCarBox.attach(SERVO_CAR_BOX_PIN);
  servoCarBox.write(ANGLE_CAR_BOX_CLOSE);
  delay(1000);
  servoAiCam.attach(SERVO_AI_CAM_PIN);
  servoAiCam.write(ANGLE_AI_CAM_FRONT);
  delay(1000);

  //HuskyLens鏡頭初始化
  Wire.begin();
  while (!huskylens.begin(Wire)) {
    Serial.println(F("Begin failed!"));
    Serial.println(F("1.Please recheck the Protocol Type in HUSKYLENS (General Settings>>Protocol Type>>I2C)"));
    Serial.println(F("2.Please recheck the connection."));
    delay(100);
  }
  huskylens.writeAlgorithm(ALGORITHM_OBJECT_RECOGNITION);  //物體辨識模式
  CurrentAlgo = "ALGORITHM_OBJECT_RECOGNITION";

  //測電壓電流初始
  if (!ina219.begin()) {
    Serial.println("Failed to find INA219 chip");
    while (1) { delay(10); }
  }

  //小車初始化
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

  //循跡感測器初始化
  pinMode(TRACK_LEFT_PIN, INPUT);
  pinMode(TRACK_FRONT_PIN, INPUT);
  pinMode(TRACK_BACK_PIN, INPUT);
  pinMode(TRACK_RIGHT_PIN, INPUT);

  stopCar();
  delay(2000);
}

void convertXyToCarMove() {
  //反轉陣列(原本A*輸出結果相反)
  reverseStringArray(pathXY, pathCount + 1);
  reverseCharArray(pathMapDirect, pathCount + 1);

  //將地圖方向URDL轉成順時針角度90°,180°,270°
  for (int i = 0; i < pathCount + 1; i++) {
    pathCarDegree[i] = mapDirectToCarDegree(pathMapDirect[i], pathMapDirect[i + 1]);
  }

  //將角度轉換成車子移動F,RF,RRF,LF
  for (int i = 0; i < pathCount; i++) {
    pathCarMove[i] = carDegreeToMove(pathCarDegree[i]);
  }
}

void printAStarResult() {
  //印出地圖座標
  for (int i = 0; i < pathCount + 1; i++) {
    Serial.print(pathXY[i]);
    Serial.print("→");
  }
  Serial.println("");

  //印出地圖上下左右方向
  for (int i = 0; i < pathCount + 1; i++) {
    Serial.print(pathMapDirect[i]);
    Serial.print(',');
  }
  Serial.println("");

  //印出角度
  for (int i = 0; i < pathCount; i++) {
    Serial.print(pathCarDegree[i]);
    Serial.print(',');
  }
  Serial.println("");

  //印出車子移動指令
  for (int i = 0; i < pathCount; i++) {
    Serial.print(pathCarMove[i]);
    //Serial.print(',');
  }
  Serial.println("");
}


void loop() {
  //傳送訊息：Mega→ESP32
  // if (Serial.available()) {
  //   String str = Serial.readString();
  //   ESP32Serial.print(str);
  // }

  //接收訊息：ESP32→Mega
  while (ESP32Serial.available()) {
    String str = ESP32Serial.readString();
    Serial.println(str);

    if (str.indexOf(MAP_SET) != -1) {
      //開啟貨斗
      servoCarBox.write(ANGLE_CAR_BOX_OPEN);
      delay(1000);

      //儲存地圖陣列(格式:MAP_SET,4x6地圖陣列)
      String tmpArray[25];
      char* token = strtok((char*)str.c_str(), ",");
      int tokenLen = 0;
      while (token != NULL && tokenLen < 25) {
        tmpArray[tokenLen] = token;
        token = strtok(NULL, ",");
        tokenLen++;
      }

      int count = 1;  //第0個MAP_SET不用放入
      for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 6; j++) {
          grid[i][j] = tmpArray[count++].toInt();
        }
      }
    } else if (str.indexOf(GOODS_LOAD) != -1) {
      //儲存收件人陣列(格式:goodsLoad,姓名,商品,倉庫X,倉庫Y,收件人X,收件人Y)
      String tmpArray[7];
      char* token = strtok((char*)str.c_str(), ",");
      int tokenLen = 0;
      while (token != NULL && tokenLen < 7) {
        tmpArray[tokenLen] = token;
        token = strtok(NULL, ",");
        tokenLen++;
      }

      //第0個goodsLoad不用放入
      int count = 0;
      for (int i = 1; i < 7; i++) {
        recipient[count++] = tmpArray[i];
      }

      //關閉貨斗
      servoCarBox.write(ANGLE_CAR_BOX_CLOSE);
      delay(1000);

      //A*路徑歸劃
      bool isFindPath = starAStarPlan(Recipient_POINT);

      //開始導航
      starNav(isFindPath, Recipient_POINT);

      //抵達目的地,AI鏡頭朝向,準備人臉識別收貨人
      if (isFindPath) {
        standByAiCam();
      }

      //完成送貨，發送LINE通知收貨人(格式:LINE_NOTIFY,姓名,商品)
      if (isFindPath) {
        ESP32Serial.print(String(LINE_NOTIFY) + "," + recipient[0] + recipient[1]);
      }
    }
  }

  //等待AI人臉識別
  if (CurrentAlgo == "ALGORITHM_FACE_RECOGNITION") {
    //開始AI人臉識別
    startDetectObject();

    if (aiId == FACE_ID1) {
      Serial.println("收貨人1");
      //開鎖
      servoCarBox.write(ANGLE_CAR_BOX_OPEN);
      delay(1000);
      //復位
      servoAiCam.write(ANGLE_AI_CAM_FRONT);
      delay(1000);
      CurrentAlgo = "ALGORITHM_OBJECT_RECOGNITION";
    }
    //delay(500);
  }

  //按下簽收鈕
  if (digitalRead(BUTTON_SIGN_PIN) == 1) {
    //自動關閉貨斗
    servoCarBox.write(ANGLE_CAR_BOX_CLOSE);
    delay(1000);

    //A*路徑歸劃
    bool isFindPath = starAStarPlan(GOODS_POINT);
    //開始導航回物流站
    starNav(isFindPath, GOODS_POINT);
    //抵達物流站，車子原地轉向(車頭要朝下D，否則貨斗開啟方向會卡住)
    carHeadTurn('D');
  }

  //判斷是否電量低於20%
  checkIsLowPower(0.2);

}  //end loop

void checkIsLowPower(float lowPercent) {
  //在物流站才判斷
  if (currentPoint != GOODS_POINT) {
    return;
  }

  //取得電池當前電壓百分比(小數)
  float percent = getBusPowerPercent();

  if (percent <= lowPercent) {
    startCharge();
  }
}

float getBusPowerPercent() {
  const float minVolt = 6.3;  //以7.4v鋰電池為準
  const float maxVolt = 8.2;  //以7.4v鋰電池為準
  //測電壓電流
  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  power_mW = ina219.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);

  return ((busvoltage - minVolt) / (maxVolt - minVolt));
}

void startCharge() {
  //導航至充電站
  bool isFindPath = starAStarPlan(CHARGE_POINT);
  starNav(isFindPath, CHARGE_POINT);

  //進充電站前，車子原地轉向，車頭要朝左L
  carHeadTurn('L');

  //接著倒車進入充電站
  backward();
  delay(2000);  //xx秒數要測試
  stopCar();

  //充電中……
  float percent = 0.0;
  while (percent < 1) {  //100%
    percent = getBusPowerPercent();
    delay(10000);
  }

  //充電完成，車子往前開出充電站
  forward();
  delay(2000);  //xx秒數要測試
  stopCar();

  //完成充電，導航回物流站
  isFindPath = starAStarPlan(GOODS_POINT);
  starNav(isFindPath, GOODS_POINT);
}


void carHeadTurn(char targetDirect) {
  //車頭轉向
  int degree = mapDirectToCarDegree(CAR_INIT_DIRECT, targetDirect);
  char* CAR_MOVE_NO_FRONT[4] = { "", "R", "RR", "L" };
  int index = degree / 90;
  if (CAR_MOVE_NO_FRONT[index] == "R") {
    turnRight();
    delay(RTimer);
    stopCar();
    delay(RTimer);
    Serial.println("右轉,");
  } else if (CAR_MOVE_NO_FRONT[index] == "RR") {
    for (int i = 0; i < 2; i++) {
      turnRight();
      delay(RTimer);
      stopCar();
      delay(RTimer);
      Serial.println("右轉,");
    }
  } else if (CAR_MOVE_NO_FRONT[index] == "L") {
    turnLeft();
    delay(LTimer);
    stopCar();
    delay(LTimer);
    Serial.println("左轉,");
  }

  //紀錄車頭方向
  CAR_INIT_DIRECT = targetDirect;
}
