/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 28 Sep 2020 06:09:04 GMT
 */

#include <SPI.h>

#include <MFRC522.h>

#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include "U8glib.h"
#include <Ultrasonic.h>
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

String myId;

int distance;

float amb;

float obj;

MFRC522 rfid(/*SS_PIN*/ 10, /*RST_PIN*/ UINT8_MAX);

String mfrc522_readID()
{
  String ret;
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial())
  {
    MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);

    for (byte i = 0; i < rfid.uid.size; i++) {
      ret += (rfid.uid.uidByte[i] < 0x10 ? "0" : "");
      ret += String(rfid.uid.uidByte[i], HEX);
    }
  }

  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
  return ret;
}

void myRFID() {
  myId = mfrc522_readID();
  myId.toUpperCase();
  if ((myId.length()) > 0) {
    Serial.println(myId);
    beep();

  }
  delay(100);
}

Adafruit_MLX90614 mlx;
void myMLX90614_0() {
}

void myMLX90614_1() {
  Serial.println("測試");
  mlx = (Adafruit_MLX90614());
  mlx.begin();
}

void myMLX90614_2() {
  Serial.print("室溫= ");
  Serial.print((mlx.readAmbientTempC()));
  Serial.println("*C");
  Serial.print("體溫= ");
  Serial.print((mlx.readObjectTempC()));
  Serial.println("*C");
  Serial.println("");
  delay(500);
}

U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE); // I2C / TWI ;
void myOLED_1() {
  //正式寫專案時,要將amb及obj預設值刪除
  amb = 0;
  obj = 0;
}

void myOLED_2() {
  //正式寫專案時,將環境溫度及體溫傳入amb,obj
  amb=mlx.readAmbientTempC();
  obj=mlx.readObjectTempC();
  u8g.firstPage();
  do {
  draw();
  } while ( u8g.nextPage() );
  delay(100);
}

void draw() {
  u8g.setFont(u8g_font_fur25);
  u8g.setPrintPos(10, 29);
  u8g.print(amb, 1);
  u8g.drawStr( 80, 29, "*C");
  u8g.setPrintPos(10, 63);
  u8g.print(obj, 1);
  u8g.drawStr( 80, 63, "*C");
}
DFRobotDFPlayerMini myDFPlayer;
/*安裝Ultrasonic by ErickSimoes的函式庫*/
Ultrasonic ultrasonic(5, 6);//(Trig,Echo)
void HCSR04_0() {
}

void HCSR04_2() {
  distance = (ultrasonic.read());
  if (distance < 50) {
    Serial.print("距離：");
    Serial.print(distance);
    Serial.println(" cm");
    myDFPlayer.play(1);

  }
}

void beep() {
  for (int count = 0; count < 80; count++) {
    digitalWrite(4, LOW);
    delay(1);
    digitalWrite(4, HIGH);
    delay(1);
  }
  digitalWrite(4, HIGH);
}

SoftwareSerial mySoftwareSerial(7, 8);

void myMP3_0() {
}

void myMP3_1() {
  /*
    將myDFPlayer.play(1);註解，否則會一直repeat
  */
  mySoftwareSerial.begin(9600);
  if (!(myDFPlayer.begin(mySoftwareSerial))) {
    while (true) {
    }

  }
  myDFPlayer.volume(10);
  //myDFPlayer.play(1);
}

void myMP3_2() {
  /*
    此區塊不放入loop，待需要時再用，
    可用myDFPlayer.play(n);不要再用myDFPlayer.next();
  */
  delay(3000);
  myDFPlayer.next();
}

void setup()
{
  Serial.begin(115200);

  myMLX90614_1();
  myMP3_1();
  SPI.begin();
  rfid.PCD_Init();

  pinMode(4, OUTPUT);
}


void loop()
{
  myRFID();
  myMLX90614_2();
  myOLED_2();
  HCSR04_2();
}
