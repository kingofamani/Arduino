/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 11 Oct 2021 03:09:44 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include <IRremote.h>

IRrecv irrecv(11);
decode_results results;

void setup()
{
  Serial.begin(9600);

  irrecv.enableIRIn();

}


void loop()
{
  if (irrecv.decode(&results)) {
      Serial.println(String(results.value, HEX));

    irrecv.resume();
  }
}