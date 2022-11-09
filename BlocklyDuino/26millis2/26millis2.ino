/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Wed, 09 Nov 2022 02:03:51 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


int secs = 20;

float durs = 0;

void startCount() {
  Serial.print("目前時間：");
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

  delay(2000);
}


void loop()
{
  durs = durationSecs(1, secs);
  Serial.println(durs);
  delay(500);
}