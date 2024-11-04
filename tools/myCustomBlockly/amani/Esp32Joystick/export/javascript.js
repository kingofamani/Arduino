Blockly.Arduino['_01amani_esp32joystick_init'] = function(block) {
  var value_xpin = Blockly.Arduino.valueToCode(block, 'xpin', Blockly.Arduino.ORDER_ATOMIC);
  var value_ypin = Blockly.Arduino.valueToCode(block, 'ypin', Blockly.Arduino.ORDER_ATOMIC);
  var value_swpin = Blockly.Arduino.valueToCode(block, 'swpin', Blockly.Arduino.ORDER_ATOMIC);
  var dropdown_angle = block.getFieldValue('angle');
  var dropdown_order = block.getFieldValue('order');
  
  Blockly.Arduino.definitions_['_01amani_esp32joystick_init'+dropdown_order] = 'const int x_joy_pin'+dropdown_order+' = '+value_xpin+';    //VRx\nconst int y_joy_pin'+dropdown_order+' = '+value_ypin+';   //VRy\nconst int sw_joy_pin'+dropdown_order+' = '+value_swpin+';  //SW\nint angle_joy'+dropdown_order+' = '+dropdown_angle+';          //旋轉角度\n';

  Blockly.Arduino.definitions_['_01amani_esp32joystick_init'] = 'String directs[8] = { "u", "ur", "r", "dr", "d", "dl", "l", "ul" };\nconst int coord_center[2] = { 1800, 1900 };  //x,y的中心位置範圍\nconst int coord_max = 4095;                  //x,y的最大值\n';

  Blockly.Arduino.setups_['_01amani_esp32joystick_init'] = '  analogReadResolution(12);  //4095\n';
  
  Blockly.Arduino.setups_['_01amani_esp32joystick_init'+dropdown_order] = 'pinMode('+value_swpin+', INPUT_PULLUP);';
  
  Blockly.Arduino.functions_['_01amani_esp32joystick_init'] = 'int getDirectIndex(int angle, int x, int y) {\n  int index = 0;\n  if (isCenter(x) && y == 0) {\n    index = 0;  //上\n  } else if (x == coord_max && y == 0) {\n    index = 1;  //右上\n  } else if (x == coord_max && isCenter(y)) {\n    index = 2;  //右\n  } else if (x == coord_max && y == coord_max) {\n    index = 3;  //右下\n  } else if (isCenter(x) && y == coord_max) {\n    index = 4;  //下\n  } else if (x == 0 && y == coord_max) {\n    index = 5;  //左下\n  } else if (x == 0 && isCenter(y)) {\n    index = 6;  //左\n  } else if (x == 0 && y == 0) {\n    index = 7;  //左上\n  } else if (isCenter(x) && isCenter(y)) {\n    index = 99;  //中間\n  }\n  //取得旋轉後的index\n  if (index == 99) {\n    return index;\n  } else {\n    return index = getRotateIndex(angle, index);\n  }\n}\nbool isCenter(int coord) {\n  return (coord >= coord_center[0] && coord <= coord_center[1]);\n}\nint getRotateIndex(int angle, int direct_index) {\n  int rotate[4] = { 0, 6, 4, 2 };  //旋轉後增加的index值\n  int rotate_index = ((direct_index + 8) + rotate[angle / 90]) % 8;\n  return rotate_index;\n}\nString getDirect(int angle, int x, int y) {\n  int index = getDirectIndex(angle, x, y);\n  if (index == 99) {\n    return "";  //方向桿在中間\n  } else {\n    return directs[index];\n  }\n}\nbool isDirect(String dir,int angle, int x, int y) {\n  String direct = getDirect(angle,x,y);\n  return direct == dir;\n}\n';


  var code = '';
  return code;
};

Blockly.Arduino['_02amani_esp32joystick_dir'] = function(block) {
  var dropdown_order = block.getFieldValue('order');
  // TODO: Assemble javascript into code variable.
  var code = 'getDirect(angle_joy'+dropdown_order+', analogRead(x_joy_pin'+dropdown_order+'), analogRead(y_joy_pin'+dropdown_order+'))';
  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.Arduino.ORDER_NONE];
};

Blockly.Arduino['_03amani_esp32joystick_isdir'] = function(block) {
  var dropdown_direct = block.getFieldValue('direct');
  var dropdown_order = block.getFieldValue('order');
  // TODO: Assemble javascript into code variable.
  var code = 'isDirect("'+dropdown_direct+'",angle_joy'+dropdown_order+', analogRead(x_joy_pin'+dropdown_order+'), analogRead(y_joy_pin'+dropdown_order+'))';


  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.Arduino.ORDER_NONE];
};

Blockly.Arduino['_04amani_esp32joystick_sw'] = function(block) {
  var dropdown_order = block.getFieldValue('order');
  // TODO: Assemble javascript into code variable.
  var code = 'digitalRead(sw_joy_pin'+dropdown_order+')';

  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.Arduino.ORDER_NONE];
};