/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 26 Oct 2020 03:34:41 GMT
 */



int score[] = {79, 95, 100, 99, 50};

int i;

void setup()
{
  Serial.begin(9600);

  for (i = 0; i <= 4; i++) {
    Serial.println((score[i]));
  }
}


void loop()
{

}