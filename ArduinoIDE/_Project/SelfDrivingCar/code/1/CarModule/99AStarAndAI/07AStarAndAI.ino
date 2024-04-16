#include <Arduino.h>
#include "HUSKYLENS.h"
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
char MAP_DIRECT[4] = {'U', 'R', 'D', 'L'};
int pathCount = 0;

//儲存車子(順時針)轉動角度
int pathCarDegree[numRows * numCols];

//儲存車子移動方向
char* pathCarMove[numRows * numCols];
char* CAR_MOVE[4] = {"F,", "R,F,", "R,R,F,", "L,F,"};
//char* CAR_MOVE[4] = {"F", "RF", "RRF", "LF"};

//儲存車子開始移動，馬達轉向
String pathCarMotor[numRows * numCols * 3]; //每個指令最多可拆成3個，例如RRF
int pathCarMotorCount = 0;

/***

   實體小車和馬達相關程式

*/
//===========小車Start===========
byte m1aL9110 = 16;
byte m1bL9110 = 17;
byte m2aL9110 = 19;
byte m2bL9110 = 23;
byte m1bCH = 13;
byte m2bCH = 14;

int ForwardTime = 500;
int turnTime = 300;
int stopTime = 1000;
int ForwardSpeed = 255;
int turnSpeed = 255;
void forward() {
  digitalWrite(m1aL9110, 1);
  ledcWrite(m1bCH, 255 - ForwardSpeed);
  digitalWrite(m2aL9110, 1);
  ledcWrite(m2bCH, 255 - ForwardSpeed);
  delay(ForwardTime);
  Serial.print("前,");
}

void backward() {
  digitalWrite(m1aL9110, 0);
  ledcWrite(m1bCH, ForwardSpeed);
  digitalWrite(m2aL9110, 0);
  ledcWrite(m2bCH, ForwardSpeed);
  delay(ForwardTime);
  Serial.print("x");
}

void turnRight() {
  digitalWrite(m1aL9110, 1);
  ledcWrite(m1bCH, 255 - turnSpeed);
  digitalWrite(m2aL9110, 1);
  ledcWrite(m2bCH, 255);
  delay(turnTime);
  Serial.print("右,");
}

void turnLeft() {
  digitalWrite(m2aL9110, 1);
  ledcWrite(m2bCH, 255 - turnSpeed);
  digitalWrite(m1aL9110, 1);
  ledcWrite(m1bCH, 255);
  delay(turnTime);
  Serial.print("左,");
}

void stopCar() {
  digitalWrite(m1aL9110, 1);
  ledcWrite(m1bCH, 255);
  digitalWrite(m2aL9110, 1);
  ledcWrite(m2bCH, 255);
  delay(stopTime);
  Serial.print("停,");
}

void goCar() {
  for (int i = 0 ; i < pathCarMotorCount ; i++)
  {
    if (pathCarMotor[i] == "F") {
      forward();
    } else if (pathCarMotor[i] == "R") {
      turnRight();
    } else if (pathCarMotor[i] == "L") {
      turnLeft();
    }
  }

}

//===========小車End===========

/***

   HsukyLens AI鏡頭相關程式
   程式由BlockyDuino積木ICSHOP產生

   HsukyLens(ESP32的I2C接腳是21,22)：
    T 21
    R 22
    - GND
    + 5V
*/
//===========HsukyLens AI鏡頭Start===========
//
HUSKYLENS huskylens;
int readData[5] = {};
byte dataType = 0;
byte idCount = 0;
bool detection_now = 0;

int aiId = 0;
int aiX = 0; //中心點X座標
int aiY = 0; //中心點Y座標
int aiWidth = 0;
int aiHeight = 0;
const int PERSON_ID = 1;//人(透過AI鏡頭訓練)
const int CAR_ID = 2;//車子

void goCarByAI() {
  for (int i = 0 ; i < pathCarMotorCount ; i++)
  {
    if (pathCarMotor[i] == "F") {
      AiDetect();
      forward();
    } else if (pathCarMotor[i] == "R") {
      turnRight();
    } else if (pathCarMotor[i] == "L") {
      turnLeft();
    }
  }
}

