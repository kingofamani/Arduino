/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Sat, 26 Sep 2020 12:12:28 GMT
 */

#include <IRremote.h>

unsigned long button;

#define POWER 0x10EFD827
#define A 0x10EFF807
#define B 0x10EF7887
#define C 0x10EF58A7
#define UP 0x10EFA05F
#define DOWN 0x10EF00FF
#define LEFT 0x10EF10EF
#define RIGHT 0x10EF807F
#define SELECT 0x10EF20DF

IRrecv irrecv11(11);
decode_results results11;

unsigned long getDecodedValue(IRrecv receiver, decode_results results) {
  if (receiver.decode(&results)) {
      receiver.resume();
      return results.value;
    }
  return 0;
}

void setup()
{
  Serial.begin(9600);

  irrecv11.enableIRIn(); // Start the receiver

}


void loop()
{
  button = (getDecodedValue(irrecv11,results11));
if (button != 0) {
  Serial.println(button);

}

}