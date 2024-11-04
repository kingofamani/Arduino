//Generated Date: Sat, 06 May 2023 10:32:28 GMT

#include <TM1637Display.h>

TM1637Display tm_display23(2, 3);

void setup()
{

  tm_display23.setBrightness(7);
 tm_display23.clear();

}

void loop()
{
  tm_display23.showNumberDec(1234, true);
   delay(1000);
  tm_display23.clear();
   delay(1000);
}
