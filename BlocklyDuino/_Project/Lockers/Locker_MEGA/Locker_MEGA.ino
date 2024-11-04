/*
RC522 Uno/Nano  MEGA
IRQ   X       X
NSS   D10     D9
SCK   D13     D52
MOSI  D11     D51
MISO  D12     D50
GND   GND     GND
RST   D9      D8
VCC   5V      5V
*/

#include <SPI.h>
#include <RFID.h>

#define SDA_DIO 9
#define RESET_DIO 8
RFID RC522(SDA_DIO, RESET_DIO); 

String myId = "";
const int PIN_RELAY = 3;
bool isOpen = false;

void setup()
{ 
  Serial.begin(9600);
  pinMode(PIN_RELAY, OUTPUT);
  SPI.begin(); 
  RC522.init();
}

void loop()
{
  if (RC522.isCard())
  {
    myId = "";
    RC522.readCardSerial();
    //Serial.println("Card:");
    for(int i=0;i<5;i++)
    {
      myId += String(RC522.serNum[i]);
    }

    if (myId == "202155191111129") {
      Serial.println(myId + " 您好！");
      openDoor();
    } else {
      Serial.println("您沒有權限喔！");
    }
  }
  delay(1000);
}

void openDoor() {
  isOpen = !isOpen;
  if (isOpen) {    
    digitalWrite(PIN_RELAY, HIGH);
    Serial.println("Open開門");
  } else {    
    digitalWrite(PIN_RELAY, LOW);
    Serial.println("Close關門");
  }  
}
