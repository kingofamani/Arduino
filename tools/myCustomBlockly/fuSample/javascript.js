Blockly.Arduino['fu_ez_digitalwrite'] = function(block) {
  var dropdown_led = block.getFieldValue('led');
  var pinRYG = [[16,12,13],[13,12,11],[13,14,15]];
  if (getBoardType()=="esp32")
	var pin = pinRYG[0][dropdown_led]; 
  else if (getBoardType()=="LinkIt")
	var pin = pinRYG[1][dropdown_led];
  else
	var pin = pinRYG[2][dropdown_led];  

  var dropdown_value = block.getFieldValue('value');

  //新增pinMode程式碼於setup區，NAME值須有固定格式綁定pin值。
  Blockly.Arduino.setups_['pinmode_' + pin] = 'pinMode('+ pin +', OUTPUT);';
  
  var code = 'digitalWrite(%1, %2);\n';
  code = code.replace("%1", pin );
  code = code.replace("%2", dropdown_value );
  return code;
};

Blockly.Arduino['fu_ez_digitalwrite_input'] = function(block) {
  var dropdown_led = block.getFieldValue('led');
  var pinRYG = [[16,12,13],[13,12,11],[13,14,15]];
  if (getBoardType()=="esp32")
	var pin = pinRYG[0][dropdown_led]; 
  else if (getBoardType()=="LinkIt")
	var pin = pinRYG[1][dropdown_led];
  else
	var pin = pinRYG[2][dropdown_led];

  var value_value = Blockly.Arduino.valueToCode(block, 'value', Blockly.Arduino.ORDER_ATOMIC); 

  Blockly.Arduino.setups_['pinmode_'+ pin] = 'pinMode('+ pin +', OUTPUT);';
  var code = 'digitalWrite('+ pin + ', ' + value_value +');\n';
  return code;
};

Blockly.Arduino['fu_ez_digitalwrite_input_relay'] = function(block) {
  if (getBoardType()=="esp32")
	var pin = 25; 
  else if (getBoardType()=="LinkIt")
	var pin = 5;
  else
	var pin = 9; 
  
  var value_value = Blockly.Arduino.valueToCode(block, 'value', Blockly.Arduino.ORDER_ATOMIC); 

  Blockly.Arduino.setups_['pinmode_'+ pin] = 'pinMode('+ pin +', OUTPUT);';
  
  var code = 'digitalWrite('+ pin +', '+ value_value +');\n';
  return code;
};

Blockly.Arduino['fu_ez_analogwrite_input'] = function(block) {
  if (getBoardType()=="esp32") 
	  var code = "";
  else {	
	  var dropdown_led = block.getFieldValue('led');
	  var pinRYG = [[16,12,13],[13,12,11],[13,14,15]];
	  if (getBoardType()=="esp32")
		var pin = pinRYG[0][dropdown_led]; 
	  else if (getBoardType()=="LinkIt")
		var pin = pinRYG[1][dropdown_led];
	  else
		var pin = pinRYG[2][dropdown_led];

	  var value_value = Blockly.Arduino.valueToCode(block, 'value', Blockly.Arduino.ORDER_ATOMIC);

	  Blockly.Arduino.setups_['pinmode_'+ pin] = 'pinMode('+ pin +', OUTPUT);';
	  var code = 'analogWrite('+ pin +', '+ value_value +');\n';
  }
  return code;
};

Blockly.Arduino['fu_ez_analogwrite_input_esp'] = function(block) {
  if (getBoardType()!="esp32") 
	  var code = "";
  else {	
	  var dropdown_led = block.getFieldValue('led');
	  var pinRYG = [[16,12,13],[13,12,11],[13,14,15]];
	  if (getBoardType()=="esp32")
		var pin = pinRYG[0][dropdown_led]; 
	  else if (getBoardType()=="LinkIt")
		var pin = pinRYG[1][dropdown_led];
	  else
		var pin = pinRYG[2][dropdown_led];

	  var value_value = Blockly.Arduino.valueToCode(block, 'value', Blockly.Arduino.ORDER_ATOMIC);
	  var value_channel = Blockly.Arduino.valueToCode(block, 'channel', Blockly.Arduino.ORDER_ATOMIC);
	 
	  Blockly.Arduino.setups_['ledc_'+ pin] = 'ledcAttachPin('+ pin +','+ value_channel +');\n  '+
													   'ledcSetup('+ value_channel +',5000,8);';
	  var code = 'ledcWrite(%1, %2);\n';
	  code = code.replace("%1", value_channel);
	  code = code.replace("%2", value_value);
  }
  return code;
};

