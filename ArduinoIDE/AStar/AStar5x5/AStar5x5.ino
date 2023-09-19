#include <Arduino.h>

// 定義地圖大小
const int numRows = 5;
const int numCols = 5;

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
      while (current != nullptr) {
        Serial.print("[" + String(current->row) + "," + String(current->col) + "] ");
        current = current->parent;
      }
      Serial.println();
      return true;
    }

    // 獲取當前節點的相鄰節點
    int neighbors[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

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

void setup() {
  Serial.begin(9600);

  // 地圖表示，0表示障礙物，1表示可通行
  int grid[numRows][numCols] = {
    {1, 1, 1, 1, 1},
    {0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0},
    {1, 1, 1, 1, 1}
  };

  int startRow = 0;
  int startCol = 0;
  int endRow = 4;
  int endCol = 4;

  Serial.println("A* 路徑:");

  if (aStar(grid, startRow, startCol, endRow, endCol)) {
    Serial.println("找到路徑!");
  } else {
    Serial.println("未找到路徑.");
  }
}

void loop() {
  // 程序主循環
}
