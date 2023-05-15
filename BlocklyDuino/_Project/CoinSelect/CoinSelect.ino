//Generated Date: Mon, 15 May 2023 04:29:09 GMT



void setup()
{
  Serial.begin(9600);


}

void loop()
{
  Serial.println(analogRead(A0));
  Serial.println(analogRead(A1));
  Serial.println(analogRead(A2));
  Serial.println("");
  delay(100);
}
