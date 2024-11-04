/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Wed, 17 Mar 2021 06:44:58 GMT
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>

#include <MFRC522.h>

String name;

String myId;

boolean faceYes;

boolean faceNo;

int flag;

LiquidCrystal_I2C lcd(0x27,16,2);
void LCM1602_0() {
}

void LCM1602_1() {
  //螢幕不能顯示中文
  lcd.init();
  lcd.backlight();
}

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

void hello() {
  digitalWrite(8, LOW);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Hello~ Please");
  lcd.setCursor(0,1);
  lcd.print("Sense Your Card");
}

void setup()
{
  Serial.begin(9600);

  name = "";
  LCM1602_1();
  hello();
  //pinMode(2, INPUT_PULLUP);
  //pinMode(4, INPUT_PULLUP);
  SPI.begin();
  rfid.PCD_Init();

  pinMode(8, OUTPUT);
  pinMode(2, INPUT);
  pinMode(4, INPUT);
}


void loop()
{
  myId = mfrc522_readID();
  if ((myId.length()) > 0) {
    myId.toUpperCase();
    Serial.println(myId);
    if (myId == "CA9BBF6F") {
      name = "eric";

    } else if (myId == "E92F52B3") {
      name = "sam";
    } else {
      name = "stranger";

    }
    if (name == "stranger") {
      Serial.println("你誰啊你");
      lcd.clear();
      lcd.print("who are you?");

    } else {
      if (flag == 0) {
        digitalWrite(8, HIGH);
        Serial.println("歡迎");
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Hello");
        lcd.setCursor(0,1);
        lcd.print(name);
        flag = 1;

      } else {
        digitalWrite(8, LOW);
        Serial.println("再見");
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("see you again");
        lcd.setCursor(0,1);
        lcd.print(name);
        flag = 0;

      }

    }

  }
  /*
    臉部辨識
  */
  faceYes = digitalRead(2);
  faceNo = digitalRead(4);
  if (faceYes == true && faceNo == false) {
    Serial.println("人臉辨識系統！主人回來了");
    digitalWrite(8, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Face AI");
    lcd.setCursor(0,1);
    lcd.print("BOSS come home");
    delay(15000);
    hello();

  }
  delay(500);
}