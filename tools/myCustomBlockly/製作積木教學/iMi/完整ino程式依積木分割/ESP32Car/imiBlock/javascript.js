Blockly.Arduino['imi_esp32car_init'] = function(block) {
  var value_uart = generator.valueToCode(block, 'uart', javascript.Order.ATOMIC);
  var value_wifi = generator.valueToCode(block, 'wifi', javascript.Order.ATOMIC);
  var value_line = generator.valueToCode(block, 'line', javascript.Order.ATOMIC);
  var value_mqtt = generator.valueToCode(block, 'mqtt', javascript.Order.ATOMIC);
  // TODO: Assemble javascript into code variable.
  

  var code = '123';
  return code;
};

Blockly.Arduino['imi_esp32car_init_uart'] = function(block) {
  var value_rx = generator.valueToCode(block, 'rx', javascript.Order.ATOMIC);
  var value_tx = generator.valueToCode(block, 'tx', javascript.Order.ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code ='//UART通訊'+'\n '+'SoftwareSerial MegaSerial('+value_rx+',' +value_tx+');'+'\n ';

  return [code, Blockly.javascript.ORDER_NONE];
};

Blockly.Arduino['imi_esp32car_init_wifi'] = function(block) {
  var value_ssid = generator.valueToCode(block, 'ssid', javascript.Order.ATOMIC);
  var value_wifi_pwd = generator.valueToCode(block, 'wifi_pwd', javascript.Order.ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code ='//WiFi設定'+'\n '+'const char* ssid ="' +value_ssid+'";'+'\n '+'const char* password ="' +value_wifi_pwd+'";'+'\n ';

  return [code, Blockly.javascript.ORDER_NONE];
};

Blockly.Arduino['imi_esp32car_init_line'] = function(block) {
  var value_line_token = generator.valueToCode(block, 'line_token', javascript.Order.ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code ='//LINE權杖'+'\n '+'String lineToken ="' +value_line_token+'";'+'\n ';

  return [code, Blockly.javascript.ORDER_NONE];
};

Blockly.Arduino['imi_esp32car_init_mqtt'] = function(block) {
  var value_mqtt_user = generator.valueToCode(block, 'mqtt_user', javascript.Order.ATOMIC);
  var value_mqtt_pwd = generator.valueToCode(block, 'mqtt_pwd', javascript.Order.ATOMIC);
  var value_mqtt_port = generator.valueToCode(block, 'mqtt_port', javascript.Order.ATOMIC);
  var value_mqtt_server = generator.valueToCode(block, 'mqtt_server', javascript.Order.ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code ='//---- HiveMQ設定 Start -----'+'\n '+'const char* mqtt_server = "' +value_mqtt_server +'";'+'\n '+'const char* mqtt_username ="' +value_mqtt_user+'";'+'\n '+'const char* mqtt_password ="' +value_mqtt_pwd+'";'+'\n '+'const int mqtt_port =' +value_mqtt_port+';'+'\n ';

  return [code, Blockly.javascript.ORDER_NONE];
};

Blockly.Arduino['imi_esp32car_loop'] = function(block) {
  // TODO: Assemble javascript into code variable.
  var code ='//MQTT啟動\n  client.loop();\n  //接收訊息：Mega→ESP32\n    UartGetFromMega();\n';

  return code;
};

Blockly.Arduino['imi_esp32car_getarduino_func'] = function(block) {
  var statements_msg = generator.statementToCode(block, 'msg');
  Blockly.Arduino.functions_['imi_esp32car_getArduino_func'] = '//接收訊息：Mega→ESP32\n void UartGetFromMega() {  \n   while (MegaSerial.available()) {\n     String str = MegaSerial.readString();\n     Serial.println(str);\n}//while\n }\n ';

  var code = '';
  return code;
};

Blockly.Arduino['imi_esp32car_submqtt'] = function(block) {
  var dropdown_mqtt_topic = block.getFieldValue('mqtt_topic');
  // TODO: Assemble javascript into code variable.
  Blockly.Arduino.setups_['imi_esp32car_submqtt'+dropdown_mqtt_topic] = 'client.subscribe('+dropdown_mqtt_topic+');\n';

  var code = '';
  return code;
};

Blockly.Arduino['imi_esp32car_mqttcallback_func'] = function(block) {
  var statements_msg = generator.statementToCode(block, 'msg');
  Blockly.Arduino.functions_['imi_esp32car_mqttcallback_func'] = '//訂閱的主題回覆\n void callback(char* topic, byte* payload, unsigned int length) {\n   mqttGetMsg = "";\n   for (int i = 0; i < length; i++) {\n     mqttGetMsg += (char)payload[i];\n   }\n   mqttGetMsg.trim();\n   Serial.println(String(topic));\n   Serial.println(mqttGetMsg);\n ' + statements_msg + '}\n ';

  var code = '';
  return code;
};

Blockly.Arduino['imi_esp32car_ismqtttopic'] = function(block) {
  var dropdown_mqtt_topic = block.getFieldValue('mqtt_topic');
  var code ='String(topic) ==' +dropdown_mqtt_topic;

  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.javascript.ORDER_NONE];
};

Blockly.Arduino['imi_esp32car_sendarduino_mapset'] = function(block) {
  var code ='//儲存地圖陣列(格式:MAP_SET,4x6地圖陣列)\n     UartSentToMega(String(MAP_SET) + "," + mqttGetMsg);\n     delay(1000);\n ';

  return code;
};

Blockly.Arduino['imi_esp32car_pubmqtt_carstandby'] = function(block) {
  var code ='//發送MQTT：TOPIC_CAR_STANDBY\n     mqttSendMsg = "1";\n     client.publish(TOPIC_CAR_STANDBY, mqttSendMsg);\n ';

  return code;
};

Blockly.Arduino['imi_esp32car_sendarduino_goodsload'] = function(block) {
  var code ='//開始送貨(格式:GOODS_LOAD,姓名,商品,倉庫X,倉庫Y,收件人X,收件人Y)\n     UartSentToMega(String(GOODS_LOAD) + "," + mqttGetMsg);\n ';

  return code;
};

Blockly.Arduino['imi_esp32car_isarduinomsg'] = function(block) {
  var dropdown_uart_topic = block.getFieldValue('uart_topic');
  // TODO: Assemble javascript into code variable.
  var code ='str.indexOf('+dropdown_uart_topic+') != -1';

  return [code, Blockly.javascript.ORDER_NONE];
};

Blockly.Arduino['imi_esp32car_getarduino_recipient'] = function(block) {
  var code ='//收貨人資料字串轉陣列\n       String tmpArray[3];\n       char* token = strtok((char*)str.c_str(), ",");\n       int tokenLen = 0;\n       while (token != NULL && tokenLen < 3) {\n         tmpArray[tokenLen] = token;\n         token = strtok(NULL, ",");\n         tokenLen++;\n       }\n ';

  return code;
};

Blockly.Arduino['imi_esp32car_line_recipient'] = function(block) {
  // TODO: Assemble javascript into code variable.
  var code ='//發送LINE\n       sendLineMsg(tmpArray[1] + "您好：您的商品：「" + tmpArray[2] + "」已送達，請至門口進行人臉識別簽收。");\n ';

  return code;
};

Blockly.Arduino['imi_esp32car_getarduino_gps'] = function(block) {
  // TODO: Assemble javascript into code variable.
  var code ='//座標字串轉陣列\n       String arryGps[3];\n       char* token = strtok((char*)str.c_str(), ",");\n       int tokenLen = 0;\n       while (token != NULL && tokenLen < 3) {\n         arryGps[tokenLen] = token;\n         token = strtok(NULL, ",");\n         tokenLen++;\n       }\n ';

  return code;
};

Blockly.Arduino['imi_esp32car_pubmqtt_cargps'] = function(block) {
  // TODO: Assemble javascript into code variable.
  var code ='//發送MQTT：TOPIC_CAR_GPS(格式:xy)\n       //    使用String結合x和y的內容\n       String xy = arryGps[1] + arryGps[2];\n       //    將String轉換為const char*\n       const char* msg = (xy).c_str();\n       //    const char*轉char*\n       mqttSendMsg = const_cast<char*>(msg);\n       client.publish(TOPIC_CAR_GPS, mqttSendMsg);\n ';

  return code;
};