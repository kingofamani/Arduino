void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(7,INPUT);
  pinMode(3,OUTPUT);
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  int water=digitalRead(7);
  Serial.println(water);
  if(water==0){
    digitalWrite(3,HIGH);
    delay(20000);
  }else{
    digitalWrite(3,LOW);
  }
  delay(100);
}
