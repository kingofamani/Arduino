#include <Arduino.h>
//★★★車頭初始向右邊

// 定義地圖大小
const int numRows = 5;
const int numCols = 8;

//儲存座標結果
String pathXY[numRows * numCols];
int pathXYCount = 0;

//儲存方向結果
char pathDirect[numRows * numCols];
int pathDirectCount = 0;

//小烏龜移動路徑
char* pathTurtle[numRows * numCols];

//小烏龜移動矩陣
char* matrix[3][3] = {
  {"-", "L,F,", "-"},
  {"R,R,F,", "-", "F,"},
  {"-", "R,F,", "-"}
};
//  char* matrix[3][3] = {
//   {"-", "LF", "-"},
//   {"RRF", "-", "F"},
//   {"-", "RF", "-"}
// };


//範例
//const int pathCount=8;
//char pathDirect[pathCount]={'R','D','L','U'};//F,RF,RF,RF,
//char pathDirect[pathCount]={'U','L','D','R'};//LF,LF,LF,LF,
//char pathDirect[pathCount]={'R','R','D','L','L','D','R','R'};//F,F,RF,RF,F,LF,LF,F,
//char pathDirect[pathCount]={'L','L','U','R','R','U','L','L'};//RRF,F,RF,RF,F,LF,LF,F,
//char* pathTurtle[pathCount];

//ESP32腳位
byte m1aL9110 = 16;
byte m1bL9110 = 17;
byte m2aL9110 = 21;
byte m2bL9110 = 22;
byte m1bCH = 13;
byte m2bCH = 14;



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
        pathXY[pathXYCount++] = "[" + String(current->row) + "," + String(current->col) + "]";

        int deltaX = current->col - current->parent->col;
        int deltaY = current->row - current->parent->row;

        if (deltaX == 1) {
          //Serial.print("右");
          pathDirect[pathDirectCount++] = 'R';
        } else if (deltaX == -1) {
          //Serial.print("左");
          pathDirect[pathDirectCount++] = 'L';
        } else if (deltaY == 1) {
          //Serial.print("下");
          pathDirect[pathDirectCount++] = 'D';
        } else if (deltaY == -1) {
          //Serial.print("上");
          pathDirect[pathDirectCount++] = 'U';
        }

        //Serial.println("");

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

//旋轉小烏龜移動矩陣
void rotateMatrix(int degrees) {
  char* temp[3][3];

  // 顺时针旋转90度
  if (degrees == 90) {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        temp[i][j] = matrix[3 - 1 - j][i];
      }
    }
    // 旋转180度
  } else if (degrees == 180) {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        temp[i][j] = matrix[3 - 1 - i][3 - 1 - j];
      }
    }
    // 逆时针旋转90度
  } else if (degrees == 270) {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        temp[i][j] = matrix[j][3 - 1 - i];
      }
    }
  }

  // 更新原始数组
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix[i][j] = temp[i][j];
      //Serial.print(matrix[i][j]);
      //Serial.print(",");
    }
    //Serial.println("");
  }
}

//旋轉小烏龜移動矩陣
//當車頭轉向時，就要旋轉矩陣
void rotateMatrixByTurtle(char* turtle) {
  if (turtle == "RF") {
    rotateMatrix(90);
  } else if (turtle == "RRF") {
    rotateMatrix(180);
  } else if (turtle == "LF") {
    rotateMatrix(270);
  }
}

//將上下左右轉換成小烏龜移動
char* directToTurtle(char direct) {
  char* tur = "";
  if (direct == 'U') {
    tur = matrix[0][1];
  } else if (direct == 'D') {
    tur = matrix[2][1];
  } else if (direct == 'L') {
    tur = matrix[1][0];
  } else if (direct == 'R') {
    tur = matrix[1][2];
  }
  return tur;
}

void forward() {
  digitalWrite(m1aL9110, 1);
  ledcWrite(m1bCH, 255 - 255);
  digitalWrite(m2aL9110, 1);
  ledcWrite(m2bCH, 255 - 255);
  Serial.print("前,");
}

void backward() {
  digitalWrite(m1aL9110, 0);
  ledcWrite(m1bCH, 255);
  digitalWrite(m2aL9110, 0);
  ledcWrite(m2bCH, 255);
  Serial.print("x");
}

