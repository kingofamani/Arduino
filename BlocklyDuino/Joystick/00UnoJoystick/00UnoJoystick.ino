//Generated Date: Mon, 14 Oct 2024 07:28:33 GMT



int joystick_xVal = analogRead(A0);// vY腳位
int joystick_yVal = analogRead(A5);// vX腳位
 int joystick_swVal = digitalRead(12);


void setup()
{
  pinMode(12, INPUT_PULLUP);


  Serial.begin(9600);

}

void loop()
{
  Serial.println((is_this_direct("Up") ));
  Serial.println((is_this_direct("Down") ));
  Serial.println((is_this_direct("Left") ));
  Serial.println((is_this_direct("Right") ));
  Serial.println((is_click_sw()));
  Serial.println("---------------------------");
  delay(500);
}

bool is_this_direct(String direct){
  return direct == joystick_direct();
}
String joystick_direct(){
  joystick_xVal = analogRead(A0);
  joystick_yVal = analogRead(A5);
  String xDirect = "";
  String yDirect = "";
  if (joystick_xVal < 480) {
    xDirect="Left";
  } else if (joystick_xVal > 520) {
    xDirect="Right";
  }
  if (joystick_yVal < 480) {
    yDirect ="Down";
  } else if (joystick_yVal > 520) {
    yDirect ="Up";
  }
  return xDirect+yDirect;
}
bool is_click_sw(){
  joystick_swVal = digitalRead(12);
  return !joystick_swVal;
}
