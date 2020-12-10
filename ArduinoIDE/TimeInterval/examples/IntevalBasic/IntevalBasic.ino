#include <TimeInterval.h>

TimeInterval tt;

//int interval = 2000;

void setup() {
  Serial.begin(57600);   
}

void loop()
{ 
  tt.go();
}
