const int max471_out_pin = A1;

int RawValue= 0;
float Current = 0;

void setup(){   
  pinMode(max471_out_pin, INPUT);
  Serial.begin(9600);
}

void loop(){  
  RawValue = analogRead(max471_out_pin); 
  Current = (RawValue * 5.0 )/ 1024.0; // scale the ADC         
  Serial.print("Current = ");      
  Serial.print(Current,3); //3 digits after the decimal point
  Serial.println(" amps DC"); //3 digits after the decimal point    
  delay(500);  
}