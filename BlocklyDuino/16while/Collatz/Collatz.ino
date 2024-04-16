//Generated Date: Mon, 04 Dec 2023 00:04:41 GMT



unsigned long Num = 6171;

void setup()
{
  Serial.begin(9600);

  Serial.println(Num);
  while (!(Num == 1)) {
    if (Num % 2 == 0) {
      Num = Num / 2;
    } else {
      Num = (Num * 3) + 1;
    }
    Serial.println(Num);
  }
}

void loop()
{

}
