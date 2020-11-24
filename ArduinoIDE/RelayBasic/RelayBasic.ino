//byte test;

void setup() {
  Serial.begin(9600);  
   //test = analogRead(A0);
   //Serial.print("setup:");
   //erial.println(test);
  //pinMode(A0,INPUT);//水位偵測器
  pinMode(7,OUTPUT); //繼電器的接腳
  //delay(2000);
}

void loop() {  
  //Serial.print("loop:");
  Serial.println(analogRead(A0));
    if(analogRead(A0)>300){
      digitalWrite(7,LOW);
      Serial.println("倒滿水Full");
      Serial.println("馬達ON");
    }
    else{
      Serial.println("沒水了Empty");
      digitalWrite(7,HIGH);
      Serial.println("馬達OFF"); 
    }
    delay(2000);
    //test = !test;
}
