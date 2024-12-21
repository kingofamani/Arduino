Blockly.Arduino['amani_fake_ina226_init'] = function(block) {
  var dropdown_inachannel = block.getFieldValue('inachannel');
  // TODO: Assemble javascript into code variable.
  var code = '';
  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.Arduino.ORDER_NONE];
};

Blockly.Arduino['amani_fake_ina226_mv'] = function(block) {
  var dropdown_inachannel = block.getFieldValue('mvchannel');
  // TODO: Assemble javascript into code variable.
  var code = '';
  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.Arduino.ORDER_NONE];
};

Blockly.Arduino['amani_fake_ina226_ma'] = function(block) {
  var dropdown_inachannel = block.getFieldValue('machannel');
  // TODO: Assemble javascript into code variable.
  var code = '';
  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.Arduino.ORDER_NONE];
};

Blockly.Arduino['amani_fake_cnc_init'] = function(block) {
  var value_cncenable = Blockly.Arduino.valueToCode(block, 'cncenable', Blockly.Arduino.ORDER_ATOMIC);
  var value_xdir = Blockly.Arduino.valueToCode(block, 'xdir', Blockly.Arduino.ORDER_ATOMIC);
  var value_xstep = Blockly.Arduino.valueToCode(block, 'xstep', Blockly.Arduino.ORDER_ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code = '';
  return code;
};

Blockly.Arduino['amani_fake_cnc_xmove'] = function(block) {
  var value_xmove = Blockly.Arduino.valueToCode(block, 'xmove', Blockly.Arduino.ORDER_ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code = '';
  return code;
};

Blockly.Arduino['amani_fake_cnc_xcurrent'] = function(block) {
  // TODO: Assemble javascript into code variable.
  var code = '';
  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.Arduino.ORDER_NONE];
};

Blockly.Arduino['amani_fake_yfs201_init'] = function(block) {
  var value_yfspin = Blockly.Arduino.valueToCode(block, 'yfspin', Blockly.Arduino.ORDER_ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code = '';
  return code;
};

Blockly.Arduino['amani_fake_yfs201_flow'] = function(block) {
  // TODO: Assemble javascript into code variable.
  var code = '';
  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.Arduino.ORDER_NONE];
};