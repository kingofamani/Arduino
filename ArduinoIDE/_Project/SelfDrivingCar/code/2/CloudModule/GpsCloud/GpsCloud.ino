//Generated Date: Fri, 22 Dec 2023 00:30:44 GMT

#include "arduino_secrets.h"
 #include "thingProperties.h"
 //=====變數設定 Start=====
   //UART
  #define U1RXD 16
  #define U1TXD 17
//=====變數設定 End=====
 double  Lats[4][6]={
   {22.6364582999265,22.6364582999265,22.6364582999265,22.6364582999265,22.6364582999265,22.6364582999265},
   {22.6349390408069,22.6349390408069,22.6349390408069,22.6349390408069,22.6349390408069,22.6349390408069},
   {22.6334197816872,22.6334197816872,22.6334197816872,22.6334197816872,22.6334197816872,22.6334197816872},
   {22.6319005225676,22.6319005225676,22.6319005225676,22.6319005225676,22.6319005225676,22.6319005225676}
 };
 double  Longs[4][6]={
   {120.30257035839 , 120.304121598992, 120.305672839593 , 120.307224080195 , 120.308775320796 , 120.310326561398},
   {120.30257035839 , 120.304121598992, 120.305672839593 , 120.307224080195 , 120.308775320796 , 120.310326561398},
   {120.30257035839 , 120.304121598992, 120.305672839593 , 120.307224080195 , 120.308775320796 , 120.310326561398},
   {120.30257035839 , 120.304121598992, 120.305672839593 , 120.307224080195 , 120.308775320796 , 120.310326561398}
 };
 int carX = 0;
 int carY = 0;


void setup()
{
    Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, U1RXD, U1TXD);
  delay(1500);
  // Defined in thingProperties.h
  initProperties();
  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();


}

void loop()
{
  ArduinoCloud.update();
  String str = Serial2.readString();
    if(str !=""){
      carX = (int)(str.charAt(0) - '0');
      carY = (int)(str.charAt(1) - '0');
      Serial.println(carX);
      Serial.println(carY);
  coordinates = {Lats[carX][carY], Longs[carX][carY]};
}
  
}//end loop