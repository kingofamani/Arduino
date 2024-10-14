const int x_joy_pin = 15;    //VRx
const int y_joy_pin = 12;   //VRy
const int sw_joy_pin = 17;  //SW
int angle_joy = 90;          //旋轉角度

String directs[8] = { "u", "ur", "r", "dr", "d", "dl", "l", "ul" };

const int coord_center[2] = { 1700, 2000 };  //x,y的中心位置範圍
const int coord_max = 4095;                  //x,y的最大值

int getDirectIndex(int angle, int x, int y) {
  int index = 0;
  if (isCenter(x) && y == 0) {
    index = 0;  //上
  } else if (x == coord_max && y == 0) {
    index = 1;  //右上
  } else if (x == coord_max && isCenter(y)) {
    index = 2;  //右
  } else if (x == coord_max && y == coord_max) {
    index = 3;  //右下
  } else if (isCenter(x) && y == coord_max) {
    index = 4;  //下
  } else if (x == 0 && y == coord_max) {
    index = 5;  //左下
  } else if (x == 0 && isCenter(y)) {
    index = 6;  //左
  } else if (x == 0 && y == 0) {
    index = 7;  //左上
  } else if (isCenter(x) && isCenter(y)) {
    index = 99;  //中間
  }

  //取得旋轉後的index
  if (index == 99) {
    return index;
  } else {
    return index = getRotateIndex(angle, index);
  }
}

bool isCenter(int coord) {
  return (coord >= coord_center[0] && coord <= coord_center[1]);
}

int getRotateIndex(int angle, int direct_index) {
  int rotate[4] = { 0, 6, 4, 2 };  //旋轉後增加的index值

  int rotate_index = ((direct_index + 8) + rotate[angle / 90]) % 8;
  return rotate_index;
}

String getDirect(int angle, int x, int y) {
  int index = getDirectIndex(angle, x, y);
  if (index == 99) {
    return "";  //方向桿在中間
  } else {
    return directs[index];
  }
}

bool isDirect(String dir) {
  String direct = getDirect(angle_joy, analogRead(x_joy_pin), analogRead(y_joy_pin));
  return direct == dir;
}

void setup() {
  Serial.begin(9600);

  pinMode(sw_joy_pin, INPUT_PULLUP);
  analogReadResolution(12);  //4095(3.3v)
}



void loop() {

  Serial.println(getDirect(angle_joy, analogRead(x_joy_pin), analogRead(y_joy_pin)));
  // Serial.println(getDirect(90, analogRead(x_joy_pin), analogRead(y_joy_pin)));
  // Serial.println(getDirect(180, analogRead(x_joy_pin), analogRead(y_joy_pin)));
  // Serial.println(getDirect(270, analogRead(x_joy_pin), analogRead(y_joy_pin)));
  // Serial.println("========");

  // Serial.println(isDirect("u"));
  // Serial.println(isDirect("d"));
  // Serial.println(isDirect("l"));
  // Serial.println(isDirect("r"));
  // Serial.println("========");

  Serial.print("x: ");
  Serial.print(analogRead(x_joy_pin));  // print the value of VRx

  Serial.print("|y: ");
  Serial.print(analogRead(y_joy_pin));  // print the value of VRx

  Serial.print("|Z: ");
  Serial.println(digitalRead(sw_joy_pin));  // print the value of SW
  delay(500);
}