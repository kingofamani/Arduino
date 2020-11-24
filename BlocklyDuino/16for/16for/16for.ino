/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 26 Oct 2020 07:37:40 GMT
 */



boolean prime;

int num;

int i;

void setup()
{
  Serial.begin(9600);

  prime = true;
  num = 997;
  int i_end = num - 1;
  for (i = 2;
      (2 <= i_end) ? i <= i_end : i >= i_end;
      i += (2 <= i_end) ? 1 : -1) {
    if (num % i == 0) {
      prime = false;
      break;

    }
  }
  if (prime == true) {
    Serial.println("質數");

  } else {
    Serial.println("不是質數");

  }
}


void loop()
{

}
