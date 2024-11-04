//Generated Date: Mon, 28 Oct 2024 06:49:04 GMT

#include <PS2X_lib.h>
PS2X ggPs2x;

boolean isMoveJoystick(int x, int y) {
  boolean moveX = !(x == 127 || x == 128);
  boolean moveY = !(y == 127 || y == 128);
  if (!moveX && !moveY) {
    return (false);
  } else {
    return (true);
  }
}

void setup()
{
  ggPs2x.config_gamepad(13,11,10,12,true,true);


  Serial.begin(9600);

}

void loop()
{
  //讀取手把狀態
  ggPs2x.read_gamepad(false,0x00);
  //判斷按鈕：上下左右○×△□
  if (ggPs2x.Button(PSB_TRIANGLE)) {
    Serial.println("你按了三角形鈕");
  }
  //判斷移動L3搖桿
  if (isMoveJoystick(ggPs2x.Analog(PSS_LX), ggPs2x.Analog(PSS_LY))) {
    Serial.println((String("左搖桿：")+String(ggPs2x.Analog(PSS_LX))+String(",")+String(ggPs2x.Analog(PSS_LY))+String("。")));
  }
  Serial.println("======================");
  delay(10);
}
