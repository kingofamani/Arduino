/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 14 Mar 2022 03:48:28 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


int ans = 0;

String num = "";

int count = 0;

int best = 999;

void checkIsBest() {
  Serial.println((String("你總共猜了")+String(count)+String("次。")));
  if (count < best) {
    Serial.println((String("恭喜！你破紀錄了，你只用")+String(count)+String("次，就猜中了！")));
    best = count;
  } else {
    Serial.println((String("可惜！你沒有破最佳紀錄，目前最快紀錄是")+String(best)+String("次。")));
  }
}

void reStart() {
  Serial.println("");
  Serial.println("-------------新的一局-------------");
  ans = random(1, 100);
  num = "";
  count = 0;
  Serial.println("請猜答案(1~99)：");
}

void setup()
{
  Serial.begin(9600);

  /*
    讀取序列埠會大於1個字元(1~99)，
     所以不適合用char，要用String。
     也不能直接用「讀取序列埠」積木，要用Serial.readString()
  */
  randomSeed(analogRead(0));
  //ans電腦自動產生答案
  //★絕對不能在「初始化」就產生亂數，否則會永遠一樣。要在「重複執行」產生亂數。
  //num玩家輸入的值
  //count總共猜了幾次
  //best最佳成績(猜最少的次數)
  Serial.println("請猜答案(1~99)：");
}


void loop()
{
  if (ans == 0) {
    ans = random(1, 100);
  }
  if (Serial.available() == 1) {
    count = count + 1;
    num = Serial.readString();
    if ((num.toInt()) == ans) {
      Serial.println((String("恭喜你猜對了，答案就是：")+String(ans)));
      checkIsBest();
      reStart();
    } else if ((num.toInt()) > ans) {
      Serial.println((String(num)+String("太大了，再小一點：")));
    } else {
      Serial.println((String(num)+String("太小了，再大一點：")));
    }
  }
}