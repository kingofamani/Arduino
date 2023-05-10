//const int swPin = 12;
//const int VrxPin = A5;
//const int VryPin = A0;

//int xDirection = 0;
//int yDirection = 0;
//int switchState = 1;

void setup() {
  Serial.begin(9600);
  pinMode(12, INPUT_PULLUP);
}

void loop() {
  int xVal = analogRead(A0);// vY腳位
  int yVal = analogRead(A5);// vX腳位
  int swVal = digitalRead(12);

  Serial.println(joystick_direct(xVal,yVal));
  Serial.println(is_click_sw(swVal));
  Serial.println(is_this_direct(xVal,yVal,"Up"));
  
}

bool is_this_direct(int xVal,int yVal,String direct){
  return direct == joystick_direct(xVal,yVal);
}

String joystick_direct(int xVal,int yVal){
  String xDirect = "";
  String yDirect = "";
  
  if (xVal < 480) {
    xDirect="Left";
  } else if (xVal > 520) {
    xDirect="Right";
  }
  
  if (yVal < 480) {
    yDirect ="Down";
  } else if (yVal > 520) {
    yDirect ="Up";
  }

  return xDirect+yDirect;
}

bool is_click_sw(int swVal){
  return !swVal;
}
