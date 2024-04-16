Blockly.Arduino['amani_tm1637_show'] = function(block) {
  var value_clk = Blockly.Arduino.valueToCode(block, 'clk', Blockly.Arduino.ORDER_ATOMIC);
  var value_dio = Blockly.Arduino.valueToCode(block, 'dio', Blockly.Arduino.ORDER_ATOMIC);
  var value_num = Blockly.Arduino.valueToCode(block, 'num', Blockly.Arduino.ORDER_ATOMIC);
  var dropdown_leading_zero = block.getFieldValue('leading_zero');
  // TODO: Assemble Arduino into code variable.
Blockly.Arduino.definitions_['amani_tm1637_show'] = '#include <TM1637Display.h>\n';
  Blockly.Arduino.definitions_['amani_tm1637_show' + value_clk + value_dio ] = 'TM1637Display tm_display' +value_clk +value_dio+'('+value_clk+', ' + value_dio+'); ';
Blockly.Arduino.setups_['amani_tm1637_show' + value_clk + value_dio] = 'tm_display'+ value_clk+ value_dio+'.setBrightness(7); \n '+'tm_display' +value_clk +value_dio+'.clear(); \n ';
var code ='tm_display' +value_clk +value_dio+'.showNumberDec('+value_num+', ' +dropdown_leading_zero+'); \n ';

  
  return code;
};

Blockly.Arduino['amani_tm1637_colon'] = function(block) {
  var value_clk = Blockly.Arduino.valueToCode(block, 'clk', Blockly.Arduino.ORDER_ATOMIC);
  var value_dio = Blockly.Arduino.valueToCode(block, 'dio', Blockly.Arduino.ORDER_ATOMIC);
  var value_num1 = Blockly.Arduino.valueToCode(block, 'num1', Blockly.Arduino.ORDER_ATOMIC);
  var value_num2 = Blockly.Arduino.valueToCode(block, 'num2', Blockly.Arduino.ORDER_ATOMIC);
  // TODO: Assemble Arduino into code variable.
  Blockly.Arduino.definitions_['amani_tm1637_show'] = '#include <TM1637Display.h>\n';
  Blockly.Arduino.definitions_['amani_tm1637_show' + value_clk + value_dio ] = 'TM1637Display tm_display' +value_clk +value_dio+'('+value_clk+', ' + value_dio+'); ';
  Blockly.Arduino.setups_['amani_tm1637_show' + value_clk + value_dio] = 'tm_display'+ value_clk+ value_dio+'.setBrightness(7); \n '+'tm_display' +value_clk +value_dio+'.clear(); \n ';
  var code =
'tm_display'+value_clk+ value_dio+'.showNumberDecEx('+value_num1+', 0x40, true, 2, 0); \n'+
'tm_display'+value_clk +value_dio+'.showNumberDecEx('+value_num2+',  0, true,  2, 2); \n ';
  
  return code;
};

Blockly.Arduino['amani_tm1637_clear'] = function(block) {
  var value_clk = Blockly.Arduino.valueToCode(block, 'clk', Blockly.Arduino.ORDER_ATOMIC);
  var value_dio = Blockly.Arduino.valueToCode(block, 'dio', Blockly.Arduino.ORDER_ATOMIC);
  // TODO: Assemble Arduino into code variable.
  var code ='tm_display' +value_clk +value_dio+'.clear();\n ';
  return code;
};

Blockly.Arduino['amani_st7920lcd_string'] = function(block) {
  var value_row = Blockly.Arduino.valueToCode(block, 'row', Blockly.Arduino.ORDER_ATOMIC);
  var value_col = Blockly.Arduino.valueToCode(block, 'col', Blockly.Arduino.ORDER_ATOMIC);
  var value_str = Blockly.Arduino.valueToCode(block, 'str', Blockly.Arduino.ORDER_ATOMIC);
  // TODO: Assemble Arduino into code variable.
  Blockly.Arduino.definitions_['amani_st7920lcd_string'] = '#include "LCD12864RSPI.h"\n#define AR_SIZE( a ) sizeof( a ) / sizeof( a[0] )\n';
  Blockly.Arduino.setups_['amani_st7920lcd_string'] = 'LCDA.Initialise();\ndelay(100);\n';
  var code ='LCDA.DisplayString('+ (value_row-1)+ ', ' +(value_col-1)+ ', ' +value_str+', AR_SIZE('+ value_str+'));\n';

  return code;
};

Blockly.Arduino['amani_st7920lcd_clear'] = function(block) {
  // TODO: Assemble Arduino into code variable.
  var code ='LCDA.CLEAR();\n';
  
  return code;
};

