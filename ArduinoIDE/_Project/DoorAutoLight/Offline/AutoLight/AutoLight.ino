//Generated Date: Sat, 27 Apr 2024 08:02:06 GMT

#include <Ultrasonic.h>

int lightSecs = 60;
Ultrasonic ultrasonic0(4, 16);

void setup()
{
  Serial.begin(9600);


  pinMode(5, OUTPUT);
}

void loop()
{
  if (ultrasonic0.convert(ultrasonic0.timing(), 1) < 80) {
    Serial.println(ultrasonic0.convert(ultrasonic0.timing(), 1));
    digitalWrite(5, HIGH);
    delay((lightSecs * 1000));
    digitalWrite(5, LOW);
  }
  delay(100);
}
