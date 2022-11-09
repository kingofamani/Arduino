/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Wed, 09 Nov 2022 04:00:44 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


int startTime = 0;

int beforeFlagSec = 0;

int startCountDown(int secs) {
  if (startTime == 0) {
    startTime = millis();
    beforeFlagSec = startTime;
  }
  if (startTime != 0) {
    if ((millis()) > startTime + (secs * 1000)) {
      startTime = 0;
      beforeFlagSec = 0;
      return (0);
    } else if ((millis()) > beforeFlagSec + 1000) {
      beforeFlagSec = millis();
      return (round((beforeFlagSec-startTime)/1000));
    }
  }
}

float durationSecs(int item, int secs) {
  static int startTime= millis();
  float duration = (round((millis()-startTime)/1000));
  if (item == 1) {
    //正數計時
    Serial.print((millis()));
    Serial.print("、");
    Serial.print((startTime));
    Serial.print("、");
    Serial.print(((millis()-startTime)/1000));
    Serial.print("、");
    Serial.print((round((millis()-startTime)/1000)));
    Serial.print("、");
    Serial.println(duration);
    return (duration);
  } else if (item == 2) {
    //倒數計時
    return (secs - duration);
  }
}

void setup()
{
  Serial.begin(9600);


}


void loop()
{
  delay(2000);
  Serial.println((startCountDown(10)));
}