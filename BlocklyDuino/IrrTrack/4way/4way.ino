//Generated Date: Wed, 01 Nov 2023 01:47:14 GMT



void setup()
{
  Serial.begin(9600);


  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
}

void loop()
{
  Serial.println(digitalRead(4));
  Serial.println(digitalRead(5));
  Serial.println(digitalRead(6));
  Serial.println(digitalRead(7));
  Serial.println("-------");
  delay(100);
}
