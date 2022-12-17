#define U1RXD 18
#define U1TXD 17
void setup() {
  Serial.begin(9600);
  Serial1.begin(9600, SERIAL_8N1, U1RXD, U1TXD);
}
void loop() {
    if (Serial1.available()) {
      Serial.write(Serial1.read());
  }
}
