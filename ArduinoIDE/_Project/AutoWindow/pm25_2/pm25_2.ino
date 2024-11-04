/*
 * 等級     1    2      3     4     5     6     7     8     9   10
 * 分類    低    低     低     中     中   中     高     高   高   非常高
 * μg/m3 0-11  12-23 24-35 36-41 42-47 48-53 54-58 59-64 65-70 >71
*/
int measurePin = 0; //Connect dust sensor to Arduino A0 pin
int ledPower = 2; //Connect 3 led driver pins of dust sensor to Arduino D2
int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680; 
float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0; 

void setup() {
  Serial.begin(9600);
  pinMode(ledPower, OUTPUT);
} 

void loop() {
  digitalWrite(ledPower, LOW); // power on the LED
  delayMicroseconds(samplingTime); 
  voMeasured = analogRead(measurePin); // read the dust value

  delayMicroseconds(deltaTime);
  digitalWrite(ledPower, HIGH); // turn the LED off
  delayMicroseconds(sleepTime);

  // 0 - 5V mapped to 0 - 1023 integer values
  // recover voltage
  calcVoltage = voMeasured * (5.0 / 1024.0);

  // linear eqaution taken from http://www.howmuchsnow.com/arduino/airquality/
  // Chris Nafis (c) 2012
  dustDensity = 0.17 * calcVoltage - 0.1;

  Serial.print("Raw Signal Value (0-1023): ");
  Serial.print(voMeasured);

  Serial.print(" - Voltage: ");
  Serial.print(calcVoltage);

  Serial.print(" - Dust Density: ");
  Serial.print(dustDensity * 1000); // 這裡將數值呈現改成較常用的單位( ug/m3 )
  Serial.println(" ug/m3 ");
  delay(1000);
}
