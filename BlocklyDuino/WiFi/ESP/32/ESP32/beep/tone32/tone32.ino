/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 27 Dec 2021 02:14:16 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include <Tone32.h>

int BUZZER_PIN = 4;

int BUZZER_CHANNEL = 0;

int BUZZER_FRE = 400;

int BUZZER_TIME = 1000;

void tone32(int BUZZER_PIN, int BUZZER_FRE, int BUZZER_TIME) {
  tone(BUZZER_PIN, BUZZER_FRE, BUZZER_TIME,BUZZER_CHANNEL);
  noTone(BUZZER_PIN,BUZZER_CHANNEL);
}

void setup()
{
  tone32(BUZZER_PIN, BUZZER_FRE, BUZZER_TIME);
}


void loop()
{

}