void turnRight() {
  digitalWrite(m1aL9110, 1);
  ledcWrite(m1bCH, 255 - 255);
  digitalWrite(m2aL9110, 1);
  ledcWrite(m2bCH, 255);
  Serial.print("右,");
}

void turnLeft() {
  digitalWrite(m2aL9110, 1);
  ledcWrite(m2bCH, 255 - 255);
  digitalWrite(m1aL9110, 1);
  ledcWrite(m1bCH, 255);
  Serial.print("左,");
}

void stopCar() {
  digitalWrite(m1aL9110, 1);
  ledcWrite(m1bCH, 255);
  digitalWrite(m2aL9110, 1);
  ledcWrite(m2bCH, 255);
}

void turtleToCarMove(char* turtle) {

}



void setup() {
  //★★★車頭初始向右邊

  Serial.begin(9600);

  //馬達
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

  // 地圖表示，0表示障礙物，1表示可通行
  int grid[numRows][numCols] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1}
  };
  //  int grid[numRows][numCols] = {
  //    {1, 1, 1, 1, 1, 1, 1, 1},
  //    {0, 0, 0, 0, 0, 0, 0, 1},
  //    {1, 1, 1, 1, 1, 1, 1, 1},
  //    {1, 0, 0, 0, 0, 0, 0, 0},
  //    {1, 1, 1, 1, 1, 1, 1, 1},
  //    {0, 0, 0, 0, 0, 0, 0, 1},
  //    {1, 0, 1, 1, 1, 1, 1, 1},
  //    {1, 1, 1, 1, 1, 1, 1, 1}
  //  };

  int startRow = 0;
  int startCol = 0;
  int endRow = 4; // 更新endRow和endCol到所需的終點位置
  int endCol = 7;

  Serial.println("A* 路徑:");

  if (aStar(grid, startRow, startCol, endRow, endCol)) {
    Serial.println("找到路徑!");
    printAStarResult();
  } else {
    Serial.println("未找到路徑.");
  }

}

//印出結果
void printAStarResult() {
  //印出座標
  for (int i = pathXYCount - 1; i >= 0; i--) {
    Serial.println(pathXY[i]);
  }

  Serial.println("");

  //印出上下左右方向
  for (int i = pathDirectCount - 1; i >= 0; i--) {
    Serial.println(pathDirect[i]);
  }

  Serial.println("");

  //將上下左右方向轉成Turtle移動方向
  for (int i = pathDirectCount - 1; i >= 0; i--) {
    pathTurtle[i] = directToTurtle(pathDirect[i]);
    rotateMatrixByTurtle(pathTurtle[i]);
  }
  for (int i = pathDirectCount - 1; i >= 0; i--) {
    //Serial.print(pathTurtle[i]);
    //Serial.print(',');
  }
  //以上要配合：
  //  char* matrix[3][3] = {
  //   {"-", "LF", "-"},
  //   {"RRF", "-", "F"},
  //   {"-", "RF", "-"}
  // };

  Serial.println("");

  //移動車子：
  //1.先將小烏龜轉成字串
  String stringPathTurtle = "";
  for (int i = pathDirectCount - 1; i >= 0; i--) {
    stringPathTurtle += pathTurtle[i];
  }
  Serial.println(stringPathTurtle);

  //2.字串轉成陣列
  // 使用 strtok() 函数分割字符串
  String startMoveCarArray[200];
  char *token = strtok((char *)stringPathTurtle.c_str(), ",");
  int tokenLen = 0;
  //字串轉成陣列
  while (token != NULL && tokenLen < 200) {
    startMoveCarArray[tokenLen] = token;
    token = strtok(NULL, ",");
    tokenLen++;
  }

  //3.開始移動車子
  for (int i = 0 ; i < tokenLen ; i++)
  {
    if(startMoveCarArray[i]=="F"){
      forward();
    }else if(startMoveCarArray[i]=="R"){
      turnRight();
    }else if(startMoveCarArray[i]=="L"){
      turnLeft();
    }
    //Serial.println(startMoveCar[i]);
  }


}

void loop() {
  // 程序主循環
}