Blockly.Arduino['fu_ez_digitalread'] = function(block) {
  var dropdown_button = block.getFieldValue('button');	
  var pinButton = [[5,36],[0,7],[5,11]];  
  if (getBoardType()=="esp32")
	var pin = pinButton[0][dropdown_button];
  else if (getBoardType()=="LinkIt")
	var pin = pinButton[1][dropdown_button];
  else
	var pin = pinButton[2][dropdown_button];
  
  Blockly.Arduino.setups_['pinmode_'+ pin] = 'pinMode('+ pin +', INPUT_PULLUP);';
  
  var code = 'digitalRead('+ pin +')' ;
  return [code, Blockly.Arduino.ORDER_NONE];
};

Blockly.Arduino['fu_ez_digitalread_button'] = function(block) {
  var dropdown_type = block.getFieldValue('type');	
  var pinButton = [[5,36],[0,7],[5,11]];  
  if (getBoardType()=="esp32") {
	var pinA = pinButton[0][0];
	var pinB = pinButton[0][1];	
  }
  else if (getBoardType()=="LinkIt") {
	var pinA = pinButton[1][0];
	var pinB = pinButton[1][1];
  }
  else {
	var pinA = pinButton[2][0];
	var pinB = pinButton[2][1];
  }
  
  if (dropdown_type == "A") {
	Blockly.Arduino.setups_['pinmode_'+ pinA] = 'pinMode('+ pinA +', INPUT_PULLUP);';	  
	var code = 'digitalRead('+ pinA +')==0' ;
  }
  else if (dropdown_type == "B") {
	Blockly.Arduino.setups_['pinmode_'+ pinB] = 'pinMode('+ pinB +', INPUT_PULLUP);';
	var code = 'digitalRead('+ pinB +')==0' ;
  }
  else if (dropdown_type == "AB") {
	Blockly.Arduino.setups_['pinmode_'+ pinA] = 'pinMode('+ pinA +', INPUT_PULLUP);';
    Blockly.Arduino.setups_['pinmode_'+ pinB] = 'pinMode('+ pinB +', INPUT_PULLUP);';
	Blockly.Arduino.definitions_['digitalRead_AB'] = ''+
	    'int pressButtonAB() {\n'+
		'  if ((digitalRead('+ pinA +')==0) || (digitalRead('+ pinB +')==0)) {\n' +
		'    delay(200);\n'+
		'    return (digitalRead('+ pinA +')==0) && (digitalRead('+ pinB +')==0);\n'+
		'  }\n'+			
		'  else \n'+		
		'    return 0;\n'+
		'}';
	var code = 'pressButtonAB()';
  }
  
  return [code, Blockly.Arduino.ORDER_NONE];
};

Blockly.Arduino['fu_ez_analogread_potentiometer'] = function(block) {
  if (getBoardType()=="esp32")
	var pin = 34; 
  else if (getBoardType()=="LinkIt")
	var pin = 16;
  else
	var pin = 2; 

  Blockly.Arduino.setups_['pinmode_'+ pin] = 'pinMode('+ pin +', INPUT);';
	
  var code = 'analogRead('+ pin +')' ;
  return [code, Blockly.Arduino.ORDER_NONE];
};

Blockly.Arduino['fu_ez_analogread_photoresistor'] = function(block) {
  if (getBoardType()=="esp32")
	var pin = 39; 
  else if (getBoardType()=="LinkIt")
	var pin = 15;
  else
	var pin = 1; 

  Blockly.Arduino.setups_['pinmode_'+ pin] = 'pinMode('+ pin +', INPUT);';
  
  var code = 'analogRead('+ pin +')' ;
  return [code, Blockly.Arduino.ORDER_NONE];
};

