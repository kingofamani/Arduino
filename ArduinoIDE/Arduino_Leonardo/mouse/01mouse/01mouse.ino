#include <Mouse.h>



void setup(){  // put your setup code here, to run once:
  Mouse.begin(); // initialize control over the mouse
}

void loop(){  // put your main code here, to run repeatedly:
  pinMode(4,INPUT_PULLUP); //make pin 4 an input and turn on the pullup resistor so it goes high unless connected to ground
  if(digitalRead(4)==LOW){  // do nothing until pin 4 goes low
    Mouse.move(100, 100, 0);
  }	
  delay( 1000 ); // waits a few milliseconds 
  pinMode(4,INPUT_PULLUP); //make pin 4 an input and turn on the pullup resistor so it goes high unless connected to ground
  if(digitalRead(4)==LOW){  // do nothing until pin 4 goes low
    Mouse.move(-100, -100, 0);
  }	
  delay( 1000 ); // waits a few milliseconds 
}
