#define U1RXD 16
#define U1TXD 17
void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, U1RXD, U1TXD);
}
void loop() {
    Serial.println("Message Received: ");
    Serial.println(Serial2.readString());
}
