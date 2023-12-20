Blockly.Arduino['_01imi_espmap_init'] = function(block) {
  var statements_wifi = Blockly.Arduino.statementToCode(block, 'wifi');
  var statements_mqtt = Blockly.Arduino.statementToCode(block, 'mqtt');
  var statements_button = Blockly.Arduino.statementToCode(block, 'button');
  var statements_map = Blockly.Arduino.statementToCode(block, 'map');
  // TODO: Assemble javascript into code variable.
  var code = 
  '1111\n'+
  statements_wifi +
  '2222\n'+
   statements_mqtt+
  '3333\n'+
   statements_button+
  '4444\n'+
  statements_map;
  return code;
};

Blockly.Arduino['_02imi_espmap_wifi'] = function(block) {
  var value_ssid = Blockly.Arduino.valueToCode(block, 'ssid', Blockly.Arduino.ORDER_ATOMIC);
  var value_wifipwd = Blockly.Arduino.valueToCode(block, 'wifipwd', Blockly.Arduino.ORDER_ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code = '...\n';
  return code;
};

Blockly.Arduino['_03imi_espmap_mqtt'] = function(block) {
  var value_mqtt_user = Blockly.Arduino.valueToCode(block, 'mqtt_user', Blockly.Arduino.ORDER_ATOMIC);
  var value_mqtt_pwd = Blockly.Arduino.valueToCode(block, 'mqtt_pwd', Blockly.Arduino.ORDER_ATOMIC);
  var value_mqtt_port = Blockly.Arduino.valueToCode(block, 'mqtt_port', Blockly.Arduino.ORDER_ATOMIC);
  var value_mqtt_server = Blockly.Arduino.valueToCode(block, 'mqtt_server', Blockly.Arduino.ORDER_ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code = '...\n';
  return code;
};

Blockly.Arduino['_04imi_espmap_button'] = function(block) {
  var value_btnpin = Blockly.Arduino.valueToCode(block, 'btnpin', Blockly.Arduino.ORDER_ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code = '...\n';
  return code;
};

Blockly.Arduino['_05imi_espmap_map'] = function(block) {
  var value_00 = Blockly.Arduino.valueToCode(block, '00', Blockly.Arduino.ORDER_ATOMIC);
  var value_01 = Blockly.Arduino.valueToCode(block, '01', Blockly.Arduino.ORDER_ATOMIC);
  var value_02 = Blockly.Arduino.valueToCode(block, '02', Blockly.Arduino.ORDER_ATOMIC);
  var value_03 = Blockly.Arduino.valueToCode(block, '03', Blockly.Arduino.ORDER_ATOMIC);
  var value_04 = Blockly.Arduino.valueToCode(block, '04', Blockly.Arduino.ORDER_ATOMIC);
  var value_05 = Blockly.Arduino.valueToCode(block, '05', Blockly.Arduino.ORDER_ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code =  '    { '+value_00+',' +value_01+',' +value_02+',' +value_03+',' +value_04+',' +value_05+ '},\n';
  return code;
};

Blockly.Arduino['_06imi_espmap_loop'] = function(block) {
  // TODO: Assemble javascript into code variable.
  var code = '...\n';
  return code;
};

Blockly.Arduino['_07imi_espmap_isbutton'] = function(block) {
  // TODO: Assemble javascript into code variable.
  var code = '...';
  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.Arduino.ORDER_NONE];
};

Blockly.Arduino['_08imi_espmap_pubmqtt_mapset'] = function(block) {
  // TODO: Assemble javascript into code variable.
  var code = '...\n';
  return code;
};

Blockly.Arduino['_05imi_espmap_maps'] = function(block) {
  var statements_msg = Blockly.Arduino.statementToCode	(block, 'msg');
  // TODO: Assemble javascript into code variable.
  var code = 
  'int grid[4][6] = {\n'+
  statements_msg+
  '};\n';
  return code;
};