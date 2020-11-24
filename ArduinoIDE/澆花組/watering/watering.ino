#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

float lowTemp = 0;
float highTemp = 0;

void setup() {
  Serial.begin(9600); 
  
  pinMode(7,OUTPUT); //繼電器的接腳

  // initialize the lcd
  /*
  lcd.init();                       
  lcd.backlight();
  lcd.setCursor(2,0);
  lcd.print("Welcome!");
  lcd.setCursor(2,1);
  lcd.print("Ann's Garden");
  */
}

void loop() {
  //澆花
  delay(300);  //延遲時間，可自行調整
  int sensorValue = analogRead(A0); //土壤濕度感測器的接腳，讀取數值
  sensorValue = 1023 - sensorValue;
  sensorValue = map(sensorValue,0,1023,0,999);
  float percentVaule = sensorValue/10;
  Serial.println(analogRead(A0));
  Serial.print(percentVaule,1);
  Serial.println("%");
  if(percentVaule < 50){   //判斷是不是太乾燥了。600只是參考值，可依不同環境及土壤，設定不同的數值。
    digitalWrite(7,HIGH);   //如果太乾燥，就啟動抽水泵給水
  }else{
    digitalWrite(7,LOW);    //如果濕度夠了就停止給水
  }

/*
  //更新最高與最低濕度
  if(percentVaule < lowTemp){
    lowTemp = percentVaule;
  }
  if(percentVaule > highTemp){
    highTemp = percentVaule;
  }

  //LCD顯示
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Now Temp:");
  lcd.print(percentVaule);
  lcd.print("%");
  lcd.setCursor(0,1);
  //lcd.print("Low:");
  lcd.print(lowTemp);
  lcd.print("%~");
  //lcd.print("High:");
  lcd.print(highTemp);
  lcd.print("%");
  */
}
