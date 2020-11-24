/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Tue, 20 Oct 2020 01:15:02 GMT
 */

#include <Wire.h>
#include <Adafruit_MLX90614.h>

float amb;

float obj;

Adafruit_MLX90614 mlx;

void setup()
{
  Serial.begin(9600);

  mlx = (Adafruit_MLX90614());
  mlx.begin();
}


void loop()
{
  Serial.print("室溫= ");
  amb = (mlx.readAmbientTempC());
  obj = (mlx.readObjectTempC());
  Serial.print(amb);
  Serial.println("*C");
  Serial.print("體溫= ");
  Serial.print(obj);
  Serial.println("*C");
  Serial.println("");
  delay(500);
}