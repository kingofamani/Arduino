/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 07 Nov 2022 03:53:16 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include <IRremote.h>
#include <Servo.h>
#include <Ultrasonic.h>

IRrecv irrecv(4);
decode_results results;
Servo __myservo3;
Ultrasonic ultrasonic_5_6(5, 6);

void setup()
{
  Serial.begin(9600);

  irrecv.enableIRIn();
  __myservo3.attach(3);
  __myservo3.write(0);
  delay(1000);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}


void loop()
{
  if (ultrasonic_5_6.convert(ultrasonic_5_6.timing(), Ultrasonic::CM) <= 20) {
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
    __myservo3.write(130);
    delay(3000);
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    __myservo3.write(0);
    delay(1000);
  }
  if (irrecv.decode(&results)) {
      if (String(results.value, HEX) == "ff6897") {
      digitalWrite(11, LOW);
      digitalWrite(12, HIGH);
      digitalWrite(13, LOW);
      __myservo3.write(130);
      delay(3000);
      digitalWrite(11, HIGH);
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
      __myservo3.write(0);
      delay(1000);
    }

    irrecv.resume();
  }
}