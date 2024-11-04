const int outPin = A0;
const int busPin = A1;
const int signPin = 8;

void setup() {
  Serial.begin(9600);
  Serial.println("MAX471 Strom- und Leistungssensor");
  Serial.println();
}

void loop() {
  float voltage = 0.0;
  unsigned long rawVal = 0;
  analogReference(INTERNAL);

  /* After switching you have to execute a dummy analogRead, 
     followed by a short */
  rawVal = analogRead(outPin);
  rawVal = 0;
  delay(10);

 
  for(int i=0; i<25; i++){
    rawVal += analogRead(outPin);
    delay(10);  // 25 measurements to reduce noise
  }
    
  voltage = (rawVal/25.0) * 1100.0 / 1023.0;
  Serial.print("V Out         [mV]: ");
  Serial.println(voltage);

  float current_mA = voltage * 0.9452 + 1.0544; // Calibration parameters
  Serial.print("Busstrom      [mA]: ");  // Bus current
  Serial.println(current_mA);

  Serial.print("Stromrichtung:    : ");  // Current direction
  if(digitalRead(signPin)){
    Serial.println("RS+ -> RS-");
  }
  else{
    Serial.println("RS- -> RS+");
  }

  analogReference(DEFAULT);
  voltage = analogRead(busPin) * 5.0 / 1023.0;  
  Serial.print("Busspannung    [V]: "); // Bus voltage
  Serial.println(voltage);

  float power_mW = (voltage * current_mA);
  Serial.print("Leistung      [mW]: ");  // Power
  Serial.println(power_mW);

  Serial.println("-------------------------------");
  delay(2000);
}