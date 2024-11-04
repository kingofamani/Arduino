Blockly.Arduino['_01imi_espcharge_init'] = function(block) {
  var statements_wifi = Blockly.Arduino.statementToCode(block, 'wifi');
  var statements_sheet = Blockly.Arduino.statementToCode(block, 'sheet');
  // TODO: Assemble javascript into code variable.
  Blockly.Arduino.definitions_['_01imi_espcharge_init'] = '#include <WiFi.h>\n #include <WiFiClientSecure.h>\n #include <Wire.h>\n #include <Adafruit_INA219.h>\n //https://docs.google.com/spreadsheets/d/1EhpZyQILsXqWKgGFPZdoaBGQzfcb2x20n4-tTqJc-uI/edit#gid=399078205\n //====變數設定 Start====\n ' + statements_wifi+statements_sheet + '//====變數設定 End====\n //asId不要變更\n const char* asId="AKfycbyR-Yp-uu4nIvnjvnkILaQ5AX8yFxp-UpBO-Sqs0su3ai1N_BvQsz_Q";\n  \n //測電流電壓\n float shuntvoltage = 0;\n float busvoltage = 0;\n float current_mA = 0;\n float loadvoltage = 0;\n float power_mW = 0;\n Adafruit_INA219 ina219Bat;//太陽能→14500鋰電池\n Adafruit_INA219 ina219Car;//14500鋰電池→小車\n //紀錄上一次上傳google sheet時間\n unsigned long preMillisBat;\n unsigned long preMillisCar;\n ';
  
  Blockly.Arduino.functions_['_01imi_espcharge_init'] = 'void setup_wifi() {\n  delay(10);\n  Serial.println();\n  Serial.print("Connecting to ");\n  Serial.println(ssid);\n  WiFi.mode(WIFI_STA);\n  WiFi.begin(ssid, password);\n  while (WiFi.status() != WL_CONNECTED) {\n    delay(500);\n    Serial.print(".");\n  }\n  Serial.println("");\n  Serial.println("WiFi connected");\n  Serial.println("IP address: ");\n  Serial.println(WiFi.localIP());\n}\nString URLEncode(const char* msg)\n{\n  const char *hex = "0123456789abcdef";\n  String encodedMsg = "";\n  while (*msg!=\'\\0\'){\n      if( (\'a\' <= *msg && *msg <= \'z\')\n              || (\'A\' <= *msg && *msg <= \'Z\')\n              || (\'0\' <= *msg && *msg <= \'9\') ) {\n          encodedMsg += *msg;\n      } else {\n          encodedMsg += \'%\';\n          encodedMsg += hex[*msg >> 4];\n          encodedMsg += hex[*msg & 15];\n      }\n      msg++;\n  }\n  return encodedMsg;\n}\nvoid  sendToGoogleSheets(const String& dateInclude,const String& data)\n{\n  sheetTag=URLEncode(sTag);\n  static WiFiClientSecure sheetClient;\n  sheetClient.setInsecure();\n  const char* host="script.google.com";\n  if (sheetClient.connect(host, 443)) {\n      const String url = String() +"https://"+host+"/macros/s/"+asId+"/exec?type=insert&dateInclude="+dateInclude+"&sheetId="+sheetId+"&sheetTag="+sheetTag+"&data="+data;\n      sheetClient.println("GET " + url + " HTTP/1.1");\n      sheetClient.println(String()+"Host: "+host);\n      sheetClient.println("Accept: */*");\n      sheetClient.println("Connection: close");\n      sheetClient.println();\n      sheetClient.println();\n      sheetClient.stop();\n  }\n}\nvoid batCharging(){\n    int interval = 31;//每隔幾秒紀錄一次\n  if(millis()-preMillisBat>=interval*1000){\n      preMillisBat = millis();\n      \n      shuntvoltage = ina219Bat.getShuntVoltage_mV();\n      busvoltage = ina219Bat.getBusVoltage_V();//Bus Voltage電池電壓(V)\n      current_mA = ina219Bat.getCurrent_mA();//Current負載電流(mA)\n      power_mW = ina219Bat.getPower_mW();//Power負載功率(mW)\n      loadvoltage = busvoltage + (shuntvoltage / 1000);//Load Voltage負載電壓(V)\n      \n      //寫入google試算表\n      if(power_mW>0){\n        sendToGoogleSheets("1",URLEncode((String() + "太陽能板產生能量" + "," + power_mW + "," + interval).c_str()));\n      }      \n  }   \n}\nvoid carCharging(){\n    int interval = 61;//每隔幾秒紀錄一次\n  if(millis()-preMillisCar>=interval*1000){\n      preMillisCar = millis();\n      \n      shuntvoltage = ina219Car.getShuntVoltage_mV();\n      busvoltage = ina219Car.getBusVoltage_V();//Bus Voltage電池電壓(V)\n      current_mA = ina219Car.getCurrent_mA();//Current負載電流(mA)\n      power_mW = ina219Car.getPower_mW();//Power負載功率(mW)\n      loadvoltage = busvoltage + (shuntvoltage / 1000);//Load Voltage負載電壓(V)\n      \n      //寫入google試算表\n      if(power_mW>0){\n        sendToGoogleSheets("1",URLEncode((String() + "小車消耗能量" + "," + power_mW + "," + interval).c_str()));\n      }      \n  }   \n}\n';
  
  Blockly.Arduino.setups_['_01imi_espcharge_init'] = '  Serial.begin(9600);\n  while (!Serial) {delay(1);}\n  delay(500);\n  setup_wifi();\n   \n  //測電流電壓初始\n  if (! ina219Bat.begin()) {\n    Serial.println("Failed to find ina219Bat chip");\n    while (1) { delay(10); }\n  }\n  if (! ina219Car.begin()) {\n    Serial.println("Failed to find ina219Car chip");\n    while (1) { delay(10); }\n  }\n';

  var code = '';
  return code;
};

Blockly.Arduino['_02imi_espcharge_wifi'] = function(block) {
  var value_ssid = Blockly.Arduino.valueToCode(block, 'ssid', Blockly.Arduino.ORDER_ATOMIC);
  var value_wifipwd = Blockly.Arduino.valueToCode(block, 'wifipwd', Blockly.Arduino.ORDER_ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code = '//WiFi'+'\n'+ 'const char* ssid = '+value_ssid+';'+'\n'+ 'const char* password = '+value_wifipwd+';'+'\n';

  return code;
};

Blockly.Arduino['_03imi_espcharge_sheet'] = function(block) {
  var value_sheetid = Blockly.Arduino.valueToCode(block, 'sheetid', Blockly.Arduino.ORDER_ATOMIC);
  var value_stag = Blockly.Arduino.valueToCode(block, 'stag', Blockly.Arduino.ORDER_ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code = '//google 試算表'+'\n'+ 'String sheetId='+value_sheetid+';//試算表id'+'\n'+ 'String sheetTag="";'+'\n'+ 'const char* sTag = '+value_stag+';//工作表名稱'+'\n';

  return code;
};

Blockly.Arduino['_04mi_espcharge_writesheet'] = function(block) {
  var dropdown_type = block.getFieldValue('type');
  // TODO: Assemble javascript into code variable.
  var code ="";
  if(dropdown_type=="sun"){
    code = "batCharging();\n";
  }else if(dropdown_type=="car"){
    code = "carCharging();\n";
  }

  return code;
};