/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Thu, 12 Nov 2020 03:41:10 GMT
 */

#include <DHT.h>

float tem;

float hum;

DHT dht11(12, DHT11);

void setup()
{
  Serial.begin(9600);


  dht11.begin();
}


void loop()
{
  tem = dht11.readTemperature();
  hum = dht11.readHumidity();
  Serial.print("溫度：");
  Serial.println(tem);
  Serial.print("濕度：");
  Serial.println(hum);
  delay(5000);
}
