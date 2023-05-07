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
'tm_display'+value_clk +value_dio+'.showNumberDecEx('+value_num2+',  0, false,  2, 2); \n ';
  
  return code;
};

Blockly.Arduino['amani_tm1637_clear'] = function(block) {
  var value_clk = Blockly.Arduino.valueToCode(block, 'clk', Blockly.Arduino.ORDER_ATOMIC);
  var value_dio = Blockly.Arduino.valueToCode(block, 'dio', Blockly.Arduino.ORDER_ATOMIC);
  // TODO: Assemble Arduino into code variable.
  var code ='tm_display' +value_clk +value_dio+'.clear();\n ';
  return code;
};


