#include <Arduino.h>
//序列埠115200

//★★★車頭初始向上
char CAR_INIT_DIRECT = 'U';

// 定義地圖大小
const int numRows = 5;
const int numCols = 8;

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
//char* CAR_MOVE[4] = {"F", "RF", "RRF", "LF"};

//====UART通訊(UNO傳來循跡感測器結果) start====
#define U1RXD 16
#define U1TXD 17

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
bool loopHasRun = false;

//====UART end====


//===========小車Start===========
//L298N腳位
#define L298N_IN1 14
#define L298N_IN2 27
#define L298N_IN3 26
#define L298N_IN4 25
#define L298N_IN5 23
#define L298N_IN6 4
#define L298N_IN7 15  //原16
#define L298N_IN8 32  //原17

#define L298N_EN1 13  //PWM
#define L298N_EN2 33  //PWM
#define L298N_EN3 5   //PWM
#define L298N_EN4 19  //PWM

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

void trackForward() {
  Serial.print("trackForward,");
  //每隔ms觸發一次循跡

  //先往前300ms,越過前方白線
  forward();
  Serial.print("forward,");
  delay(300);
  //stopCar();
  //接收循跡值
  //trackFromUNO();
  //開始前進,直循跡感測踫到前方白線
  int trackTimer = 20;
  while(!isFrontArrive){
    Serial.print("while,");
    //開始判斷偏左、偏右、跑完一格
    if(trackSensor[TRACK_LEFT]==TRIGGLED && trackSensor[TRACK_RIGHT]!=TRIGGLED){
      diagonalLeft();      
      //stopCar();
    }else if(trackSensor[TRACK_LEFT]!=TRIGGLED && trackSensor[TRACK_RIGHT]==TRIGGLED){
      diagonalRight();
      //stopCar();
    }else{
      forward();
      //stopCar();
    }
    delay(trackTimer);

    if(trackSensor[TRACK_FRONT]==TRIGGLED){
      stopCar();
      delay(STimer);
      //結束此格行走
      isFrontArrive = true;
    }
  }//end while
}

void diagonalRight() {
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

void diagonalLeft() {
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
  for (int i = 0; i < tokenLen; i++) {
    if (pathCarMotor[i] == "F") {
      trackForward();
      isFrontArrive = false;
      //forward();
      //delay(FTimer);
      //stopCar();
      //delay(FTimer);
      Serial.print("前,");
    } else if (pathCarMotor[i] == "R") {
      turnRight();
      delay(RTimer);
      stopCar();
      delay(RTimer);
      Serial.print("右轉,");
    } else if (pathCarMotor[i] == "L") {
      turnLeft();
      delay(LTimer);
      stopCar();
      delay(LTimer);
      Serial.print("左轉,");
    }
  }
}

//===========小車End===========

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

// A*算法
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
        //Serial.print("[" + String(current->row) + "," + String(current->col) + "] ");
        pathXY[pathCount] = "(" + String(current->row) + "," + String(current->col) + ")";

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

void setup() {
  Serial.begin(115200);
  //UART
  Serial2.begin(9600, SERIAL_8N1, U1RXD, U1TXD);

  //=====小車初始化START=====
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
  ledcSetup(EN1_CHL, 1000, 8);  //channel,frequence,resolution(8表示0~255)
  ledcAttachPin(L298N_EN1, EN1_CHL);
  ledcSetup(EN2_CHL, 1000, 8);
  ledcAttachPin(L298N_EN2, EN2_CHL);
  ledcSetup(EN3_CHL, 1000, 8);
  ledcAttachPin(L298N_EN3, EN3_CHL);
  ledcSetup(EN4_CHL, 1000, 8);
  ledcAttachPin(L298N_EN4, EN4_CHL);

  stopCar();
  delay(2000);
  //=====小車初始化END=====
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
    Serial.print(',');
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

//UART接收UNO傳送來的循跡感測器結果(左前後右ex:1011)
void trackFromUNO() {
  //Serial.print("trackFromUNO,");
  String str = Serial2.readString();
  Serial.print(str);
  for (int i = 0; i < 4; i++) {
    trackSensor[i] = (int)(str.charAt(i) - '0');
  }
}

//UART接收UNO傳送來的循跡感測器結果(左前後右ex:1011)
// void trackFromUNO(){
//   Serial.print("trackFromUNO,");
//   if (Serial2.available()) {
//     Serial.print("available,");
//     String str = Serial2.readString();
//     Serial.print("str:");
//     Serial.print(str);
//     for(int i=0;i<4;i++){
//       trackSensor[i] = (int)(str.charAt(i) - '0');
//     }
//     Serial.print(trackSensor[TRACK_LEFT]);
//     Serial.print(trackSensor[TRACK_FRONT]);
//     Serial.print(trackSensor[TRACK_BACK]);
//     Serial.println(trackSensor[TRACK_RIGHT]);
//     //Serial.println("===");
//   }
// }

void loop() {
  if (loopHasRun) {
    return;
  }

  // 地圖表示，0表示障礙物，1表示可通行
  int grid[numRows][numCols] = {
    { 1, 1, 1, 1, 1, 1, 1, 1 },
    { 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0 },
    { 1, 1, 1, 1, 1, 1, 1, 1 }
  };

  int startRow = 0;
  int startCol = 0;
  int endRow = 4;  // 更新endRow和endCol到所需的終點位置
  int endCol = 7;

  if (aStar(grid, startRow, startCol, endRow, endCol)) {
    Serial.println("找到路徑!");
    //座標起點
    pathXY[pathCount] = "(" + String(startRow) + "," + String(startCol) + ")";
    //車頭初始方向
    pathMapDirect[pathCount] = CAR_INIT_DIRECT;
    //座標轉換成車子移動指令
    convertXyToCarMove();
    //印出結果
    printAStarResult();
    //開始移動實際車子
    goCar();
  } else {
    Serial.println("未找到路徑.");
  }

  loopHasRun = true;
}
