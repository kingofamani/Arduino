/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Thu, 07 Jan 2021 01:53:17 GMT
 */

#include <SPI.h>
#include <RFID.h>

String myId;

int  i;

#define SDA_DIO 9
#define RESET_DIO 8
RFID RC522(SDA_DIO, RESET_DIO);
void R0() {
  myId = "";
}

void setup()
{
  Serial.begin(9600);

  SPI.begin();
  RC522.init();
}


void loop()
{
  if (RC522.isCard())
  {
  myId = "";
  RC522.readCardSerial();
  for (i = 0; i <= 4; i++) {
    myId += String(RC522.serNum[i]);
  }
  //從這裡開始改程式：
  Serial.println(myId);
  }//end if
  delay(100);
}