Blockly.Arduino['fu_ez_buzzer_tone'] = function(block) {
  if (getBoardType()=="esp32") 
	  var code = "";
  else {		
	  if (getBoardType()=="esp32")
		var pin = 14; 
	  else if (getBoardType()=="LinkIt")
		var pin = 14;
	  else
		var pin = 0; 

	  var value_frequency = Blockly.Arduino.valueToCode(block, 'frequency', Blockly.Arduino.ORDER_ATOMIC);
	 
	  Blockly.Arduino.setups_['pinmode_'+ pin] = 'pinMode('+ pin +', OUTPUT);';
	  var code = 'tone('+ pin +', '+ value_frequency +');\n' ;
  }
  return code;
};

Blockly.Arduino['fu_ez_buzzer_tone_duration'] = function(block) {
  if (getBoardType()=="esp32") 
	  var code = "";
  else {	
	  if (getBoardType()=="esp32")
		var pin = 14; 
	  else if (getBoardType()=="LinkIt")
		var pin = 14;
	  else
		var pin = 0; 

	  var value_frequency = Blockly.Arduino.valueToCode(block, 'frequency', Blockly.Arduino.ORDER_ATOMIC);
	  var value_duration = Blockly.Arduino.valueToCode(block, 'duration', Blockly.Arduino.ORDER_ATOMIC);

	  Blockly.Arduino.setups_['pinmode_'+ pin] = 'pinMode('+ pin +', OUTPUT);';
	  var code = 'tone('+ pin +', '+ value_frequency +', '+ value_duration +');\n' ;
  }
  return code;
};

Blockly.Arduino['fu_ez_buzzer_tone_duration_esp'] = function(block) {
  if (getBoardType()!="esp32") 
	  var code = "";
  else {	
	  if (getBoardType()=="esp32")
		var pin = 14; 
	  else if (getBoardType()=="LinkIt")
		var pin = 14;
	  else
		var pin = 0; 

	  var value_frequency = Blockly.Arduino.valueToCode(block, 'frequency', Blockly.Arduino.ORDER_ATOMIC);
	  var value_duration = Blockly.Arduino.valueToCode(block, 'duration', Blockly.Arduino.ORDER_ATOMIC);
	  var value_channel = Blockly.Arduino.valueToCode(block, 'channel', Blockly.Arduino.ORDER_ATOMIC);

	  Blockly.Arduino.setups_['ledc_'+ pin] = 'ledcSetup('+value_channel+',2000,8);\n'+
											  '  ledcAttachPin('+pin+','+value_channel+');'; 
	  Blockly.Arduino.definitions_['tone'] = 'void tone(int channel, int frequency, int delaytime, ) {\n'+
											 '  ledcWriteTone(channel, frequency);\n'+
											 '  delay(delaytime);\n'+
											 '  ledcWriteTone(channel, 0);\n'+
											 '}';

	  var code = 'tone('+ value_channel +','+ value_frequency +', '+ value_duration +');\n' ;
  }
  return code;
};

Blockly.Arduino['fu_ez_buzzer_tone_duration_esp_array'] = function(block) {
  if (getBoardType()!="esp32") 
	  var code = "";
  else {
	  if (getBoardType()=="esp32")
		var pin = 14; 
	  else if (getBoardType()=="LinkIt")
		var pin = 14;
	  else
		var pin = 0; 

	  var value_frequency = Blockly.Arduino.valueToCode(block, 'frequency', Blockly.Arduino.ORDER_ATOMIC);
	  var value_duration = Blockly.Arduino.valueToCode(block, 'duration', Blockly.Arduino.ORDER_ATOMIC);
	  var value_channel = Blockly.Arduino.valueToCode(block, 'channel', Blockly.Arduino.ORDER_ATOMIC);  

	  Blockly.Arduino.setups_['ledc_'+ pin] = 'ledcSetup('+value_channel+',2000,8);\n'+
											  '  ledcAttachPin('+pin+','+value_channel+');'; 
	  Blockly.Arduino.definitions_['toneArray'] = 'void toneArray(String frequency, String delaytime, int channel) {\n'+
													  '  String f="",d="",split=",";\n'+
													  '  int s1=0;\n'+
													  '  frequency+=",";\n'+
													  '  delaytime+=",";\n'+
													  '  for (int i=0;i<frequency.length();i++) {\n'+
													  '    if (frequency[i]==split[0]) {\n'+
													  '  	   f=frequency.substring(s1,i);\n'+
													  '  	   s1=i+1;\n'+
													  '  	   for (int j=0;j<delaytime.length();j++) {\n'+
													  '  	      if (delaytime[j]==split[0]) {\n'+
													  '  		    d=delaytime.substring(0,j);\n'+
													  '  		    ledcWriteTone(channel, f.toInt());\n'+
													  '  		    delay(d.toInt());\n'+
													  '  		    delaytime=delaytime.substring(j+1);\n'+
													  '  		    break;\n'+
													  '  	      }\n'+
													  '  	    }\n'+
													  '    }\n'+
													  '  }\n'+
													  '  ledcWriteTone(channel, 0);\n'+
													  '}';

	  var v = Blockly.getMainWorkspace().getVariablesOfType("");
	  var f1 = '"', f2 = '"', d1 = '"', d2 = '"'; 
	  for (var i=0;i<v.length;i++) {
		if (value_frequency==v[i].name) {
			f1="String(";
			f2=")";
		}
		if (value_duration==v[i].name) {
			d1="String(";
			d2=")";
		}
	  }
	  var code = 'toneArray('+f1+value_frequency.toString().replace(/"|'|{|}| /g,"")+f2+','+d1+ value_duration.toString().replace(/"|'|{|}| /g,"") +d2+','+ value_channel +');\n' ;
  }
  return code;
};

