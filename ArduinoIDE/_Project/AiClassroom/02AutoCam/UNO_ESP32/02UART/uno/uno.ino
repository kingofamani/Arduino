//Generated Date: Mon, 16 Dec 2024 02:45:11 GMT

#include <SoftwareSerial.h>
SoftwareSerial softSerial(7, 4);

void setup()
{
  softSerial.begin(9600);
  delay(10);

  Serial.begin(9600);

}

void loop()
{
  if (Serial.available()) {
     softSerial.print((Serial.readString()));
  }
   if (softSerial.available()) {
    String serialMsg = "";
    while (softSerial.available()) {
      serialMsg = softSerial.readString();
      Serial.println((serialMsg));
    }
  }
}
