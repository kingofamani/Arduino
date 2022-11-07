/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 07 Nov 2022 05:21:48 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include <Servo.h>
#include <IRremote.h>
#include <Ultrasonic.h>

Servo __myservo3;
void openAndClose() {
  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  __myservo3.write(80);
  delay(3000);
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  __myservo3.write(0);
  delay(1000);
}

IRrecv irrecv(4);
decode_results results;
int count = 0;

Ultrasonic ultrasonic_8_9(8, 9);

Ultrasonic ultrasonic_5_6(5, 6);

void open() {
  __myservo3.write(80);
  delay(1000);
}

void close() {
  __myservo3.write(0);
  delay(1000);
}

void setup()
{
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  __myservo3.attach(3);
  Serial.begin(9600);

  irrecv.enableIRIn();
  __myservo3.write(0);
  delay(1000);
}


void loop()
{
  Serial.println(ultrasonic_8_9.convert(ultrasonic_8_9.timing(), Ultrasonic::CM));
  if (ultrasonic_5_6.convert(ultrasonic_5_6.timing(), Ultrasonic::CM) <= 20) {
    openAndClose();
  }
  if (irrecv.decode(&results)) {
      if (String(results.value, HEX) == "ff6897") {
      openAndClose();
    } else if (String(results.value, HEX) == "ff9867") {
      open();
    } else if (String(results.value, HEX) == "ffb04f") {
      close();
    }

    irrecv.resume();
  }
  if (ultrasonic_8_9.convert(ultrasonic_8_9.timing(), Ultrasonic::CM) <= 5) {
    count = count + 1;
    Serial.println(count);
    delay(100);
  }
}