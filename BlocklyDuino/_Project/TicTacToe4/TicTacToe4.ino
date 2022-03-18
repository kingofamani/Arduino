/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 14 Mar 2022 02:16:27 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


char pos = '1';

char go = 'o';
char goAI = 'x';
char who = go;

char board[9] = {'-', '-', '-', '-', '-', '-', '-', '-', '-'};

//每個位置的權重(中央1000,角100,邊10)
int weights[9]={100, 10, 100, 10, 1000, 10, 100, 10, 100};

String wins[8] = {"123", "456", "789", "147", "258", "369", "159", "357"};

boolean isWin = false;

int lines[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
int linesAI[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};



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
  board[String(pos).toInt() - 1] = who;
}

void changePlayer() {
  if (who == go) {
    who = goAI;
  } else {
    who = go;
  }
  if (!isWin) {
    Serial.println("");
    Serial.println((String("請換玩家")+String(who)+String("下棋(輸入1~9)：")));
  }
}

void reStart() {
  Serial.println("");
  Serial.println("--------------新的一局----------------");
  //重置變數
  pos = '1';
  who = go;
  isWin = false;
  for (int i = 0; i <= 8; i++) {
    board[i] = '-';
    playerBoard[i] = 0;
    playerBoardAI[i] = 0;
    lines[i] = 0;
    linesAI[i] = 0;
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

char autoAI() {
  char posAI = '0';
  /*
 * 1、AI連線
 * 2、阻止玩家連線
 * 3、阻止玩家雙聽牌
 *  3-1、AI=5,玩家=雙對角時，要下在權重10的邊，四個邊任選其一
 *  其他、阻止雙聽
 * 4、AI雙聽牌
 * 5、AI單聽牌
 * 6、找最大權重(中央1000,角100,邊10)
 *  6-1、AI=5,玩家=角時，要下在玩家角的對角
 *  6-2、AI=5,玩家=邊時，要下在玩家邊的兩角之一
 *  其他、找最大權重
 */

 //
  
}

void checkIsWin() {
  if(who==go){
    for (int i = 0; i <= (sizeof(lines)/sizeof(lines[0])) - 1; i++) {
      if(lines[i]==3){
        isWin = true;
      }
    }
  }else if(who==goAI{
    for (int i = 0; i <= (sizeof(linesAI)/sizeof(linesAI[0])) - 1; i++) {
      if(linesAI[i]==3){
        isWin = true;
      }
    }
  }  
  
  if (isWin) {
    Serial.println((String("恭喜玩家")+String(who)+String("獲勝！")));
    reStart();
  } else if (checkIsFullBoard()) {
    Serial.println("平手！");
    reStart();
  } else {
    //4、圈叉遊戲者互換
    changePlayer();
  }
}

void countLine() {
  int tempLines[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (int i = 0; i <= (sizeof(wins)/sizeof(wins[0])) - 1; i++) {
    int lineCount = 0;
    for (int j = 1; j <= 3; j++) {
      if (String((wins[i].charAt((j - 1)))).toInt() == pos) {
        lineCount = lineCount + 1;
      }
    }
    tempLines[i] = lineCount;
    lineCount = 0;
  }

  if(who==go){
    lines=tempLines;
  }else if(who==goAI{
    linesAI=tempLines;
  }
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
  //電腦判斷各連線累計棋子數(0~2)
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
      //1、玩家下一棋
      setPosition();
      countLine();
      //2、顯示五子棋所有位置
      showBoard();
      //3、判斷勝負
      
      //3-2再判斷勝方
      checkIsWin();
    }
  }
}
