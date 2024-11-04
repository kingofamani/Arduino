/*
  SD card basic file example

  This example shows how to create and destroy an SD card file
  The circuit:
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

  created   Nov 2010
  by David A. Mellis
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

*/
#include <SPI.h>
#include <SD.h>

//CS的腳位可自訂(目前設為10)
#define SDCARD_SS_PIN 10

File myFile;

void setup() {
  Serial.begin(9600);
  while (!Serial) {;}

  if (!SD.begin(SDCARD_SS_PIN)) {
    Serial.println("記憶卡讀取失敗!");
    while (1);
  }

  //新增(or開啟)檔案
  myFile = SD.open("test.txt", FILE_WRITE);

  //寫入內容
  if (myFile) {
    myFile.print("德音國小創客：");
    myFile.println("SD Card記憶卡練習");
    myFile.close();
  } else {
    Serial.println("無法寫入 test.txt");
  }

  //讀取內容
  myFile = SD.open("test.txt");
  String dein = "";
  if (myFile) {
    while (myFile.available()) {
      dein += (char)myFile.read();
    }
    Serial.println(dein);
    myFile.close();
  } else {
    Serial.println("無法讀取 test.txt");
  }

}

void loop() {

}
