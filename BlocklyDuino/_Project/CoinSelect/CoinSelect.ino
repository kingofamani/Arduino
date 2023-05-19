//Generated Date: Mon, 15 May 2023 04:29:09 GMT

const int UP_LDR_PIN = A2;
const int MID_LDR_PIN = A1;
const int DOWN_LDR_PIN = A0;

//上方光敏：沒有被遮蔽、遮一半、全遮時的亮度
const int UP_LDR_LIGHT[3] = {800, 100, 400};
//中間光敏：沒有被遮蔽、遮一半、全遮時的亮度
const int MID_LDR_LIGHT[3] = {800, 100, 400};
//下方光敏：沒有被遮蔽、遮一半、全遮時的亮度
const int DOWN_LDR_LIGHT[3] = {800, 100, 400};

/***
   硬幣被上、中、下3個光敏遮住的面積：
          上   中   下
   1元：  no    no  half
   5元：  no    no  all
   10元： no    all  all
   50元： half  all  all
*/
const int DOLLAR_1 = 0;
const int DOLLAR_5 = 1;
const int DOLLAR_10 = 2;
const int DOLLAR_50 = 3;
int coinsLight[4][3] = {
  {UP_LDR_LIGHT[0], MID_LDR_LIGHT[0], DOWN_LDR_LIGHT[1]},
  {UP_LDR_LIGHT[0], MID_LDR_LIGHT[0], DOWN_LDR_LIGHT[2]},
  {UP_LDR_LIGHT[0], MID_LDR_LIGHT[2], DOWN_LDR_LIGHT[2]},
  {UP_LDR_LIGHT[1], MID_LDR_LIGHT[2], DOWN_LDR_LIGHT[2]},
};

//偵測到的亮度
int upLight = 0;
int midLight = 0;
int downLight = 0;

//亮度允許±誤差值
const int TOL = 10;

void setup()
{
  Serial.begin(9600);


}

void loop()
{
  upLight = analogRead(UP_LDR_PIN);
  midLight = analogRead(MID_LDR_PIN);
  downLight = analogRead(DOWN_LDR_PIN);

  //Serial.println(whichCoin(upLight, midLight, downLight));


  Serial.print(upLight);
  Serial.print(" ");
  Serial.print(midLight);
  Serial.print(" ");
  Serial.println(downLight);
  Serial.println("");
  delay(10);
}

int whichCoin(int up, int mid, int down) {
  int coin = -1;
  //範圍
  for(int i=0;i<4;i++){
    bool isUpOk = ((coinsLight[i][0] - TOL <= up) && (up <= coinsLight[i][0] + TOL));
    bool isMidOk = ((coinsLight[i][1] - TOL <= mid) && (mid <= coinsLight[i][1] + TOL));
    bool isDownOk = ((coinsLight[i][2] - TOL <= down) && (down <= coinsLight[i][2] + TOL));
    if(isUpOk&&isMidOk &&isDownOk){
      coin=i;
    }
  }
  return coin;    
}
