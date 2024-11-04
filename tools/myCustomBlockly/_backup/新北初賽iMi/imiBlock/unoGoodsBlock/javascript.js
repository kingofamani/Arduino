Blockly.Arduino['_01imi_unogoods_init'] = function(block) {
  var statements_cnc = Blockly.Arduino.statementToCode	(block, 'cnc');
  var statements_uart = Blockly.Arduino.statementToCode	(block, 'uart');
  var statements_servopin = Blockly.Arduino.statementToCode	(block, 'servopin');
  // TODO: Assemble javascript into code variable.
  Blockly.Arduino.definitions_['_01imi_unogoods_init'] = '#include <AccelStepper.h> \n #include <Servo.h>\n #include <SoftwareSerial.h>\n //====插入變數Start====\n ' + statements_cnc+statements_uart+statements_servopin + '//====插入變數End====\n // 伺服馬達\n Servo servoPick;\n const int xMoveSteps = 500;    // 測試電機1運行使用的運行步數\n const int yMoveSteps = 500;    // 測試電機2運行使用的運行步數\n AccelStepper stepper1(1, xstepPin, xdirPin); // 建立步進電機物件1\n AccelStepper stepper2(1, ystepPin, ydirPin); // 建立步進電機物件2\n const char* GOODS_LOAD = "goodsLoad";\n ';

	Blockly.Arduino.setups_['_01imi_unogoods_init'] = '  Serial.begin(9600);\n  // UART\n  ESP32Serial.begin(9600);\n  // 伺服馬達\n  servoPick.attach(servoPin);\n  servoPick.write(0);\n  pinMode(xstepPin, OUTPUT);    // Arduino控制A4988x步進引腳為輸出模式\n  pinMode(xdirPin, OUTPUT);     // Arduino控制A4988x方向引腳為輸出模式\n  pinMode(ystepPin, OUTPUT);    // Arduino控制A4988y步進引腳為輸出模式\n  pinMode(ydirPin, OUTPUT);     // Arduino控制A4988y方向引腳為輸出模式\n  pinMode(enablePin, OUTPUT);  // Arduino控制A4988啟用引腳為輸出模式\n  digitalWrite(enablePin, LOW); // 將啟用控制引腳設置為低電平以使電機驅動板進入工作狀態\n  stepper1.setMaxSpeed(300.0);     // 設置電機最大速度300\n  stepper1.setAcceleration(20.0);  // 設置電機加速度20.0\n  stepper2.setMaxSpeed(300.0);     // 設置電機最大速度300\n  stepper2.setAcceleration(20.0);  // 設置電機加速度20.0\n  \n  //歸零\n  resetStepper();\n';

	Blockly.Arduino.functions_['_01imi_unogoods_init'] = 'void findGoods(int x,int y){\n  //分成3*3格倉庫的xy步數\n  int xSteps=xMoveSteps/2;\n  int ySteps=yMoveSteps/2;\n  //電機移動至該貨物格子\n  stepper1.moveTo(xSteps*x);\n  stepper2.moveTo(ySteps*y);\n}\nvoid resetStepper(){\n  stepper1.moveTo(0);\n  stepper2.moveTo(0);\n}\nvoid testStepper(){\n  // 控制步進電機1往復運動\n  if ( stepper1.currentPosition() == 0 ) {\n    stepper1.moveTo(xMoveSteps);\n    servoPick.write(0);// 伺服馬達轉0度\n  } else if ( stepper1.currentPosition() == xMoveSteps  ) {\n    stepper1.moveTo(0);\n    servoPick.write(90);// 伺服馬達轉90度\n  }\n  // 控制步進電機2往復運動\n  if ( stepper2.currentPosition() == 0 ) {\n    stepper2.moveTo(yMoveSteps);\n  } else if ( stepper2.currentPosition() == yMoveSteps  ) {\n    stepper2.moveTo(0);\n  }\n  stepper1.run();   // 1號電機運行\n  stepper2.run();   // 2號電機運行\n}\n';

  var code = '';
  return code;
};

