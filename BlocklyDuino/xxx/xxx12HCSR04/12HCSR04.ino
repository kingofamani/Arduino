/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 05 Oct 2020 04:41:52 GMT
 */

#include <Ultrasonic.h>

int distance;

/*安裝Ultrasonic by ErickSimoes的函式庫*/
Ultrasonic ultrasonic(5, 6);//(Trig,Echo)

void setup()
{
  Serial.begin(9600);


}


void loop()
{
  distance = (ultrasonic.read());
  Serial.print("距離：");
  Serial.print(distance);
  Serial.println(" cm");
  delay(500);
}