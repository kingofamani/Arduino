/*
   Generated using BlocklyDuino:

   https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt

   Date: Mon, 14 Mar 2022 02:16:27 GMT
*/
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
//★若是用Arduino IDE序列埠視窗，一定要選取「沒有行結尾」

//pos下棋的位置
int pos = 1;
//初始玩家(重新一盤時玩家互換用)
int startPlayer = 0;
//0玩家、1AI
int player = startPlayer;

//玩家名稱
String playerName[2] = {"您(玩家)", "AI"};
//玩家o、AIx
char go[2] = {'o', 'x'};
//board整個棋盤
char board[9] = {'-', '-', '-', '-', '-', '-', '-', '-', '-'};

//每個位置的權重(中央1000,角100,邊10)
int weights[9] = {100, 10, 100, 10, 1000, 10, 100, 10, 100};
//wins連線獲勝的8種情況
int wins[8][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 4, 7}, {2, 5, 8}, {3, 6, 9}, {1, 5, 9}, {3, 5, 7}};
//isWin是否連線獲勝
boolean isWin = false;

//玩家 勝-負-和 統計
int scores[3] = {0, 0, 0};

//lines儲存已下棋的各種連線子數
/*
   第一層[2]玩家1、玩家2(AI)
   第二層[8]8種連線方式
   第三層[3]每1種連線方式已收集數字。0表示未收集、1表示已收集
   例如：AI已經下了1,2位置，則：
    lines[1][0]={1,1,0}、[1][3]={1,0,0}、[1][4]={1,0,0}、[1][6]={1,0,0}
*/
int lines[2][8][3] =
{
  {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  },
  {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  }
};


boolean checkIsRepeat() {
  boolean isRepeat = false;
  if (board[pos - 1] != '-') {
    isRepeat = true;
  }
  return (isRepeat);
}

void showSample() {
  Serial.println((String("請") + playerName[player] + "(" + go[player] + String(")開始下棋(輸入1~9)：")));
  for (int i = 1; i <= 9; i++) {
    Serial.print(i);
    Serial.print(",");
    if (i % 3 == 0) {
      Serial.println("");
    }
  }
}

void showBoard() {
  for (int i = 0; i <= 8; i++) {
    Serial.print((board[i]));
    Serial.print(",");
    if ((i + 1) % 3 == 0) {
      Serial.println("");
    }
  }
}

void setPosition() {
  Serial.println((playerName[player] + String("下的位置在") + String(pos)));
  board[pos - 1] = go[player];
}

void changePlayer() {
  player == 0 ? player = 1 : player = 0;
  if (!isWin) {

    //玩家
    Serial.println("");
    Serial.println((String("請換") + playerName[player] + "(" + go[player] + String(")下棋(輸入1~9)：")));
    showBoard();
  }
}

void reStart() {
  //重置變數
  pos = 1;

  //換先手
  if (startPlayer == 0) {
    player = 1;
    startPlayer = 1;
  } else {
    player = 0;
    startPlayer = 0;
  }

  isWin = false;

  for (int i = 0; i <= 8; i++) {
    board[i] = '-';
  }

  boolean isWin = false;

  for (int i = 0; i <= 1; i++) {
    for (int j = 0; j <= 7; j++) {
      for (int k = 0; k <= 2; k++) {
        lines[i][j][k] = 0;
      }
    }
  }

  Serial.println("");
  Serial.println("--------------新的一局----------------");
  Serial.println("交換，改由" + playerName[player] + "先下棋");
  delay(1000);

  //顯示位置編號
  showSample();
}

boolean checkIsFullBoard() {
  boolean isFull = true;
  for (int i = 0; i <= 8; i++) {
    if (board[i] == '-') {
      isFull = false;
    }
  }
  return (isFull);
}

