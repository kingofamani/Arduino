//Generated Date: Sun, 07 May 2023 09:14:18 GMT

#include "LCD12864RSPI.h"
#define AR_SIZE( a ) sizeof( a ) / sizeof( a[0] )

unsigned char str1[] = (0xB5, 0xC2,0xA1,0xA1, 0xD2, 0xF4);
unsigned char str2[] = "tyes.ntpc.edu.tw";

void setup()
{

  LCDA.Initialise();
delay(100);

}

void loop()
{
  LCDA.DisplayString(0, 0, str1, AR_SIZE(str1));
  delay(1000);
  LCDA.CLEAR();
  delay(1000);
  LCDA.DisplayString(1, 0, str2, AR_SIZE(str2));
  delay(1000);
  LCDA.CLEAR();
  delay(1000);
}
