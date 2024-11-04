Blockly.Arduino['_01amani_uart_init'] = function(block) {
	var serial = block.getFieldValue('serial');
	var rx = Blockly.Arduino.valueToCode(block, 'rx', Blockly.Arduino.ORDER_ATOMIC);  	
	var tx = Blockly.Arduino.valueToCode(block, 'tx', Blockly.Arduino.ORDER_ATOMIC); 	
    var baudrate = block.getFieldValue('baudrate');	
	var statement = Blockly.Arduino.statementToCode(block, 'statement');
	
	if (serial=="Serial") {
		if ('setupsTop_' in Blockly.Arduino)
			Blockly.Arduino.setupsTop_.setup_serial = serial+'.begin('+baudrate+');\n  delay(10);\n  ';
		else
			Blockly.Arduino.setups_.setup_serial = serial+'.begin('+baudrate+');\n  delay(10);\n  ';
	}
	else if (serial=="Serial1" || serial=="Serial2") {
		if ('setupsTop_' in Blockly.Arduino)
			Blockly.Arduino.setupsTop_["define_HardwareSerial_"+serial] = serial+'.begin('+baudrate+', SERIAL_8N1, '+rx+', '+tx+');\n  delay(10);\n  ';
		else
			Blockly.Arduino.setups_["define_HardwareSerial_"+serial] = serial+'.begin('+baudrate+', SERIAL_8N1, '+rx+', '+tx+');\n  delay(10);\n';	
	}	
	else if  (serial=="softSerial") {
		Blockly.Arduino.definitions_["define_SoftwareSerial"] = '#include <SoftwareSerial.h>\nSoftwareSerial '+serial+'('+rx+', '+tx+');';
		if ('setupsTop_' in Blockly.Arduino)
			Blockly.Arduino.setupsTop_["define_SoftwareSerial_"+serial] = serial+'.begin('+baudrate+');\n  delay(10);\n  ';
		else
			Blockly.Arduino.setups_["define_SoftwareSerial_"+serial] = serial+'.begin('+baudrate+');\n  delay(10);\n';
	}
	
	var code;
	code =	'if ('+serial+'.available()) {\n'+
				'  String serialMsg = "";\n'+
				'  while ('+serial+'.available()) {\n'+
				'    serialMsg = '+serial+'.readString();\n  '+statement+
				'  }\n'+	
				'}\n';
	
  return code;
};


Blockly.Arduino['_02amani_uart_get'] = function(block) {
  code = 'serialMsg';
  return [code, Blockly.Arduino.ORDER_NONE];
};

Blockly.Arduino['_03amani_uart_send'] = function(block) {
  var serial = block.getFieldValue('serial'); 
  var send = block.getFieldValue('send'); 
  var value_msg = Blockly.Arduino.valueToCode(block, 'msg', Blockly.Arduino.ORDER_ATOMIC);
  var code = "";
  if(send == "print"){
	code = serial+'.print(%1);\n'.replace("%1", value_msg);
  }else if(send == "println"){
	code = serial+'.println(%1);\n'.replace("%1", value_msg);
  }else if(send == "write"){
	code = serial+'.write(%1);\n'.replace("%1", value_msg);
  }
  return code;
};