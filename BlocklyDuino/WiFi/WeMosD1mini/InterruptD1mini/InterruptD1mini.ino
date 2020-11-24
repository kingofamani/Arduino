/*
 * 立即中斷程式
 * UNO,Nano [D2 中斷代號0]、[D3 中斷代號1]
 * MEGA 中斷代號0~5的腳位依序：2,3,21,20,19,18
*/
unsigned char PIRPin = 13;//D1 mini 13腳位表示D7

volatile boolean pirVal = 0;   //目前PIR狀態

//★D1 mini要加 ICACHE_RAM_ATTR
ICACHE_RAM_ATTR void pirDetect_init() {

  pirVal = digitalRead(PIRPin);

}

void setup() {

  pinMode(PIRPin, INPUT);
  //digitalPinToInterrupt可將腳位轉成 中斷代號
  attachInterrupt(digitalPinToInterrupt(PIRPin), pirDetect_init, CHANGE); 

  Serial.begin(9600);

}

void loop() {
  while(true){
    if(pirVal){
      Serial.println(".");
    }else{
      Serial.println("★");
    }
    delay(10);//D1 mini要加delay，否則太快會跳error log
  }
  

}
