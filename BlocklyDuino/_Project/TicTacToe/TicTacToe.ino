/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Sun, 13 Mar 2022 01:12:12 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


char pos = '1';

char go = 'o';

char board[9] = {'-', '-', '-', '-', '-', '-', '-', '-', '-'};

String wins[8] = {"123", "456", "789", "147", "258", "369", "159", "357"};

void setup()
{
  Serial.begin(9600);

  //pos下棋的位置
  //go玩家(圈or叉)
  //board整個棋盤
  //wins連線獲勝的8種情況
  Serial.println((String("請玩家")+String(go)+String("開始下棋(輸入1~9)：")));
}


void loop()
{
  if (Serial.available() == 1) {
    //1、玩家下一棋
    //playerBoard目前玩家下棋的所有位置
    int playerBoard[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    pos = Serial.read();
    Serial.println(pos);
    board[String(pos).toInt() - 1] = go;
    //2、顯示五子棋所有位置
    for (int i = 0; i <= 8; i++) {
      Serial.print((board[i]));
      Serial.print(",");
      if ((i + 1) % 3 == 0) {
        Serial.println("");
      }
    }
    //3、判斷勝負
    //3-1先取出目前遊戲者(圈or叉)下棋的位置
    int count = 0;
    for (int i = 0; i <= (sizeof(board)/sizeof(board[0])) - 1; i++) {
      if (board[i] == go) {
        playerBoard[count] = i + 1;
        count = count + 1;
      }
    }
    count = 0;
    //isWin是否連線獲勝
    boolean isWin = false;
    //3-2再判斷勝方
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
    }
    //4、圈叉遊戲者互換
    if (go == 'o') {
      go = 'x';
    } else {
      go = 'o';
    }
    if (!isWin) {
      Serial.println((String("請換玩家")+String(go)+String("下棋(輸入1~9)：")));
    }
  }
}