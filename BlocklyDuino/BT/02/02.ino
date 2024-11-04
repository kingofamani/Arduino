/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 28 Nov 2022 04:03:58 GMT
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
  Serial.println("開機hello");
  sendToBtDevice("I am arduino");
  pinMode(LED_BUILTIN, OUTPUT);
}


void loop()
{
  if (Serial.available() == 1) {
    String myMsg = (Serial.readString());
    Serial.println((String("傳至藍牙裝置(手機)←")+String(myMsg)));
    sendToBtDevice(myMsg);
  }
  if (BtDevice.available()) {
    String btMsg = (BtDevice.readString());
    Serial.println((String("從藍牙裝置(手機)傳來→")+String(btMsg)));
    if (btMsg == "1") {
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println((String("從藍牙裝置(手機)傳來→")+String(btMsg)+String(" ON燈")));
    } else if (btMsg == "0") {
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println((String("從藍牙裝置(手機)傳來→")+String(btMsg)+String(" OFF燈")));
    }
  }
}