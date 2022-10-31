/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 31 Oct 2022 03:37:04 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include "HUSKYLENS.h"

HUSKYLENS huskylens;
int ID0 = 0;

int ID1 = 1;

int ID2 = 2;

int ID3 = 3;

int ID4 = 4;

int ID5 = 5;

int ReplyID = 0;

void printResult(HUSKYLENSResult result);
void initHL() {
  Wire.begin();
  while (!huskylens.begin(Wire))
  {     Serial.println(F("Begin failed!"));
  Serial.println(F("1.Please recheck the Protocol Type in HUSKYLENS (General Settings>>Protocol Type>>I2C)"));
  Serial.println(F("2.Please recheck the connection."));
  delay(100);
  }   huskylens.writeAlgorithm(ALGORITHM_OBJECT_RECOGNITION);
}

void startRecog() {
  if (huskylens.request())
  {
  HUSKYLENSResult result;
  if (huskylens.countBlocks(ID1) >= 1) {
  result = huskylens.getBlock(ID1, 0);
  } else if (huskylens.countBlocks(ID2) >= 1) {
  result = huskylens.getBlock(ID2, 0);
  } else if (huskylens.countBlocks(ID3) >= 1) {
  result = huskylens.getBlock(ID3, 0);
  } else if (huskylens.countBlocks(ID4) >= 1) {
  result = huskylens.getBlock(ID4, 0);
  } else if (huskylens.countBlocks(ID5) >= 1) {
  result = huskylens.getBlock(ID5, 0);
  } else {
  result = huskylens.getBlock(0, 0);
  }
  printResult(result);
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
  //訓練的ID
//辨識的ID

startRecog();
}