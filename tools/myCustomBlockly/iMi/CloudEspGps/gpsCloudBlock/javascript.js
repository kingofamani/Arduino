Blockly.Arduino['_01imi_gpscloud_init'] = function(block) {
  var statements_uart = Blockly.Arduino.statementToCode(block, 'uart');
  Blockly.Arduino.definitions_['_01imi_gpscloud_init'] = '#include "arduino_secrets.h"\n #include "thingProperties.h"\n //=====變數設定 Start=====\n ' + statements_uart + '//=====變數設定 End=====\n double  Lats[4][6]={\n   {22.6364582999265,22.6364582999265,22.6364582999265,22.6364582999265,22.6364582999265,22.6364582999265},\n   {22.6349390408069,22.6349390408069,22.6349390408069,22.6349390408069,22.6349390408069,22.6349390408069},\n   {22.6334197816872,22.6334197816872,22.6334197816872,22.6334197816872,22.6334197816872,22.6334197816872},\n   {22.6319005225676,22.6319005225676,22.6319005225676,22.6319005225676,22.6319005225676,22.6319005225676}\n };\n double  Longs[4][6]={\n   {120.30257035839 , 120.304121598992, 120.305672839593 , 120.307224080195 , 120.308775320796 , 120.310326561398},\n   {120.30257035839 , 120.304121598992, 120.305672839593 , 120.307224080195 , 120.308775320796 , 120.310326561398},\n   {120.30257035839 , 120.304121598992, 120.305672839593 , 120.307224080195 , 120.308775320796 , 120.310326561398},\n   {120.30257035839 , 120.304121598992, 120.305672839593 , 120.307224080195 , 120.308775320796 , 120.310326561398}\n };\n int carX = 0;\n int carY = 0;\n ';

  var code = '';
  return code;
};

Blockly.Arduino['_02imi_gpscloud_uart'] = function(block) {
  var value_rx = Blockly.Arduino.valueToCode(block, 'rx', Blockly.Arduino.ORDER_ATOMIC);
  var value_tx = Blockly.Arduino.valueToCode(block, 'tx', Blockly.Arduino.ORDER_ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code = '//UART'+'\n'+ '#define U1RXD '+value_rx+'\n'+ '#define U1TXD '+value_tx+'\n';

  return code;
};

Blockly.Arduino['_03imi_gpscloud_setup'] = function(block) {
  // TODO: Assemble javascript into code variable.
  Blockly.Arduino.setups_['_03imi_gpscloud_setup'] = '  Serial.begin(115200);\n  Serial2.begin(9600, SERIAL_8N1, U1RXD, U1TXD);\n  delay(1500); \n  // Defined in thingProperties.h\n  initProperties();\n  // Connect to Arduino IoT Cloud\n  ArduinoCloud.begin(ArduinoIoTPreferredConnection);  \n  \n  setDebugMessageLevel(2);\n  ArduinoCloud.printDebugInfo();\n';

  var code = '';
  return code;
};

Blockly.Arduino['_04imi_gpscloud_loop'] = function(block) {
  // TODO: Assemble javascript into code variable.
  var code = 'ArduinoCloud.update();'+'\n';

  return code;
};

Blockly.Arduino['_05imi_gpscloud_getesp32xy'] = function(block) {
  // TODO: Assemble javascript into code variable.
  var code = 'String str = Serial2.readString();'+'\n'+ '  if(str !=""){'+'\n'+ '    carX = (int)(str.charAt(0) - \'0\');'+'\n'+ '    carY = (int)(str.charAt(1) - \'0\');'+'\n'+ '    Serial.println(carX);'+'\n'+ '    Serial.println(carY);'+'\n';

  return code;
};

Blockly.Arduino['_06imi_gpscloud_googlemap'] = function(block) {
  // TODO: Assemble javascript into code variable.
  var code = 'coordinates = {Lats[carX][carY], Longs[carX][carY]};\n}'+'\n';

  return code;
};