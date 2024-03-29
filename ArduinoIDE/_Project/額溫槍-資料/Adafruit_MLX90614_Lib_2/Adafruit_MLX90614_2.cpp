/***************************************************
  This is a library for the MLX90614 Temp Sensor

  Designed specifically to work with the MLX90614 sensors in the
  adafruit shop
  ----> https://www.adafruit.com/products/1748
  ----> https://www.adafruit.com/products/1749

  These sensors use I2C to communicate, 2 pins are required to
  interface
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include "Adafruit_MLX90614_2.h"

Adafruit_MLX90614_2::Adafruit_MLX90614_2(uint8_t i2caddr) { _addr = i2caddr; }

boolean Adafruit_MLX90614_2::begin(void) {
  Wire.begin();

  /*
  for (uint8_t i=0; i<0x20; i++) {
    Serial.print(i); Serial.print(" = ");
    Serial.println(read16(i), HEX);
  }
  */
  return true;
}

//////////////////////////////////////////////////////

double Adafruit_MLX90614_2::readObjectTempF(void) {
  return (readTemp(MLX90614_TOBJ1) * 9 / 5) + 32;
}

double Adafruit_MLX90614_2::readAmbientTempF(void) {
  return (readTemp(MLX90614_TA) * 9 / 5) + 32;
}

double Adafruit_MLX90614_2::readObjectTempC(void) {
  return readTemp(MLX90614_TOBJ1);
}

double Adafruit_MLX90614_2::readAmbientTempC(void) {
  return readTemp(MLX90614_TA);
}

float Adafruit_MLX90614_2::readTemp(uint8_t reg) {
  float temp;

  temp = read16(reg);
  temp *= Adafruit_MLX90614_2::multi;
  temp -= Adafruit_MLX90614_2::offset;
  return temp;
}

/*********************************************************************/

uint16_t Adafruit_MLX90614_2::read16(uint8_t a) {
  uint16_t ret;

  Wire.beginTransmission(_addr); // start transmission to device
  Wire.write(a);                 // sends register address to read from
  Wire.endTransmission(false);   // end transmission

  Wire.requestFrom(_addr, (size_t)3); // send data n-bytes read
  ret = Wire.read();                  // receive DATA
  ret |= Wire.read() << 8;            // receive DATA

  uint8_t pec = Wire.read();

  return ret;
}
