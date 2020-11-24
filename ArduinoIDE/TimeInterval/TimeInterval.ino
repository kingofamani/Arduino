/*
  Print serial text with an interval.
  Basic example.   
  
  created 01-12-2009 by kasperkamperman.com
*/

unsigned long previousMillis  = 0;
unsigned long currentMillis   = 0;

int interval = 2000;

void setup() {
  // opens serial port, sets data rate to 57600 bits per second
  Serial.begin(57600);   
}

void loop()
{ // save number of milliseconds since the program started
  currentMillis = millis();
  
  // check to see if the interval time is passed. 
  if (currentMillis - previousMillis >= interval == true ) {
    
      Serial.print("this program runs now for : ");
      Serial.print(currentMillis);
      Serial.println(" milliseconds");
      
      // save the time when we displayed the string for the last time
      previousMillis = currentMillis;
  }
}
