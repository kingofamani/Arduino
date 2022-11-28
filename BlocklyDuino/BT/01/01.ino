/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 28 Nov 2022 04:03:43 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include <SoftwareSerial.h>

SoftwareSerial BtDevice(4, 5);
void sendToBtDevice(String myMsg) {
  BtDevice.println(myMsg);
}

void setup()
{
  Serial.begin(9600);

  BtDevice.begin(9600);
  Serial.println("HELLO");
  sendToBtDevice("hello");
}


void loop()
{
  //arduino輸入時
  if (Serial.available() == 1) {
    String myMsg = (Serial.readString());
    Serial.println((String("傳至藍牙裝置(手機)←")+String(myMsg)));
    //arduino→藍牙裝置(手機)
    sendToBtDevice(myMsg);
  }
  //藍牙裝置(手機)輸入時
  if (BtDevice.available()) {
    //藍牙裝置(手機)→arduino
    String btMsg = (BtDevice.readString());
    Serial.println((String("從藍牙裝置(手機)傳來→")+String(btMsg)));
  }
}