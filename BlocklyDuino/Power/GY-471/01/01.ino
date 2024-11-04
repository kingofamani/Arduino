#define vtpin A0

#define atpin A5

#define Arduino_Voltage 5.0


void setup() {

 pinMode(vtpin, INPUT);

 pinMode(atpin, INPUT);

 Serial.begin(9600);


}


void loop() {

int v = analogRead(vtpin);

int a = analogRead(atpin);


double voltage = v * (Arduino_Voltage / 1023.0) * 5;

double current = a * (Arduino_Voltage / 1023.0);

double watts = current * voltage; 


Serial.print(voltage);

Serial.println('v');

Serial.print(current);

Serial.println('A');

Serial.print(watts);

Serial.println('W');


 delay(3000);

}