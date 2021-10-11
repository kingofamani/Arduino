/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 05 Oct 2020 05:16:16 GMT
 */



void beep() {
  for (int count = 0; count < 80; count++) {
    digitalWrite(4, HIGH);
    delay(1);
    digitalWrite(4, LOW);
    delay(1);
  }
  digitalWrite(4, HIGH);
}

void setup()
{

  pinMode(4, OUTPUT);
}


void loop()
{
  beep();
  delay(2000);
}
