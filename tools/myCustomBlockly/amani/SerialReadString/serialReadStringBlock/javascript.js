Blockly.Arduino['_01amani_serial_avail'] = function(block) {
  var dropdown_serial = block.getFieldValue('serial');
  var statements_msg = Blockly.Arduino.statementToCode(block, 'msg');
  // TODO: Assemble javascript into code variable.
  var code ='if ('+dropdown_serial+'.available()) {\n ' + statements_msg + '}\n ';
  return code;
};

Blockly.Arduino['_02amani_serial_readstring'] = function(block) {
  var dropdown_serial = block.getFieldValue('serial');
  // TODO: Assemble javascript into code variable.
  var code = dropdown_serial+'.readString()';
  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.Arduino.ORDER_NONE];
};