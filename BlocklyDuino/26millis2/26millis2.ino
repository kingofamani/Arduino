/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Tue, 08 Nov 2022 01:46:13 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


int secs = 0;

void startCountDown() {
}

int durationSecs(null, int secs) {
  static int startTime= millis();
  int duration = (round((millis()-startTime)/1000));
}

void setup()
{
  Serial.begin(9600);


}


void loop()
{
  Serial.println(millis());
  secs = round(millis() / 1000);
  Serial.print("目前時間：");
  Serial.println(secs);
  delay(1000);
}