Blockly.Arduino['_02imi_unogoods_cnc'] = function(block) {
  var value_en = Blockly.Arduino.valueToCode(block, 'en', Blockly.Arduino.ORDER_ATOMIC);
  var value_xdir = Blockly.Arduino.valueToCode(block, 'xdir', Blockly.Arduino.ORDER_ATOMIC);
  var value_xstep = Blockly.Arduino.valueToCode(block, 'xstep', Blockly.Arduino.ORDER_ATOMIC);
  var value_ydir = Blockly.Arduino.valueToCode(block, 'ydir', Blockly.Arduino.ORDER_ATOMIC);
  var value_ystep = Blockly.Arduino.valueToCode(block, 'ystep', Blockly.Arduino.ORDER_ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code = '// 定義電機控制用常數'+'\n'+ 'const int enablePin = '+value_en+';  // 啟用控制引腳'+'\n'+ 'const int xdirPin = '+value_xdir+';     // x方向控制引腳'+'\n'+ 'const int xstepPin = '+value_xstep+';    // x步進控制引腳'+'\n'+ 'const int ydirPin = '+value_ydir+';     // y方向控制引腳'+'\n'+ 'const int ystepPin = '+value_ystep+';    // y步進控制引腳'+'\n';

  return code;
};

Blockly.Arduino['_03imi_unogoods_uart'] = function(block) {
  var value_rx = Blockly.Arduino.valueToCode(block, 'rx', Blockly.Arduino.ORDER_ATOMIC);
  var value_tx = Blockly.Arduino.valueToCode(block, 'tx', Blockly.Arduino.ORDER_ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code = '// UART通訊'+'\n'+'SoftwareSerial ESP32Serial('+value_rx+',' +value_tx+');'+'\n';

  return code;
};

Blockly.Arduino['_04imi_unogoods_servopin'] = function(block) {
  var value_servo = Blockly.Arduino.valueToCode(block, 'servo', Blockly.Arduino.ORDER_ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code = '// 伺服馬達腳位(接在Z+是pin11)'+'\n'+'const int servoPin = '+value_servo+';'+'\n';

  return code;
};

Blockly.Arduino['_05imi_unogoods_esp32'] = function(block) {
  var statements_msg = Blockly.Arduino.statementToCode	(block, 'msg');
  // TODO: Assemble javascript into code variable.

  var code ='// 接收訊息：ESP32→Arduino\n   while (ESP32Serial.available()) {\n //取得貨物在倉庫xy座標\n     String str = ESP32Serial.readString();// 格式xy(例如13)\n ' + statements_msg + '  }//end while\n ';

  return code;
};

Blockly.Arduino['_06imi_unogoods_xy'] = function(block) {
  // TODO: Assemble javascript into code variable.
  var code ='int x = (int)(str.charAt(0) - \'0\');'+'\n'+'int y = (int)(str.charAt(1) - \'0\');'+'\n';

  return code;
};

Blockly.Arduino['_07imi_unogoods_findgoods'] = function(block) {
  // TODO: Assemble javascript into code variable.
  var code ='//CNC開始依座標找尋貨物'+'\n'+'findGoods(x,y);'+'\n';

  return code;
};

Blockly.Arduino['_08imi_unogoods_servo'] = function(block) {
  var dropdown_servo = block.getFieldValue('servo');
  var dropdown_angle = block.getFieldValue('angle');
  // TODO: Assemble javascript into code variable.
  var code ='// 撿貨伺服馬達'+'\n'+dropdown_servo+'.write('+dropdown_angle+');'+'\n'+'delay(2000);'+'\n';

  return code;
};

Blockly.Arduino['_09imi_unogoods_reset'] = function(block) {
  // TODO: Assemble javascript into code variable.
  var code ='//歸零'+'\n'+'resetStepper();'+'\n';

  return code;
};

Blockly.Arduino['_10imi_unogoods_sendesp32'] = function(block) {
  var dropdown_name = block.getFieldValue('NAME');
  // TODO: Assemble javascript into code variable.
  var code ='// 完成撿貨通知ESP32'+'\n'+'ESP32Serial.print(GOODS_LOAD);'+'\n';

  return code;
};