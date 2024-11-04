#include <Keyboard.h>

/*
 These core libraries allow the 32u4 and SAMD based boards 
 (Leonardo, Esplora, Zero, Due and MKR Family) 
 to appear as a native Mouse and/or Keyboard to a connected computer.
 */

void setup(){  // put your setup code here, to run once:
  pinMode( 10 , INPUT);   // sets the digital pin as input
  Keyboard.begin(); // initialize control over the keyboard
  Keyboard.releaseAll();

}

void loop(){  // put your main code here, to run repeatedly:
  if (digitalRead( 10 )) {

    pinMode(4,INPUT_PULLUP); //make pin 4 an input and turn on the pullup resistor so it goes high unless connected to ground
    if(digitalRead(4)==LOW){  // do nothing until pin 4 goes low
      Keyboard.press(131); //the key to press (ASCII code)
    }
    pinMode(4,INPUT_PULLUP); //make pin 4 an input and turn on the pullup resistor so it goes high unless connected to ground
    if(digitalRead(4)==LOW){  // do nothing until pin 4 goes low
      Keyboard.press('r'); //the key to press (ASCII code)
    }
    Keyboard.releaseAll();
    delay( 2000 ); // waits a few milliseconds 

    pinMode(4,INPUT_PULLUP); //make pin 4 an input and turn on the pullup resistor so it goes high unless connected to ground
    if(digitalRead(4)==LOW){  // do nothing until pin 4 goes low
      Keyboard.print("notepad"); //Send the message
    }	
    delay( 1000 ); // waits a few milliseconds 

    pinMode(4,INPUT_PULLUP); //make pin 4 an input and turn on the pullup resistor so it goes high unless connected to ground
    if(digitalRead(4)==LOW){  // do nothing until pin 4 goes low
      Keyboard.press(176); //the key to press (ASCII code)
    }
    Keyboard.releaseAll();
    delay( 1000 ); // waits a few milliseconds 

    pinMode(4,INPUT_PULLUP); //make pin 4 an input and turn on the pullup resistor so it goes high unless connected to ground
    if(digitalRead(4)==LOW){  // do nothing until pin 4 goes low
      Keyboard.print("Stop Talking..."); //Send the message
    }
  }
}
