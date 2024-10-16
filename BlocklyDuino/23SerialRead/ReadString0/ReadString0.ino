//Generated Date: Tue, 15 Oct 2024 23:56:16 GMT



void setup()
{
  Serial.begin(9600);


}

void loop()
{
  if (Serial.available()) {
     Serial.println((Serial.readString()));
  }
}
