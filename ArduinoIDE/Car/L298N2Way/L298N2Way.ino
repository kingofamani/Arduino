const int In1 = 4;
const int In2 = 5;
const int In3 = 6;      
const int In4 = 7;       
void setup(){
  Serial.begin(9600);
  
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);    
}
void loop(){
  mfront();
  Serial.println("前進");
  delay(2000);
  
  mstop();
  Serial.println("停止");
  delay(500);
  
  mback();
  Serial.println("後退");
  delay(2000);
  
  mstop();
  Serial.println("停止");
  delay(500);

  mright();
  Serial.println("右轉");
  delay(2000);

  mstop();
  Serial.println("停止");
  delay(500);

  mleft();
  Serial.println("左轉");
  delay(2000);
  
}
void mstop(){
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
}
void mfront(){
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
}
void mback(){
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
}

void mright(){
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
}
void mleft(){
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
}