int autoAiPos() {
  
  //
  if (isCase3_1()) {
    //Serial.println("3-1、");
    return 2;
  }
  if (isCase6_1()) {
    //Serial.println("6-1、");
    return case6_1_pos();
  }
  if (isCase6_2()) {
    //Serial.println("6-2、");
    return case6_2_pos();
  }

  //
  for (int i = 0; i <= 7; i++) {
    int count = lines[1][i][0] + lines[1][i][1] + lines[1][i][2];
    if (count == 2) {
      int lastPos = theLastPos(1, i);
      if (checkIsEmpty(lastPos)) {
        //Serial.println("1、");
        return lastPos;
      }
    }
  }

  //
  for (int i = 0; i <= 7; i++) {
    int count = lines[0][i][0] + lines[0][i][1] + lines[0][i][2];
    if (count == 2) {
      int lastPos = theLastPos(0, i);
      if (checkIsEmpty(lastPos)) {
        //Serial.println("2、");
        return lastPos;
      }
    }
  }

  //
  int playerDoubleListen = doubleListen(0);
  if (playerDoubleListen != 0) {
    //Serial.println("3-2、");
    return playerDoubleListen;
  }

  //
  int aiDoubleListen = doubleListen(1);
  if (aiDoubleListen != 0) {
    //Serial.println("4、");
    return aiDoubleListen;
  }

  //
  int aiOneListen = oneListen(1);
  if (aiOneListen != 0) {
    //Serial.println("5、");
    return aiOneListen;
  }

  return maxWeight();
}

int oneListen(int player) {
  int oneListenPos = 0;
  int listenPos[72] = {};
  int countListenPos = 0;
  for (int p = 1; p <= 9; p++) {
    for (int i = 0; i <= 7; i++) {
      int count = lines[player][i][0] + lines[player][i][1] + lines[player][i][2];
      if (count == 1 && winsHasPos(i, p) && checkIsEmpty(p)) {
        listenPos[countListenPos] = p;
        countListenPos++;
      }
    }
  }

  if (countListenPos > 0) {
    int count = 0;
    for (int p = 1; p <= 9; p++) {
      for (int i = 0; i <= (countListenPos - 1); i++) {
        if (listenPos[i] == p) {
          count++;
        }
      }
      if (count == 1) {

        oneListenPos = p;
      }
      count = 0;
    }
  }

  return oneListenPos;
}

int doubleListen(int player) {
  int maxWeightAndDoubleListenPos = 0;
  int listenPos[72] = {};
  int countListenPos = 0;
  for (int p = 1; p <= 9; p++) {
    for (int i = 0; i <= 7; i++) {
      int count = lines[player][i][0] + lines[player][i][1] + lines[player][i][2];
      if (count == 1 && winsHasPos(i, p) && checkIsEmpty(p)) {
        listenPos[countListenPos] = p;
        countListenPos++;
      }
    }
  }

  if (countListenPos > 0) {
    int doubleListenPos[9] = {};
    int countDoubleListenPos = 0;
    int count = 0;
    for (int p = 1; p <= 9; p++) {
      for (int i = 0; i <= (countListenPos - 1); i++) {
        if (listenPos[i] == p) {
          count++;
        }
      }
      if (count >= 2) {
        doubleListenPos[countDoubleListenPos] = p;
        countDoubleListenPos++;
      }
      count = 0;
    }

    //找權重最大
    if (countDoubleListenPos > 0) {
      maxWeightAndDoubleListenPos = doubleListenPos[0];//先預設第1個
      for (int i = 0; i <= (countDoubleListenPos - 1); i++) {
        if (weights[doubleListenPos[i] - 1] > weights[maxWeightAndDoubleListenPos - 1]) {
          maxWeightAndDoubleListenPos = doubleListenPos[i];
        }
      }
    }
  }

  return maxWeightAndDoubleListenPos;
}

int maxWeight() {
  //Serial.println("6-3、");
  int maxWPos = emptyWeight10Pos();
  for (int p = 1; p <= 9; p++) {
    if (checkIsEmpty(p)) {
      if (weights[p - 1] > weights[maxWPos - 1]) {
        maxWPos = p;
      }
    }
  }
  return maxWPos;
}

int emptyWeight10Pos() {
  int pos = 0;
  for (int p = 1; p <= 9; p++) {
    if (weights[p - 1] == 10 && checkIsEmpty(p)) {
      pos = p;
    }
  }
  return pos;
}

