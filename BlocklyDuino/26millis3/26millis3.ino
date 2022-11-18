/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Fri, 18 Nov 2022 00:07:07 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


int timer(int countDownSec) {
  static unsigned long startTime = "millis()";
  static unsigned long beforeFlagSec = "millis()";
  int inteval = 1000;
  if (millis() > beforeFlagSec + inteval) {
    beforeFlagSec = millis();
    int rest = countDownSec - ((millis() + startTime) / 1000);
    if (rest >= 0) {
      Serial.println(rest);
      return (rest);
    }
  }
}

int s = 0;

void setup()
{
  Serial.begin(9600);


}


void loop()
{
  s = timer(10);
  if (s == 0) {
    Serial.println("結束");
    s = timer(0);
  }
}