void AiDetect() {
  startDetectObject();
  while (detection_now) {
    if (aiId == 0){
      break;
    }
    if (aiId > 0) {
      stopCar();
      if (aiId == PERSON_ID) {
        Serial.println("人");
      } else if (aiId == CAR_ID) {
        Serial.println("車");
      }            
    }
    delay(500);
    startDetectObject();
  }
}

void startDetectObject() {
  if (!huskylens.request()) {
    Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
  }
  else {
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
      }
      else if (result.command == COMMAND_RETURN_ARROW) {
        dataType = 1;
        readData[0] = result.xOrigin;
        readData[1] = result.yOrigin;
        readData[2] = result.xTarget;
        readData[3] = result.yTarget;
        readData[4] = result.ID;
      }
      else {
        for (byte i = 0; i < 5; i++) {
          readData[i] = 0;
        }
      }
    }
    else {
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
      Serial.print(',');
      Serial.print(aiX);
      Serial.print(',');
      Serial.print(aiY);
      Serial.print(',');
      Serial.print(aiWidth);
      Serial.print(',');
      Serial.println(aiHeight);
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
    int f; // f = g + h，表示節點的總代價
    int g; // 從起點到當前節點的實際代價
    int h; // 從當前節點到目標節點的估算代價
    Node* parent;

    Node(int r, int c) : row(r), col(c), f(0), g(0), h(0), parent(nullptr) {}

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
    int neighbors[4][2] = {{ -1, 0}, {1, 0}, {0, -1}, {0, 1}};

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
        neighbor->g = currentNode->g + 1; // 假設每個步驟的代價都是1
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
  Serial.begin(9600);

  //HuskyLens鏡頭初始化
  Wire.begin();
  while (!huskylens.begin(Wire)) {
    Serial.println(F("Begin failed!"));
    Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>I2C)"));
    Serial.println(F("2.Please recheck the connection."));
    delay(100);
  }
  huskylens.writeAlgorithm(ALGORITHM_OBJECT_RECOGNITION);

  //小車初始化
  pinMode(m1aL9110, OUTPUT);
  pinMode(m2aL9110, OUTPUT);
  ledcSetup(m1bCH, 5000, 8);
  ledcAttachPin(m1bL9110, m1bCH);
  ledcSetup(m2bCH, 5000, 8);
  ledcAttachPin(m2bL9110, m2bCH);
  digitalWrite(m1aL9110, 1);
  ledcWrite(m1bCH, 255);
  digitalWrite(m2aL9110, 1);
  ledcWrite(m2bCH, 255);

  // 地圖初始，0表示障礙物，1表示可通行
  int grid[numRows][numCols] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1}
  };

  int startRow = 0;
  int startCol = 0;
  int endRow = 4;// 更新endRow和endCol到所需的終點位置
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
    //goCar();//只有A*演算法移動車子
    goCarByAI();//透過AI鏡頭，考慮行人及車子
  } else {
    Serial.println("未找到路徑.");
  }

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
  for (int i = 0 ; i  < pathCount; i++) {
    pathCarMove[i] = carDegreeToMove(pathCarDegree[i]);
  }

  //將車子移動指令F,RF,RRF,LF一一分解成
  pathCarMoveToMotor();
}

void pathCarMoveToMotor() {
  //1.先將移動指令轉成字串
  String stringPathCarMotor = "";
  for (int i = 0 ; i  < pathCount; i++) {
    stringPathCarMotor += pathCarMove[i];
  }
  Serial.println(stringPathCarMotor);

  //2.字串轉成陣列
  //使用 strtok() 函数分割字符串
  char *token = strtok((char *)stringPathCarMotor.c_str(), ",");
  int tokenLen = 0;
  //字串轉成陣列
  while (token != NULL && tokenLen < pathCount * 3) {
    pathCarMotor[tokenLen] = token;
    token = strtok(NULL, ",");
    tokenLen++;
  }
  pathCarMotorCount = tokenLen;
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
  for (int i = 0; i  < pathCount; i++) {
    Serial.print(pathCarDegree[i]);
    Serial.print(',');
  }
  Serial.println("");

  //印出車子移動指令
  for (int i = 0 ; i  < pathCount; i++) {
    Serial.print(pathCarMove[i]);
    //Serial.print(',');
  }
  Serial.println("");

}

void loop() {
  // 程序主循環
}
