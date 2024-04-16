//Generated Date: Fri, 22 Sep 2023 02:24:55 GMT

#include "HUSKYLENS.h"
#include <Wire.h>
#include <Adafruit_INA219.h>
 
Adafruit_INA219 ina219;

HUSKYLENS huskylens;
int readData[5] = {};
byte dataType = 0;
byte idCount = 0;
bool detection_now = 0;

void setup()
{
  Serial.begin(9600);

  Wire.begin();
  while (!huskylens.begin(Wire)) {
    Serial.println(F("Begin failed!"));
    Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>I2C)"));
    Serial.println(F("2.Please recheck the connection."));
    delay(100);
  }

  huskylens.writeAlgorithm(ALGORITHM_OBJECT_RECOGNITION);

  if (! ina219.begin()) {
    Serial.println("Failed to find INA219 chip");
    while (1) { delay(10); }
  }
}

void loop()
{
  if (!huskylens.request()) {
    Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
  }
  else {
    if (huskylens.available()) {
      detection_now = true;
      HUSKYLENSResult result = huskylens.read();
      idCount = huskylens.countLearned();
      if (result.command == COMMAND_RETURN_BLOCK){
        dataType = 0;
        readData[0] = result.xCenter;
        readData[1] = result.yCenter;
        readData[2] = result.width;
        readData[3] = result.height;
        readData[4] = result.ID;
      }
      else if (result.command == COMMAND_RETURN_ARROW){
        dataType = 1;
        readData[0] = result.xOrigin;
        readData[1] = result.yOrigin;
        readData[2] = result.xTarget;
        readData[3] = result.yTarget;
        readData[4] = result.ID;
      }
      else {
        for (byte i=0; i<5; i++) {
          readData[i] = 0;
        }
      }
    }
    else {
      detection_now = false;
    }
  }
  if (detection_now) {
    Serial.println(readData[4]);
    Serial.println(readData[0]);
    Serial.println(readData[1]);
    Serial.println(readData[2]);
    Serial.println(readData[3]);
    Serial.println("");
  } else {
    Serial.println("沒有物體");
  }
  delay(200);

  //----------------------
  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;
  float power_mW = 0;
 
  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  power_mW = ina219.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  
  //電池電壓
  Serial.print("Bus Voltage:   "); Serial.print(busvoltage); Serial.println(" V");
  //Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage); Serial.println(" mV");
  //負載電壓
  Serial.print("Load Voltage:  "); Serial.print(loadvoltage); Serial.println(" V");
  //負載電流
  Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
  //負載功率
  Serial.print("Power:         "); Serial.print(power_mW); Serial.println(" mW");
  Serial.println("");
 
  delay(2000);
}
