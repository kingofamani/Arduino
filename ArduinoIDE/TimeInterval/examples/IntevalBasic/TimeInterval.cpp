#include "TimeInterval.h"
#include "Arduino.h"

  unsigned long previousMillis  = 0;
  unsigned long currentMillis   = 0;
  int interval = 2000;
  TimeInterval::TimeInterval (){}

  TimeInterval::~TimeInterval (){
    disattach();
 }

  void TimeInterval::go(){
    currentMillis = millis();
    if (currentMillis - previousMillis >= interval == true ) {    
      Serial.print("this program runs now for : ");
      Serial.print(currentMillis);
      Serial.println(" milliseconds");
      // save the time when we displayed the string for the last time
      previousMillis = currentMillis;
    }
  }

  void TimeInterval::disattach()
{
    currentMillis = 0;
}
