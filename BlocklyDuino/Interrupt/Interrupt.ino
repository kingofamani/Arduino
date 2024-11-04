/*
 * 立即中斷程式
 * UNO,Nano [D2 中斷代號0]、[D3 中斷代號1]
 * MEGA 中斷代號0~5的腳位依序：2,3,21,20,19,18
*/
unsigned char PIRPin = 2;

volatile boolean pirVal = 0;   //目前PIR狀態

void pirDetect_init() {

  pirVal = digitalRead(PIRPin);

}

void setup() {

  pinMode(PIRPin, INPUT);

  attachInterrupt(0, pirDetect_init, CHANGE); //注意, 0代表的是中斷編號,不是腳位哦！D2腳位的中斷編號為0, 所以此處需放0

  Serial.begin(9600);

}

void loop() {
  if (pirVal) Serial.println("有人!");//執行過這段，程式往下輪詢時，即使D2造成priVal改變，也不會執行印出"有人!"

  while(true){//雖然是無限loop，D2造成priVal改變時，會立即作用
    if(pirVal){
      Serial.println(".");
    }else{
      Serial.println("★");
    }
  }
  

}
