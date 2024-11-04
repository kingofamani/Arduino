//Generated Date: Mon, 04 Dec 2023 00:15:25 GMT



int i = 1;

void setup()
{
  Serial.begin(9600);

  while (i <= 10) {
    Serial.println((String(i)+String("德音")));
    i = i + 1;
  }
}

void loop()
{

}