Blockly.Arduino['fu_ez_buzzer_notone'] = function(block) {
  if (getBoardType()=="esp32") 
	  var code = "";
  else {	
	  if (getBoardType()=="esp32")
		var pin = 14; 
	  else if (getBoardType()=="LinkIt")
		var pin = 14;
	  else
		var pin = 0; 

	  Blockly.Arduino.setups_['pinmode_'+ pin] = 'pinMode('+ pin +', OUTPUT);';
	  
	  var code = 'noTone('+ pin +');\n';
  }
  return code;
};

Blockly.Arduino['fu_ez_dht11'] = function(block) {
  if (getBoardType()=="esp32")
	var pin = 15; 
  else if (getBoardType()=="LinkIt")
	var pin = 10;
  else
	var pin = 16; 

  var dropdown_type = block.getFieldValue('type');

  Blockly.Arduino.definitions_['dht11_library'] = '#include <DHT.h>';
  Blockly.Arduino.definitions_['dht11_'+ pin] = 'DHT dht ('+ pin +', DHT11);';
  Blockly.Arduino.setups_['dht11_begin'] = 'dht.begin();';
  var code = dropdown_type;
  return [code, Blockly.Arduino.ORDER_NONE];
};

Blockly.Arduino['fu_ez_pixel_rgb'] = function(block) {
  var pin = 26;
  if (getBoardType()=="esp32")
	var pin = 26; 
  else if (getBoardType()=="LinkIt")
	var pin = 4;
  else
	var pin = 12;

  var dropdown_no = block.getFieldValue('no');
  var value_r = Blockly.Arduino.valueToCode(block, 'R', Blockly.Arduino.ORDER_ATOMIC);
  var value_g = Blockly.Arduino.valueToCode(block, 'G', Blockly.Arduino.ORDER_ATOMIC);
  var value_b = Blockly.Arduino.valueToCode(block, 'B', Blockly.Arduino.ORDER_ATOMIC);

  Blockly.Arduino.definitions_['pixel_'+ pin] = '#include <Adafruit_NeoPixel.h>\n'+
												'Adafruit_NeoPixel pixels(3, '+ pin +', NEO_GRB + NEO_KHZ800);';
  Blockly.Arduino.setups_['pixel_'+ pin] = 'pixels.begin();\n'+
										   '  pixels.clear();';

  var code= 'pixels.setPixelColor('+ dropdown_no +', pixels.Color('+value_r+', '+value_g+', '+value_b+'));\n'+
			'pixels.show();\n';
  return code;
};

Blockly.Arduino['fu_ez_pixel_clear'] = function(block) {
  var code = 'pixels.clear();\n';
  return code;
};

Blockly.Arduino['fu_ez_pixel_picker'] = function(block) {
  if (getBoardType()=="esp32")
	var pin = 26; 
  else if (getBoardType()=="LinkIt")
	var pin = 4;
  else
	var pin = 12; 

  var dropdown_no = block.getFieldValue('no');
  var colour_value = block.getFieldValue('value');

  Blockly.Arduino.definitions_['pixel_'+ pin] = '#include <Adafruit_NeoPixel.h>\n'+
												'Adafruit_NeoPixel pixels(3, '+ pin +', NEO_GRB + NEO_KHZ800);';
  Blockly.Arduino.setups_['pixel_'+ pin] = 'pixels.begin();\n'+
										   '  pixels.clear();';

  var code= 'pixels.setPixelColor('+ dropdown_no +', pixels.Color('+hexToRgb(colour_value).r+', '+hexToRgb(colour_value).g+', '+hexToRgb(colour_value).b+'));\n'+
			'pixels.show();\n';
  return code;
};

