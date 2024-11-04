//Generated Date: Sun, 03 Nov 2024 23:40:39 GMT

#include <SoftwareSerial.h>
SoftwareSerial softSerial(2, 3);

void setup()
{
  softSerial.begin(9600);
  delay(10);

  Serial.begin(9600);

}

void loop()
{
  //傳送OUT
  softSerial.print("test......(從UNO傳來)");
  delay(3000);
  //讀取IN
  if (softSerial.available()) {
    String serialMsg = "";
    while (softSerial.available()) {
      serialMsg = softSerial.readString();
      Serial.println((serialMsg));
    }
  }
}
