/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 26 Oct 2020 04:00:32 GMT
 */



int names[] = {"加菲貓", "蝙蝠俠", "米奇老鼠", "史努比", "忍者龜"};

int i;

void setup()
{
  Serial.begin(9600);

  for (i = 0; i <= 4; i++) {
    Serial.println((names[i]));
  }
}


void loop()
{

}