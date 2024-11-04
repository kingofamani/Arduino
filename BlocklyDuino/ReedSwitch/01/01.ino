//Generated Date: Mon, 23 Oct 2023 01:48:45 GMT



void setup()
{
  Serial.begin(9600);


  pinMode(2, INPUT);
}

void loop()
{
  Serial.println(digitalRead(2));
  delay(1000);
}
