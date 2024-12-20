/*
Liquid flow rate sensor - ESP32 optimized version

Measure the liquid/water flow rate using GPIO4 for the sensor input.
*/

#define STATUS_LED 13
#define SENSOR_PIN 4  // Use GPIO4 for flow sensor signal

// Calibration factor for the sensor
float calibrationFactor = 4.5;

volatile byte pulseCount;

float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;

unsigned long oldTime;

// Interrupt Service Routine (ISR) for counting pulses
void IRAM_ATTR pulseCounter() {
  pulseCount++;
}

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Set up the status LED line as an output
  pinMode(STATUS_LED, OUTPUT);
  digitalWrite(STATUS_LED, HIGH); // Active-low LED

  // Set up the flow sensor pin as input with pull-up resistor
  pinMode(SENSOR_PIN, INPUT_PULLUP);

  // Check sensor initial state
  Serial.println("Initializing...");
  if (digitalRead(SENSOR_PIN) == HIGH) {
    Serial.println("Sensor signal HIGH, ready.");
  } else {
    Serial.println("Sensor signal LOW, ready.");
  }

  // Initialize variables
  pulseCount = 0;
  flowRate = 0.0;
  flowMilliLitres = 0;
  totalMilliLitres = 0;
  oldTime = 0;

  // Attach interrupt for the sensor pin
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), pulseCounter, FALLING);

  Serial.println("Flow sensor initialized.");
}

void loop() {
  // Process counters once per second
  if ((millis() - oldTime) > 1000) {
    // Disable the interrupt while calculating flow rate and sending the value
    detachInterrupt(digitalPinToInterrupt(SENSOR_PIN));

    // Calculate the flow rate in litres/minute
    flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;

    // Update the time for the next cycle
    oldTime = millis();

    // Convert flow rate to millilitres and add to total
    flowMilliLitres = (flowRate / 60) * 1000;
    totalMilliLitres += flowMilliLitres;

    // Print the results
    Serial.print("Flow rate: ");
    Serial.print(flowRate, 2); // Print flow rate with two decimal places
    Serial.print(" L/min\t");

    Serial.print("Output Liquid Quantity: ");
    Serial.print(totalMilliLitres);
    Serial.print(" mL\t");
    Serial.print(totalMilliLitres / 1000.0, 2); // Convert to litres
    Serial.println(" L");

    // Reset the pulse counter
    pulseCount = 0;

    // Re-enable the interrupt
    attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), pulseCounter, FALLING);
  }
}
