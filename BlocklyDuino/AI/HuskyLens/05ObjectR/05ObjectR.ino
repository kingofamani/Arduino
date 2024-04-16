/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Tue, 29 Nov 2022 05:19:16 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include "HUSKYLENS.h"

HUSKYLENS huskylens;
int recValue = 100;

int countIDs[6] = {0, 0, 0, 0, 0, 0};

int IDs[6] = {0, 1, 2, 3, 4, 5};

int ReplyID = 0;

void printResult(HUSKYLENSResult result);
void initHL() {
  Wire.begin();
  while (!huskylens.begin(Wire))
  {     Serial.println(F("Begin failed!"));
  Serial.println(F("1.Please recheck the Protocol Type in HUSKYLENS (General Settings>>Protocol Type>>I2C)"));
  Serial.println(F("2.Please recheck the connection."));
  delay(100);
  }   huskylens.writeAlgorithm(ALGORITHM_OBJECT_CLASSIFICATION);
}

void startRecog() {
  if (huskylens.request())
  {
  HUSKYLENSResult result;
  //連續辨別成功次數
  for (int i = 0; i < sizeof(IDs) / sizeof(IDs[0]); i++) {
  if (huskylens.countBlocks(IDs[i]) >= 1) {
  countIDs[IDs[i]]++;
  }     }
  //判斷哪個ID達到閾值
  for (int i = 0; i < sizeof(countIDs) / sizeof(countIDs[0]); i++) {
  if (countIDs[i] >= recValue) {
  result = huskylens.getBlock(i, 0);
  printResult(result);
  //重置
  for (int j = 0; j < sizeof(countIDs) / sizeof(countIDs[0]); j++) {
  countIDs[j] = 0;
  }       }     }
  }   else   {
  Serial.println("失敗!無法從Huskylens請求物件!");
  }
}

void printResult(HUSKYLENSResult result) {
if (result.command == COMMAND_RETURN_BLOCK) {
Serial.println(String() + F("方框:X中心=") + result.xCenter + F(",Y中心=") + result.yCenter + F(",寬=") + result.width + F(",高=") + result.height + F(",ID=") + result.ID);
ReplyID = result.ID;
}
else {
Serial.println("未知的物體!");
}
}
void pR() {
}

void setup()
{
  Serial.begin(115200);

  initHL();
}


void loop()
{
  //物體識別閾值，連續識別正確次數
//訓練的ID
//辨識的ID

startRecog();
}