//Generated Date: Mon, 09 Dec 2024 02:05:58 GMT

#include <Wire.h>
#include <INA226_WE.h>

#define I2C_ADDRESS 0x40

/* There are several ways to create your INA226 object:
 * INA226_WE ina226 = INA226_WE(); -> uses I2C Address = 0x40 / Wire
 * INA226_WE ina226 = INA226_WE(I2C_ADDRESS);
 * INA226_WE ina226 = INA226_WE(&Wire); -> uses I2C_ADDRESS = 0x40, pass any Wire Object
 * INA226_WE ina226 = INA226_WE(&Wire, I2C_ADDRESS);
 */
INA226_WE ina226 = INA226_WE(I2C_ADDRESS);

#include <SimpleTimer.h>
SimpleTimer timer;

float fan_mW = 0;

void setup()
{
  Wire.begin();
  if(!ina226.init()){
    Serial.println("Failed to init INA226. Check your wiring.");
    while(1){}
  }
  ina226.waitUntilConversionCompleted(); //if you comment this line the first data might be zero

  Serial.begin(9600);

  pinMode(8, OUTPUT);
  ina226.powerUp();
  Serial.println(ina226.init());
  digitalWrite(8, HIGH);
  timer.setInterval(60000, timerFunc0);

}

void loop()
{
  timer.run();

}

void timerFunc0(){
   fan_mW = (ina226.getShuntVoltage_mV() * ina226.getCurrent_mA()) / 1000;
  Serial.println("即時功率(mW):");
  Serial.println(fan_mW);
  Serial.println("累加能量(mWh):");
  Serial.println((fan_mW / 60));
  Serial.println("---------");
  }
