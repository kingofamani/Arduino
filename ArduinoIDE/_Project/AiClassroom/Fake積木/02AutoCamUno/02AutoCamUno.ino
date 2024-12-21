//Generated Date: Sat, 21 Dec 2024 03:55:33 GMT

#include <SoftwareSerial.h>
SoftwareSerial softSerial(7, 4);

int TRASH_POSITION = 600;
int PLANT_POSITION = 1320;
boolean isMoveTrashCam = false;
boolean isMovePlantCam = false;

void setup()
{
  softSerial.begin(9600);
  delay(10);
  Serial.begin(9600);

  //設定垃圾桶、馬達移動位置
  //是否開始垃圾桶、植物拍照
}

void loop()
{
  //2、開始移動鏡頭
  //鏡頭移動至垃圾桶
  if (isMoveTrashCam == true) {
    if (0 == TRASH_POSITION) {
      delay(5000);
      //3、通知UNO,開始拍照
      softSerial.print("START_TRASH_CAM");
      isMoveTrashCam = false;
      delay(3000);
    }
  }
  //鏡頭移動至植物
  if (isMovePlantCam == true) {
    if (0 == PLANT_POSITION) {
      delay(5000);
      //3、通知UNO,開始拍照
      softSerial.print("START_PLANT_CAM");
      isMoveTrashCam = false;
      delay(3000);
    }
  }
//1、接收來自ESP32訊息：準備拍照
if (softSerial.available()) {
  String serialMsg = "";
  while (softSerial.available()) {
    serialMsg = softSerial.readString();
    if ((serialMsg) == "STANDBY_TRASH_CAM") {
    isMoveTrashCam = true;
  } else if ((serialMsg) == "STANDBY_PLANT_CAM") {
    isMovePlantCam = false;
  }
  }
}

}
