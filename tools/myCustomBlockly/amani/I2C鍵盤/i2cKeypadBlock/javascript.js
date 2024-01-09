Blockly.Arduino['_01amani_i2ckeypad_init'] = function(block) {
  Blockly.Arduino.definitions_['_01amani_i2ckeypad_init'] = '#include <Wire.h>\nchar i2cKey = \'\\0\';  //不能是null\n';

  Blockly.Arduino.setups_['_01amani_i2ckeypad_init'] = 'Wire.begin();\n';
  
  Blockly.Arduino.functions_['_01amani_i2ckeypad_init'] = 'void keypadLoop() {\n  volatile int code;\n  Wire.beginTransmission(0x27);\n  Wire.write(3);\n  Wire.endTransmission();\n  Wire.requestFrom(0x27, 1);\n  while (Wire.available()) {\n    char code = Wire.read();\n    if (code != 16) {\n      i2cKey = getKeyChar(code);\n    }\n  }\n}\nchar getKeyChar(char code) {\n  char keys[16] = {\n    \'0\', \'1\', \'2\', \'3\',\n    \'4\', \'5\', \'6\', \'7\',\n    \'8\', \'9\', \'A\', \'B\',\n    \'C\', \'D\', \'*\', \'#\'\n  };\n  return keys[code];\n}\nint charToInt(char c) {\n  int num = c - \'0\';\n  return num;\n}\nboolean checkIsNumber(char key) {\n  char N[] = "1234567890";\n  //一定要大寫NULL\n  if ((strchr(N, key)) != (NULL)) {\n    return (true);\n  } else {\n    return (false);\n  }\n}\n';

  var code = '';
  return code;
};

Blockly.Arduino['_02amani_i2ckeypad_loop'] = function(block) {
  // TODO: Assemble javascript into code variable.
  var code = 'keypadLoop();'+'\n';

  return code;
};

Blockly.Arduino['_03amani_i2ckeypad_iskey'] = function(block) {
  // TODO: Assemble javascript into code variable.
  var code = 'i2cKey !=\'\\0\'';

  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.Arduino.ORDER_NONE];
};

Blockly.Arduino['_04amani_i2ckeypad_key'] = function(block) {
  // TODO: Assemble javascript into code variable.
  var code = 'i2cKey';

  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.Arduino.ORDER_NONE];
};

Blockly.Arduino['_05amani_i2ckeypad_keynull'] = function(block) {
  // TODO: Assemble javascript into code variable.
  var code = 'i2cKey =\'\\0\';'+'\n';

  return code;
};

Blockly.Arduino['_06amani_i2ckeypad_funcnum'] = function(block) {
  // TODO: Assemble javascript into code variable.  
  var value_c = Blockly.Arduino.valueToCode(block, 'c', Blockly.Arduino.ORDER_ATOMIC);
  
  var code = 'charToInt('+value_c+')';

  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.Arduino.ORDER_NONE];
};

Blockly.Arduino['_07amani_i2ckeypad_isnum'] = function(block) {
  // TODO: Assemble javascript into code variable.  
  var value_c = Blockly.Arduino.valueToCode(block, 'c', Blockly.Arduino.ORDER_ATOMIC);
  
  var code = 'checkIsNumber('+value_c+')';

  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.Arduino.ORDER_NONE];
};