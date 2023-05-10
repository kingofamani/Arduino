const int swPin = 12;
const int VrxPin = A5;
const int VryPin = A0;

int xDirection = 0;
int yDirection = 0;
int switchState = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(swPin, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  xDirection = analogRead(VryPin);
  yDirection = analogRead(VrxPin);

  switchState = digitalRead(swPin);

  Serial.print("Switch:  ");
  Serial.println(switchState);

  Serial.print("X-axis:        ");
  Serial.println(xDirection);

  Serial.print("Y-axis:        ");
  Serial.println(yDirection);

  Serial.println("");

  if (!switchState) {
    Serial.println("Switch pressed");
  }

  if (xDirection < 480) {
    Serial.println("Left");
  } else if (xDirection > 520) {
    Serial.println("Right");
  }

  if (yDirection < 480) {
    Serial.println("Down");
  } else if (yDirection > 520) {
    Serial.println("Up");
  }

  delay(500);
}