function hexToRgb(hex) {
  var result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
  return result ? {
    r: parseInt(result[1], 16),
    g: parseInt(result[2], 16),
    b: parseInt(result[3], 16)
  } : null;
}

Blockly.Arduino['fu_ez_pixel_clear'] = function(block) {
  var code = 'pixels.clear();\n';
  return code;
};

Blockly.Arduino['fu_ez_ir_receive'] = function(block) {
  if (getBoardType()=="esp32")
	var pin = 33; 
  else if (getBoardType()=="LinkIt")
	var pin = 17;
  else
	var pin = 8; 

  var variable_value = Blockly.Arduino.nameDB_.getName(block.getFieldValue('value'), Blockly.Variables.NAME_TYPE);
  var variable_type = Blockly.Arduino.nameDB_.getName(block.getFieldValue('type'), Blockly.Variables.NAME_TYPE);
  var statements_execute = Blockly.Arduino.statementToCode(block, 'execute');
  
  Blockly.Arduino.definitions_['ir_definition'] = '#include <IRremote.h>\nIRrecv irrecv('+pin+');\ndecode_results results;';
  Blockly.Arduino.setups_['ir_setup'] = 'irrecv.enableIRIn();';
  Blockly.Arduino.definitions_['ir_getIrType'] = 'String getIrType(int type) {\n' +
										   '  if (type==1)\n' +
										   '   return "NEC";\n' +
										   '  else if (type==2)\n' +
										   '   return "SONY";\n' +
										   '  else if (type==3)\n' +
										   '   return "RC5";\n' +
										   '  else if (type==4)\n' +
										   '   return "RC6";\n' +
										   '  else if (type==5)\n' +
										   '   return "DISH";\n' +
										   '  else if (type==6)\n' +
										   '   return "SHARP";\n' +
										   '  else if (type==7)\n' +
										   '   return "PANASONIC";\n' +
										   '  else if (type==8)\n' +
										   '   return "JVC";\n' +
										   '  else if (type==9)\n' +
										   '   return "SANYO";\n' +
										   '  else if (type==10)\n' +
										   '   return "MITSUBISHI";\n' +
										   '  else\n' +
										   '   return "UNKNOWN";\n' +										   
										   '}';										   
  var code = 'if (irrecv.decode(&results)) {\n'+
			 '  String '+variable_value+' = String(results.value, HEX);\n'+
			 '  String '+variable_type+' = getIrType(results.decode_type);\n'+
			 statements_execute +
			 '  irrecv.resume();\n'+
			 '}\n'+
			 'delay(300);';
  return code;
};


Blockly.Arduino['fu_ez_oled_draw'] = function(block) {
  var statements_draw = Blockly.Arduino.statementToCode(block, 'draw');
  
  Blockly.Arduino.definitions_['u8g2_definition'] = '#include <U8g2lib.h>\n'+
												  '#include <Wire.h>\n'+
												  'U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);';												  
  Blockly.Arduino.setups_['u8g2_setup'] = 'u8g2.begin();\n  '+
										  'u8g2.setFont(u8g2_font_ncenB08_tr);';
  
  var code = 'u8g2.clearBuffer();\n'+ 
			 statements_draw +
			 'u8g2.sendBuffer();\n';
  return code;
};

Blockly.Arduino['fu_ez_oled_drawstr'] = function(block) {
  var value_x = Blockly.Arduino.valueToCode(block, 'x', Blockly.Arduino.ORDER_ATOMIC);
  var value_y = Blockly.Arduino.valueToCode(block, 'y', Blockly.Arduino.ORDER_ATOMIC);
  var value_str = Blockly.Arduino.valueToCode(block, 'str', Blockly.Arduino.ORDER_ATOMIC);

  var code = 'u8g2.drawStr('+value_x+','+value_y+',String('+value_str+').c_str());\n';
  return code;
};