//
boolean isCase6_2() {
  bool is6_2 = false;
  char board6_2_1[9] = {'-', 'o', '-', '-', 'x', '-', '-', '-', '-'};
  char board6_2_2[9] = {'-', '-', '-', 'o', 'x', '-', '-', '-', '-'};
  char board6_2_3[9] = {'-', '-', '-', '-', 'x', 'o', '-', '-', '-'};
  char board6_2_4[9] = {'-', '-', '-', '-', 'x', '-', '-', 'o', '-'};

  int count1 = 0;
  int count2 = 0;
  int count3 = 0;
  int count4 = 0;
  for (int i = 0; i < 9; i++) {
    if (board[i] == board6_2_1[i]) {
      count1++;
    }
    if (board[i] == board6_2_2[i]) {
      count2++;
    }
    if (board[i] == board6_2_3[i]) {
      count3++;
    }
    if (board[i] == board6_2_4[i]) {
      count4++;
    }
  }

  if (count1 == 9 || count2 == 9 || count3 == 9 || count4 == 9) {
    is6_2 = true;
  }

  return is6_2;
}

int case6_2_pos() {
  int is6_2 = 0;
  char board6_2_1[9] = {'-', 'o', '-', '-', 'x', '-', '-', '-', '-'};
  char board6_2_2[9] = {'-', '-', '-', 'o', 'x', '-', '-', '-', '-'};
  char board6_2_3[9] = {'-', '-', '-', '-', 'x', 'o', '-', '-', '-'};
  char board6_2_4[9] = {'-', '-', '-', '-', 'x', '-', '-', 'o', '-'};

  int count1 = 0;
  int count2 = 0;
  int count3 = 0;
  int count4 = 0;
  for (int i = 0; i < 9; i++) {
    if (board[i] == board6_2_1[i]) {
      count1++;
    }
    if (board[i] == board6_2_2[i]) {
      count2++;
    }
    if (board[i] == board6_2_3[i]) {
      count3++;
    }
    if (board[i] == board6_2_4[i]) {
      count4++;
    }
  }

  if (count1 == 9) {
    is6_2 = 1; //or 3
  }
  if (count2 == 9) {
    is6_2 = 7; //or 1
  }
  if (count3 == 9) {
    is6_2 = 3; //or 9
  }
  if (count4 == 9) {
    is6_2 = 9; //or 7
  }

  return is6_2;
}

//
boolean isCase6_1() {
  bool is6_1 = false;
  char board6_1_1[9] = {'o', '-', '-', '-', 'x', '-', '-', '-', '-'};
  char board6_1_2[9] = {'-', '-', 'o', '-', 'x', '-', '-', '-', '-'};
  char board6_1_3[9] = {'-', '-', '-', '-', 'x', '-', 'o', '-', '-'};
  char board6_1_4[9] = {'-', '-', '-', '-', 'x', '-', '-', '-', 'o'};

  int count1 = 0;
  int count2 = 0;
  int count3 = 0;
  int count4 = 0;
  for (int i = 0; i < 9; i++) {
    if (board[i] == board6_1_1[i]) {
      count1++;
    }
    if (board[i] == board6_1_2[i]) {
      count2++;
    }
    if (board[i] == board6_1_3[i]) {
      count3++;
    }
    if (board[i] == board6_1_4[i]) {
      count4++;
    }
  }

  if (count1 == 9 || count2 == 9 || count3 == 9 || count4 == 9) {
    is6_1 = true;
  }

  return is6_1;
}

int case6_1_pos() {
  int is6_1 = 0;
  char board6_1_1[9] = {'o', '-', '-', '-', 'x', '-', '-', '-', '-'};
  char board6_1_2[9] = {'-', '-', 'o', '-', 'x', '-', '-', '-', '-'};
  char board6_1_3[9] = {'-', '-', '-', '-', 'x', '-', 'o', '-', '-'};
  char board6_1_4[9] = {'-', '-', '-', '-', 'x', '-', '-', '-', 'o'};

  int count1 = 0;
  int count2 = 0;
  int count3 = 0;
  int count4 = 0;
  for (int i = 0; i < 9; i++) {
    if (board[i] == board6_1_1[i]) {
      count1++;
    }
    if (board[i] == board6_1_2[i]) {
      count2++;
    }
    if (board[i] == board6_1_3[i]) {
      count3++;
    }
    if (board[i] == board6_1_4[i]) {
      count4++;
    }
  }

  if (count1 == 9) {
    is6_1 = 9;
  }
  if (count2 == 9) {
    is6_1 = 7;
  }
  if (count3 == 9) {
    is6_1 = 3;
  }
  if (count4 == 9) {
    is6_1 = 1;
  }

  return is6_1;
}


