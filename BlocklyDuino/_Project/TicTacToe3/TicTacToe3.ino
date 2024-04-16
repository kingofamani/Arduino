/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Sun, 13 Mar 2022 04:36:25 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


char pos = '1';

char go = 'o';

char board[9] = {'-', '-', '-', '-', '-', '-', '-', '-', '-'};

int playerBoard[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

String wins[8] = {"123", "456", "789", "147", "258", "369", "159", "357"};

boolean isWin = false;

void setPlayerBoard() {
  int count = 0;
  for (int i = 0; i <= (sizeof(board)/sizeof(board[0])) - 1; i++) {
    if (board[i] == go) {
      playerBoard[count] = i + 1;
      count = count + 1;
    }
  }
  count = 0;
}

boolean checkIsRepeat() {
  boolean isRepeat = false;
  if (board[String(pos).toInt() - 1] != '-') {
    isRepeat = true;
  }
  return (isRepeat);
}

void showSample() {
  Serial.println((String("請玩家")+String(go)+String("開始下棋(輸入1~9)：")));
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
  Serial.println((String("您下的位置在")+String(pos)));
  board[String(pos).toInt() - 1] = go;
}

void checkIsWin() {
  for (int i = 0; i <= (sizeof(wins)/sizeof(wins[0])) - 1; i++) {
    int lineCount = 0;
    for (int k = 0; k <= (sizeof(playerBoard)/sizeof(playerBoard[0])) - 1; k++) {
      for (int j = 1; j <= 3; j++) {
        if (String((wins[i].charAt((j - 1)))).toInt() == playerBoard[k]) {
          lineCount = lineCount + 1;
        }
      }
    }
    if (lineCount == 3) {
      isWin = true;
    }
    lineCount = 0;
  }
  if (isWin) {
    Serial.println((String("恭喜玩家")+String(go)+String("獲勝！")));
    reStart();
  } else if (checkIsFullBoard()) {
    Serial.println("平手！");
    reStart();
  } else {
    //4、圈叉遊戲者互換
    changePlayer();
  }
}

void changePlayer() {
  if (go == 'o') {
    go = 'x';
  } else {
    go = 'o';
  }
  if (!isWin) {
    Serial.println("");
    Serial.println((String("請換玩家")+String(go)+String("下棋(輸入1~9)：")));
  }
}

void reStart() {
  Serial.println("");
  Serial.println("--------------新的一局----------------");
  //重置變數
  pos = '1';
  go = 'o';
  isWin = false;
  for (int i = 0; i <= 8; i++) {
    board[i] = '-';
  }
  for (int i = 0; i <= 8; i++) {
    playerBoard[i] = 0;
  }
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

void setup()
{
  Serial.begin(9600);

  //★若是用Arduino IDE序列埠視窗，一定要選取「沒有行結尾」
  //pos下棋的位置
  //go玩家(圈or叉)
  //board整個棋盤
  //playerBoard目前玩家下棋的所有位置
  //wins連線獲勝的8種情況
  //isWin是否連線獲勝
  //提醒玩家開始下棋，顯示1~9位置的範例
  showSample();
}


void loop()
{
  if (Serial.available() == 1) {
    //將圈叉存在棋盤裡
    pos = Serial.read();
    if (checkIsRepeat()) {
      Serial.println((String("錯誤！第")+String(pos)+String("格已經下過了，請重新下棋(輸入1~9)：")));
    } else {
      //清空目前玩家下棋的所有位置
      for (int i = 0; i <= 8; i++) {
        playerBoard[i] = 0;
      }
      //1、玩家下一棋
      setPosition();
      //2、顯示五子棋所有位置
      showBoard();
      //3、判斷勝負
      //3-1先取出目前遊戲者(圈or叉)下棋的位置
      setPlayerBoard();
      //3-2再判斷勝方
      checkIsWin();
    }
  }
}