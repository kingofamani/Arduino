#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

String data1;  
  
void setup()  
{  
  Serial.begin(9600);  
  pinMode(2,OUTPUT);  
  Serial.println("cmd=upload&device_name=arduino&data=126&uid=kingofamani&key=f050573271c8eb57f619f41166133bd1");  
  Serial.flush();  
  delay(1000);  
    Serial.println("cmd=subscribe&topic=kingofamani");      
}  
  void loop()  
  {  
    if (Serial.available() > 0)    
    {  
      data1 = String(Serial.readString());  
      delay(5);  
    
      if (data1.indexOf("LEDon")>0)  
      {  
        Serial.println("LED ON");  
        digitalWrite(2, HIGH);  
      }  
      if (data1.indexOf("LEDoff")>0)  
      {  
        Serial.println("LED OFF");  
        digitalWrite(2, LOW);  
      }  
    
    }    
  } 
