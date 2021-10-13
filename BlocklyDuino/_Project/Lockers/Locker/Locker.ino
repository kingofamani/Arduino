/*
   Generated using BlocklyDuino:

   https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt

   Date: Thu, 22 Oct 2020 00:40:59 GMT
*/

#include <SPI.h>

#include <MFRC522.h>

String myId;

MFRC522 rfid(/*SS_PIN*/ 10, /*RST_PIN*/ UINT8_MAX);

const int PIN_RELAY = 3;
bool isOpen = false;

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

void setup()
{
  Serial.begin(9600);
  pinMode(PIN_RELAY, OUTPUT);

  SPI.begin();
  rfid.PCD_Init();

}


void loop()
{
  myId = mfrc522_readID();
  myId.toUpperCase();
  if ((myId.length()) > 0) {
    if (myId == "CA9BBF6F") {
      Serial.println(myId + " 您好！");
      openDoor();
    } else {
      Serial.println("您沒有權限喔！");
    }
  }
  delay(100);
}

void openDoor() {
  isOpen = !isOpen;
  if (isOpen) {    
    digitalWrite(PIN_RELAY, HIGH);
    delay(100);
    Serial.println("Open開門");
  } else {    
    digitalWrite(PIN_RELAY, LOW);
    delay(100);
    Serial.println("Close關門");
  }  
}
