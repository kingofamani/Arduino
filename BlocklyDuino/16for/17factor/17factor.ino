/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Wed, 09 Dec 2020 00:34:49 GMT
 */



String num;

int number;

String factor;

int i;

void setup()
{
  Serial.begin(9600);

  num = "2000";
  number = (num.toInt());
  factor = "";
  for (i = 1;
      (1 <= number) ? i <= number : i >= number;
      i += (1 <= number) ? 1 : -1) {
    if (number % i == 0) {
      factor = String() + factor + i + ",";

    }
  }
  Serial.println(factor);
}


void loop()
{

}
