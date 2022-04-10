#include "HUSKYLENS.h"

HUSKYLENS huskylens;
//HUSKYLENS green line >> SDA; blue line >> SCL
int ID0 = 0;
int ID1 = 1;
int ID2 = 2;
int ID3 = 3;
int ID4 = 4;
int ID5 = 5;

int AnsID = 0;
int ReplyID = 0;//使用者舉牌

void printResult(HUSKYLENSResult result);

void setup() {
  Serial.begin(115200);
  //初始HuskyLens
  Wire.begin();
  while (!huskylens.begin(Wire))
  {
    Serial.println(F("Begin failed!"));
    Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>I2C)"));
    Serial.println(F("2.Please recheck the connection."));
    delay(100);
  }

  huskylens.writeAlgorithm(ALGORITHM_OBJECT_RECOGNITION);

  //亂數
  randomSeed(analogRead(0));

}

void loop() {
  if (AnsID == 0) {
    AnsID = random(1, 6);
    Serial.println(String() + "答案是：" + AnsID);
  }

  if (huskylens.request())
  {
    Serial.println("###################################");
    //Serial.println(String() + F("訓練總數量 IDs:") + huskylens.countLearnedIDs());

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

    if (ReplyID == AnsID) {
      Serial.println("答對了！");
      delay(5000);
      //重新開始
      Serial.println("################重新開始###################");
      AnsID = random(1, 6);
      Serial.println(String() + "答案是：" + AnsID);
    } else {
      Serial.println(String() + "錯誤！答案是：" + AnsID + "。請再拿其他卡片試試看：");
    }

  }
  else
  {
    Serial.println("Fail to request objects from Huskylens!");
  }
  delay(1000);
}

void printResult(HUSKYLENSResult result) {
  if (result.command == COMMAND_RETURN_BLOCK) { //result is a block
    Serial.println(String() + F("方框:X中心=") + result.xCenter + F(",Y中心=") + result.yCenter + F(",寬=") + result.width + F(",高=") + result.height + F(",ID=") + result.ID);
    ReplyID = result.ID;
  }
  //    else if (result.command == COMMAND_RETURN_ARROW){//result is an arrow
  //        Serial.println(String()+F("Arrow:xOrigin=")+result.xOrigin+F(",yOrigin=")+result.yOrigin+F(",xTarget=")+result.xTarget+F(",yTarget=")+result.yTarget+F(",ID=")+result.ID);
  //    }
  else { //result is unknown.
    Serial.println("xx未知的物體!");
  }
}
