/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Wed, 07 Dec 2022 23:58:42 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


String msgs[3] = {"隊友快來carry我！", "快贏了~他們太弱了吧！", "要不要再組隊一次啊？"};

int key = 0;

void setup()
{
  Serial.begin(9600);


}


void loop()
{
  if (Serial.available() == 1) {
    key = Serial.parseInt();
    Serial.println((msgs[key - 1]));
  }
}