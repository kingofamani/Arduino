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
/* Include the RFID library */
#include <RFID.h>

/* Define the DIO used for the SDA (SS) and RST (reset) pins. */
#define SDA_DIO 9
#define RESET_DIO 8
/* Create an instance of the RFID library */
RFID RC522(SDA_DIO, RESET_DIO); 

String myId = "";

void setup()
{ 
  Serial.begin(9600);
  /* Enable the SPI interface */
  SPI.begin(); 
  /* Initialise the RFID reader */
  RC522.init();
}

void loop()
{
  /* Has a card been detected? */
  if (RC522.isCard())
  {
    myId = "";
    /* If so then get its serial number */
    RC522.readCardSerial();
    //Serial.println("Card:");
    for(int i=0;i<5;i++)
    {
      myId += String(RC522.serNum[i]);
    //Serial.print(RC522.serNum[i],DEC);
    //Serial.print(RC522.serNum[i],HEX); //to print card detail in Hexa Decimal format
    }
    //Serial.println();
    Serial.println(myId);
  }
  delay(100);
}
