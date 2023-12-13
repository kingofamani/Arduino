javascript.javascriptGenerator.forBlock['imi_esp32car_init'] = function(block, generator) {
  var value_uart = generator.valueToCode(block, 'uart', javascript.Order.ATOMIC);
  var value_wifi = generator.valueToCode(block, 'wifi', javascript.Order.ATOMIC);
  var value_line = generator.valueToCode(block, 'line', javascript.Order.ATOMIC);
  var value_mqtt = generator.valueToCode(block, 'mqtt', javascript.Order.ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code = '...\n';
  return code;
};

javascript.javascriptGenerator.forBlock['imi_esp32car_init_uart'] = function(block, generator) {
  var value_rx = generator.valueToCode(block, 'rx', javascript.Order.ATOMIC);
  var value_tx = generator.valueToCode(block, 'tx', javascript.Order.ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code = '...';
  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.javascript.ORDER_NONE];
};

javascript.javascriptGenerator.forBlock['imi_esp32car_init_wifi'] = function(block, generator) {
  var value_ssid = generator.valueToCode(block, 'ssid', javascript.Order.ATOMIC);
  var value_wifi_pwd = generator.valueToCode(block, 'wifi_pwd', javascript.Order.ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code = '...';
  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.javascript.ORDER_NONE];
};

javascript.javascriptGenerator.forBlock['imi_esp32car_init_line'] = function(block, generator) {
  var value_line_token = generator.valueToCode(block, 'line_token', javascript.Order.ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code = '...';
  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.javascript.ORDER_NONE];
};

javascript.javascriptGenerator.forBlock['imi_esp32car_init_mqtt'] = function(block, generator) {
  var value_mqtt_user = generator.valueToCode(block, 'mqtt_user', javascript.Order.ATOMIC);
  var value_mqtt_pwd = generator.valueToCode(block, 'mqtt_pwd', javascript.Order.ATOMIC);
  var value_mqtt_port = generator.valueToCode(block, 'mqtt_port', javascript.Order.ATOMIC);
  var value_mqtt_server = generator.valueToCode(block, 'mqtt_server', javascript.Order.ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code = '...';
  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.javascript.ORDER_NONE];
};

javascript.javascriptGenerator.forBlock['imi_esp32car_loop'] = function(block, generator) {
  // TODO: Assemble javascript into code variable.
  var code = '...\n';
  return code;
};

javascript.javascriptGenerator.forBlock['imi_esp32car_getarduino_func'] = function(block, generator) {
  var statements_msg = generator.statementToCode(block, 'msg');
  // TODO: Assemble javascript into code variable.
  var code = '...\n';
  return code;
};

javascript.javascriptGenerator.forBlock['imi_esp32car_submqtt'] = function(block, generator) {
  var dropdown_mqtt_topic = block.getFieldValue('mqtt_topic');
  // TODO: Assemble javascript into code variable.
  var code = '...\n';
  return code;
};

javascript.javascriptGenerator.forBlock['imi_esp32car_mqttcallback_func'] = function(block, generator) {
  var statements_msg = generator.statementToCode(block, 'msg');
  // TODO: Assemble javascript into code variable.
  var code = '...\n';
  return code;
};

javascript.javascriptGenerator.forBlock['imi_esp32car_ismqtttopic'] = function(block, generator) {
  var dropdown_mqtt_topic = block.getFieldValue('mqtt_topic');
  // TODO: Assemble javascript into code variable.
  var code = '...';
  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.javascript.ORDER_NONE];
};

javascript.javascriptGenerator.forBlock['imi_esp32car_sendarduino_mapset'] = function(block, generator) {
  // TODO: Assemble javascript into code variable.
  var code = '...\n';
  return code;
};

javascript.javascriptGenerator.forBlock['imi_esp32car_pubmqtt_carstandby'] = function(block, generator) {
  // TODO: Assemble javascript into code variable.
  var code = '...\n';
  return code;
};

javascript.javascriptGenerator.forBlock['imi_esp32car_sendarduino_goodsload'] = function(block, generator) {
  // TODO: Assemble javascript into code variable.
  var code = '...\n';
  return code;
};

javascript.javascriptGenerator.forBlock['imi_esp32car_isarduinomsg'] = function(block, generator) {
  var dropdown_uart_topic = block.getFieldValue('uart_topic');
  // TODO: Assemble javascript into code variable.
  var code = '...';
  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.javascript.ORDER_NONE];
};

javascript.javascriptGenerator.forBlock['imi_esp32car_getarduino_recipient'] = function(block, generator) {
  // TODO: Assemble javascript into code variable.
  var code = '...\n';
  return code;
};

javascript.javascriptGenerator.forBlock['imi_esp32car_line_recipient'] = function(block, generator) {
  // TODO: Assemble javascript into code variable.
  var code = '...\n';
  return code;
};

javascript.javascriptGenerator.forBlock['imi_esp32car_getarduino_gps'] = function(block, generator) {
  // TODO: Assemble javascript into code variable.
  var code = '...\n';
  return code;
};

javascript.javascriptGenerator.forBlock['imi_esp32car_pubmqtt_cargps'] = function(block, generator) {
  // TODO: Assemble javascript into code variable.
  var code = '...\n';
  return code;
};