Blockly.Arduino['amani_random'] = function(block) {
  var value_min = Blockly.Arduino.valueToCode(block, 'min', Blockly.Arduino.ORDER_ATOMIC);
  var value_max = Blockly.Arduino.valueToCode(block, 'max', Blockly.Arduino.ORDER_ATOMIC);
  value_max++;
  // TODO: Assemble Arduino into code variable.
  Blockly.Arduino.setups_['amani_random'] = 'randomSeed(analogRead(0));\n';
  var code ='random('+value_min+',' + value_max +')';
  
  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.Arduino.ORDER_NONE];
};

Blockly.Arduino['amani_stepmoter_go'] = function(block) {
  var value_in1 = Blockly.Arduino.valueToCode(block, 'in1', Blockly.Arduino.ORDER_ATOMIC);
  var value_in2 = Blockly.Arduino.valueToCode(block, 'in2', Blockly.Arduino.ORDER_ATOMIC);
  var value_in3 = Blockly.Arduino.valueToCode(block, 'in3', Blockly.Arduino.ORDER_ATOMIC);
  var value_in4 = Blockly.Arduino.valueToCode(block, 'in4', Blockly.Arduino.ORDER_ATOMIC);
  var value_c = Blockly.Arduino.valueToCode(block, 'c', Blockly.Arduino.ORDER_ATOMIC);
  // TODO: Assemble Arduino into code variable.
  Blockly.Arduino.definitions_['amani_stepmoter_go'] = '#include <Stepper.h>\nint steps=2048;\n';
Blockly.Arduino.definitions_['amani_stepmoter_go' + value_in1 + value_in2 ] = 'Stepper myStepper' +value_in1+ value_in2+ value_in3 +value_in4+'(steps, ' +value_in1+ ', ' +value_in3 +', '+ value_in2 +', ' +value_in4+ '); ';
Blockly.Arduino.setups_['amani_stepmoter_go' + value_in1 + value_in2] = 'myStepper'+ value_in1+ value_in2+ value_in3+ value_in4 +'.setSpeed(12);\n ';
Blockly.Arduino.functions_['amani_stepmoter_go'] = 'void go(float c,Stepper stepper) {\n  int num = ((abs(c)) * 8) - 1;\n  for (int i = 0; i <= num; i++) {\n    if (c >= 0) {\n      stepper.step(256);\n    } else {\n      stepper.step(-256);\n    }\n  }\n  delay(1000);\n}\n';
var code ='go('+value_c+', myStepper'+ value_in1+ value_in2+ value_in3+ value_in4 +'); \n ';

  
  return code;
};

Blockly.Arduino['amani_joystick_init'] = function(block) {
  var dropdown_xpin = block.getFieldValue('xPin');
  var dropdown_ypin = block.getFieldValue('yPin');
  var value_swpin = Blockly.Arduino.valueToCode(block, 'swPin', Blockly.Arduino.ORDER_ATOMIC);
  // TODO: Assemble Arduino into code variable.
  Blockly.Arduino.definitions_['amani_joystick_init'] = 'int joystick_xVal = analogRead(' +dropdown_ypin +');// vY腳位\n'+'int joystick_yVal = analogRead(' +dropdown_xpin +');// vX腳位\n '+'int joystick_swVal = digitalRead('+ value_swpin+ '); \n ';
  
  Blockly.Arduino.setups_['amani_joystick_init'] = 'pinMode('+value_swpin+', INPUT_PULLUP);\n ';
  
  Blockly.Arduino.functions_['amani_joystick_init'] = 'bool is_this_direct(String direct){\n  return direct == joystick_direct();\n}\nString joystick_direct(){\n  joystick_xVal = analogRead('+dropdown_ypin +');\n  joystick_yVal = analogRead(' +dropdown_xpin +');\n  String xDirect = "";\n  String yDirect = "";  \n  if (joystick_xVal < 480) {\n    xDirect="Left";\n  } else if (joystick_xVal > 520) {\n    xDirect="Right";\n  }  \n  if (joystick_yVal < 480) {\n    yDirect ="Down";\n  } else if (joystick_yVal > 520) {\n    yDirect ="Up";\n  }\n  return xDirect+yDirect;\n}\nbool is_click_sw(){\n  joystick_swVal = digitalRead('+ value_swpin+ ');\n  return !joystick_swVal;\n}\n';
  
  var code ='';
  return code;
};

Blockly.Arduino['amani_joystick_switch'] = function(block) {
  // TODO: Assemble Arduino into code variable.
  var code ='is_click_sw()';
  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.Arduino.ORDER_NONE];
};

Blockly.Arduino['amani_joystick_direct'] = function(block) {
  var dropdown_direct = block.getFieldValue('direct');
  // TODO: Assemble Arduino into code variable.
  var code ='is_this_direct("'+dropdown_direct+'") ';
  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.Arduino.ORDER_NONE];
};