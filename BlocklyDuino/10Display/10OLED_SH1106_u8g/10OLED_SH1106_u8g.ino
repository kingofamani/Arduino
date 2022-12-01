/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 05 Oct 2020 04:39:40 GMT
 */

#include "U8glib.h"

float amb;

float obj;

U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE); // I2C / TWI ;
void draw() {
  u8g.setFont(u8g_font_fur25);
  u8g.setPrintPos(10, 29);
  u8g.print(amb, 1);
  u8g.drawStr( 80, 29, "*C");
  u8g.setPrintPos(10, 63);
  u8g.print(obj, 1);
  u8g.drawStr( 80, 63, "*C");
}

void setup()
{
  Serial.begin(9600);


}


void loop()
{
  amb = 23.5;
obj = 33.2;

u8g.firstPage();
  do {
  draw();
  } while ( u8g.nextPage() );
  delay(100);
}