int posWeight(int pos) {
  return weights[pos - 1];
}

//
boolean isCase3_1() {
  bool is3_1 = false;
  char board3_1_1[9] = {'o', '-', '-', '-', 'x', '-', '-', '-', 'o'};
  char board3_1_2[9] = {'-', '-', 'o', '-', 'x', '-', 'o', '-', '-'};

  int count1 = 0;
  int count2 = 0;
  for (int i = 0; i < 9; i++) {
    if (board[i] == board3_1_1[i]) {
      count1++;
    }
    if (board[i] == board3_1_2[i]) {
      count2++;
    }
  }

  if (count1 == 9 || count2 == 9) {
    is3_1 = true;
  }

  return is3_1;
}

//獲勝連線類型，是否包含該棋子位置
boolean winsHasPos(int whichWin, int pos) {
  for (int i = 0; i <= 2; i++) {
    if (wins[whichWin][i] == pos) {
      return true;
    }
  }
  return false;
}



//連線的最後一個棋
int theLastPos(int player, int whichWin) {
  for (int i = 0; i <= 2; i++) {
    if (lines[player][whichWin][i] == 0) {
      return wins[whichWin][i];
    }
  }
  return 0;
}

//棋格是否為空
boolean checkIsEmpty(int pos) {
  boolean empty = false;
  if (board[pos - 1] == '-') {
    empty = true;
  }
  return empty;
}

void checkIsWin() {
  for (int i = 0; i <= 7; i++) {
    int count = lines[player][i][0] + lines[player][i][1] + lines[player][i][2];
    if (count == 3) {
      isWin = true;
    }
  }

  if (isWin) {
    Serial.println((String("恭喜") + playerName[player] + String("獲勝！")));
    sumScore();
    reStart();
  } else if (checkIsFullBoard()) {
    Serial.println("平手！");
    sumScore();
    reStart();
  } else {
    //4、圈叉遊戲者互換
    changePlayer();
  }
}

void sumScore() {
  if (isWin) {
    if (player == 0) {
      //勝
      scores[0] = scores[0] + 1;
    } else {
      //負
      scores[1] = scores[1] + 1;
    }
  } else {
    //平手
    scores[2] = scores[2] + 1;
  }
  Serial.println("戰績統計：" + String(scores[0]) + "勝" + String(scores[1]) + "負" + String(scores[2]) + "和");
  delay(2000);
}

void setLines() {
  for (int i = 0; i <= 7; i++) {
    for (int j = 0; j <= 2; j++) {
      if (wins[i][j] == pos) {
        lines[player][i][j] = 1;
      }
    }
  }

  //showLines();
}

void showLines() {
  Serial.println("Lines：");
  for (int i = 0; i <= 1; i++) {
    for (int j = 0; j <= 7; j++) {
      for (int k = 0; k <= 2; k++) {
        Serial.print(lines[i][j][k]);
        Serial.print(",");
      }
      Serial.println("");
    }
    Serial.println("");
  }
}

void setup()
{
  Serial.begin(9600);
  //提醒玩家開始下棋，顯示1~9位置的範例
  showSample();
}

void judge() {
  //儲存下棋位置
  setPosition();
  //設定每種連線棋子數
  setLines();
  //顯示五子棋所有位置
  showBoard();
  //判斷勝負
  checkIsWin();
}

void loop()
{
  //AI
  if (player == 1) {
    Serial.println(playerName[player] + "下棋中…");
    delay(1000);
    pos = autoAiPos();
    judge();
  }
  //玩家
  if (Serial.available() == 1) {
    //將圈叉存在棋盤裡
    //將char轉成整數，也可以寫成pos = Serial.read()- '0';
    pos = Serial.parseInt();
    //是否為1~9
    if (!(pos >= 1 && pos <= 9)) {
      Serial.println("錯誤！輸入的數字超過範圍，請重新下棋(輸入1~9)：");
      return;
    }
    //是否重複
    if (checkIsRepeat()) {
      Serial.println((String("錯誤！第") + String(pos) + String("格已經下過了，請重新下棋(輸入1~9)：")));
    } else {
      judge();
    }
  }
}
