Blockly.Arduino['_01imi_espgoods_init'] = function(block) {
  var statements_wifi = Blockly.Arduino.statementToCode(block, 'wifi');
  var statements_mqtt = Blockly.Arduino.statementToCode(block, 'mqtt');
  var statements_uart = Blockly.Arduino.statementToCode(block, 'uart');
  var statements_sheet = Blockly.Arduino.statementToCode(block, 'sheet');
  // TODO: Assemble javascript into code variable.
  Blockly.Arduino.definitions_['_01imi_espgoods_init'] = '#include <WiFi.h>\n #define ARDUINOJSON_DECODE_UNICODE 1\n #include <ArduinoJson.h>\n #include <WiFiClientSecure.h>\n #include <PubSubClient.h>\n #include <SoftwareSerial.h>\n //===設定變數 Start===\n ' + statements_wifi+statements_mqtt+statements_uart+statements_sheet + '//===設定變數 End===\n String sheetTag="";\n //asId不要變更\n const char* asId="AKfycbyR-Yp-uu4nIvnjvnkILaQ5AX8yFxp-UpBO-Sqs0su3ai1N_BvQsz_Q";\n DynamicJsonDocument docSheet(2048);\n //收件人資料(格式:姓名,商品,倉庫X,倉庫Y,收件人X,收件人Y)\n String recipient[6];\n String strRecipient="";\n //Topic主題\n const char* TOPIC_MAP_SET = "imiRobot/map/set";\n const char* TOPIC_CAR_STANDBY = "imiRobot/car/standby";\n const char* TOPIC_CAR_GPS = "imiRobot/car/gps";\n const char* TOPIC_GOODS_LOAD = "imiRobot/goods/load";\n const char* TOPIC_CAR_LOWPOWER = "imiRobot/car/lowPower";\n //UART\n const char* GOODS_LOAD = "goodsLoad";\n //發佈者 傳送的消息內容\n char* mqttSendMsg = "";\n //訂閱者 接收的消息內容\n String mqttGetMsg = "";\n WiFiClientSecure espClient;\n PubSubClient client(espClient);\n // HiveMQ Cloud\n static const char* root_ca PROGMEM = R"EOF(\n -----BEGIN CERTIFICATE-----\n MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw\n TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh\n cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMTUwNjA0MTEwNDM4\n WhcNMzUwNjA0MTEwNDM4WjBPMQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJu\n ZXQgU2VjdXJpdHkgUmVzZWFyY2ggR3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBY\n MTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAK3oJHP0FDfzm54rVygc\n h77ct984kIxuPOZXoHj3dcKi/vVqbvYATyjb3miGbESTtrFj/RQSa78f0uoxmyF+\n 0TM8ukj13Xnfs7j/EvEhmkvBioZxaUpmZmyPfjxwv60pIgbz5MDmgK7iS4+3mX6U\n A5/TR5d8mUgjU+g4rk8Kb4Mu0UlXjIB0ttov0DiNewNwIRt18jA8+o+u3dpjq+sW\n T8KOEUt+zwvo/7V3LvSye0rgTBIlDHCNAymg4VMk7BPZ7hm/ELNKjD+Jo2FR3qyH\n B5T0Y3HsLuJvW5iB4YlcNHlsdu87kGJ55tukmi8mxdAQ4Q7e2RCOFvu396j3x+UC\n B5iPNgiV5+I3lg02dZ77DnKxHZu8A/lJBdiB3QW0KtZB6awBdpUKD9jf1b0SHzUv\n KBds0pjBqAlkd25HN7rOrFleaJ1/ctaJxQZBKT5ZPt0m9STJEadao0xAH0ahmbWn\n OlFuhjuefXKnEgV4We0+UXgVCwOPjdAvBbI+e0ocS3MFEvzG6uBQE3xDk3SzynTn\n jh8BCNAw1FtxNrQHusEwMFxIt4I7mKZ9YIqioymCzLq9gwQbooMDQaHWBfEbwrbw\n qHyGO0aoSCqI3Haadr8faqU9GY/rOPNk3sgrDQoo//fb4hVC1CLQJ13hef4Y53CI\n rU7m2Ys6xt0nUW7/vGT1M0NPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNV\n HRMBAf8EBTADAQH/MB0GA1UdDgQWBBR5tFnme7bl5AFzgAiIyBpY9umbbjANBgkq\n hkiG9w0BAQsFAAOCAgEAVR9YqbyyqFDQDLHYGmkgJykIrGF1XIpu+ILlaS/V9lZL\n ubhzEFnTIZd+50xx+7LSYK05qAvqFyFWhfFQDlnrzuBZ6brJFe+GnY+EgPbk6ZGQ\n 3BebYhtF8GaV0nxvwuo77x/Py9auJ/GpsMiu/X1+mvoiBOv/2X/qkSsisRcOj/KK\n NFtY2PwByVS5uCbMiogziUwthDyC3+6WVwW6LLv3xLfHTjuCvjHIInNzktHCgKQ5\n ORAzI4JMPJ+GslWYHb4phowim57iaztXOoJwTdwJx4nLCgdNbOhdjsnvzqvHu7Ur\n TkXWStAmzOVyyghqpZXjFaH3pO3JLF+l+/+sKAIuvtd7u+Nxe5AW0wdeRlN8NwdC\n jNPElpzVmbUq4JUagEiuTDkHzsxHpFKVK7q4+63SM1N95R1NbdWhscdCb+ZAJzVc\n oyi3B43njTOQ5yOf+1CceWxG1bQVs5ZufpsMljq4Ui0/1lvh+wjChP4kqKOJ2qxq\n 4RgqsahDYVvTH9w7jXbyLeiNdd8XM2w9U/t7y0Ff/9yi0GE44Za4rF2LN9d11TPA\n mRGunUHBcnWEvgJBQl9nJEiU0Zsnvgc/ubhPgXRR4Xq37Z0j4r7g1SgEEzwxA57d\n emyPxgcYxn/eR44/KJ4EBs+lVDR3veyJm+kXQ99b21/+jh5Xos1AnX5iItreGCc=\n -----END CERTIFICATE-----\n )EOF";\n ';
  
  Blockly.Arduino.setups_['_01imi_espgoods_init'] = '  Serial.begin(9600);  \n  ArduinoSerial.begin(9600);\n  //Wifi初始\n  WiFi.disconnect();\n  WiFi.softAPdisconnect(true);\n  WiFi.mode(WIFI_STA);\n  WiFi.begin(_lwifi_ssid, _lwifi_pass);\n  while (WiFi.status() != WL_CONNECTED) { delay(500); }\n  delay(300);\n  \n  //MQTT初始\n  espClient.setCACert(root_ca);\n  client.setServer(mqtt_server, mqtt_port);\n  client.setCallback(callback);\n  if (!client.connected()) {\n    reconnect();\n  }\n';
  
  Blockly.Arduino.functions_['_01imi_espgoods_init'] = 'void reconnect() {\n  while (!client.connected()) {\n    Serial.print("Attempting MQTT connection… ");\n    String clientId = "ESP32Client";\n    if (client.connect(clientId.c_str(), mqtt_username, mqtt_password)) {\n      Serial.println("connected!");      \n    } else {\n      Serial.print("failed, rc = ");\n      Serial.print(client.state());\n      Serial.println(" try again in 5 seconds");\n      delay(5000);\n    }\n  }\n}\n//======google 試算表 函數 Start======\nString URLEncode(const char* msg)\n{\n  const char *hex = "0123456789abcdef";\n  String encodedMsg = "";\n  while (*msg!=\'\\0\'){\n      if( (\'a\' <= *msg && *msg <= \'z\')\n              || (\'A\' <= *msg && *msg <= \'Z\')\n              || (\'0\' <= *msg && *msg <= \'9\') ) {\n          encodedMsg += *msg;\n      } else {\n          encodedMsg += \'%\';\n          encodedMsg += hex[*msg >> 4];\n          encodedMsg += hex[*msg & 15];\n      }\n      msg++;\n  }\n  return encodedMsg;\n}\nvoid searchSheet(const String& fname, const String& sname){\n  static WiFiClientSecure sheetClient;\n  sheetClient.setInsecure();\n  const char* host="script.google.com";\n  String newUrl="";\n  sheetClient.connect(host, 443);\n  while (!sheetClient.connected());\n  const String url = String() +"https://"+host+"/macros/s/"+asId+"/exec?type=search&sheetId="+sheetId+"&sheetTag="+sheetTag+"&fname="+fname+"&sname="+sname;\n  sheetClient.print("GET " + url + " HTTP/1.1\\n"+String()+"Host: "+host+"\\nAccept: */*\\nConnection: close\\n\\n\\n");\n  while (!newUrl.startsWith("https:")){\n    newUrl = sheetClient.readStringUntil(\'\\n\');\n    if (newUrl.startsWith("Location: https://")) {\n      newUrl.replace("Location: ","");\n      break;\n    }\n  }\n  sheetClient.stop();\n  String jsonData ="";\n  sheetClient.connect(host, 443);\n  while (!sheetClient.connected());\n  sheetClient.print("GET " + newUrl + " HTTP/1.1\\n"+String()+"Host: "+host+"\\nAccept: */*\\nConnection: close\\n\\n\\n");\n  while(!jsonData.startsWith("{")){\n    jsonData = sheetClient.readStringUntil(\'\\n\');\n    if (jsonData.startsWith("{")) {\n      DeserializationError error = deserializeJson(docSheet, jsonData);\n      break;\n    }\n  }\n  sheetClient.stop();\n}\nvoid readGoogleSheet(String field,String name){\n  //讀取Google試算表\n  sheetTag=URLEncode(sTag);//工作表名稱\n  searchSheet(field,URLEncode(String(name).c_str()).c_str());\n  recipient[0] = String(docSheet["A"].as<String>());//姓名\n  recipient[1] = String(docSheet["B"].as<String>());//商品\n  recipient[2] = String(docSheet["C"].as<String>());//倉庫X\n  recipient[3] = String(docSheet["D"].as<String>());//倉庫Y\n  recipient[4] = String(docSheet["E"].as<String>());//收件人X\n  recipient[5] = String(docSheet["F"].as<String>());//收件人Y\n  \n  strRecipient="";\n  for(int i=0;i<6;i++){\n  strRecipient += recipient[i] + ",";\n  }\n}\n//======google 試算表 函數 End======\n//傳送訊息：ESP32→Arduino\nvoid UartSentToArduino(String msg){\n  ArduinoSerial.print(msg);\n}\nvoid pickGoods(String strX,String strY){\n  UartSentToArduino(strX+strY);//格式xy(例如13)\n}\n';

  var code = '';
  return code;
};

Blockly.Arduino['_02imi_espgoods_wifi'] = function(block) {
  var value_ssid = Blockly.Arduino.valueToCode(block, 'ssid', Blockly.Arduino.ORDER_ATOMIC);
  var value_wifipwd = Blockly.Arduino.valueToCode(block, 'wifipwd', Blockly.Arduino.ORDER_ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code = '//WiFi'+'\n'+ 'char _lwifi_ssid[] = '+value_ssid+';'+'\n'+ 'char _lwifi_pass[] = '+value_wifipwd+';'+'\n';

  return code;
};

Blockly.Arduino['_03imi_espgoods_mqtt'] = function(block) {
  var value_mqtt_user = Blockly.Arduino.valueToCode(block, 'mqtt_user', Blockly.Arduino.ORDER_ATOMIC);
  var value_mqtt_pwd = Blockly.Arduino.valueToCode(block, 'mqtt_pwd', Blockly.Arduino.ORDER_ATOMIC);
  var value_port = Blockly.Arduino.valueToCode(block, 'port', Blockly.Arduino.ORDER_ATOMIC);
  var value_mqtt_server = Blockly.Arduino.valueToCode(block, 'mqtt_server', Blockly.Arduino.ORDER_ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code = '//HiveMQ設定'+'\n'+ 'const char* mqtt_server =' +value_mqtt_server+';'+'\n'+ 'const char* mqtt_username =' +value_mqtt_user+';' +'\n'+ 'const char* mqtt_password =' +value_mqtt_pwd+';'+'\n'+ 'const int mqtt_port =' +value_port+';'+'\n';

  return code;
};

Blockly.Arduino['_04imi_espgoods_uart'] = function(block) {
  var value_rx = Blockly.Arduino.valueToCode(block, 'rx', Blockly.Arduino.ORDER_ATOMIC);
  var value_tx = Blockly.Arduino.valueToCode(block, 'tx', Blockly.Arduino.ORDER_ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code = '//UART通訊'+'\n'+ 'SoftwareSerial ArduinoSerial('+value_rx+','+value_tx+');'+'\n';

  return code;
};

Blockly.Arduino['_05imi_espgoods_sheet'] = function(block) {
  var value_sheetid = Blockly.Arduino.valueToCode(block, 'sheetid', Blockly.Arduino.ORDER_ATOMIC);
  var value_stag = Blockly.Arduino.valueToCode(block, 'stag', Blockly.Arduino.ORDER_ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code = '//google 試算表'+'\n'+ 'String sheetId='+value_sheetid+';//試算表id'+'\n'+ 'const char* sTag = '+value_stag+';//工作表名稱'+'\n';

  return code;
};

Blockly.Arduino['_06imi_espgoods_loop'] = function(block) {
  // TODO: Assemble javascript into code variable.
  var code = '//MQTT啟動'+'\n'+ '  client.loop();'+'\n'+ '  '+'\n'+ '  //接收訊息：Arduino→ESP32'+'\n'+ '  UartGetFromArduino();'+'\n';

  return code;
};

Blockly.Arduino['_07imi_espgoods_submqtt'] = function(block) {
  var dropdown_mqtt_topic = block.getFieldValue('mqtt_topic');
  // TODO: Assemble javascript into code variable.
  var code = '//MQTT Topic訂閱'+'\n'+ 'client.subscribe('+dropdown_mqtt_topic+');'+'\n';

  return code;
};

Blockly.Arduino['_08imi_espgoods_mqttcallback_func'] = function(block) {
  var statements_msg = Blockly.Arduino.statementToCode(block, 'msg');
  // TODO: Assemble javascript into code variable.
  Blockly.Arduino.functions_['_08imi_espgoods_mqttcallback_func'] = '//訂閱MQTT的主題回覆\n void callback(char* topic, byte* payload, unsigned int length) {\n   mqttGetMsg = "";\n   for (int i = 0; i < length; i++) {\n     mqttGetMsg += (char)payload[i];\n   }\n   mqttGetMsg.trim();  \n   Serial.println(String(topic));\n   Serial.println(mqttGetMsg);\n   \n   //接收Topic主題的消息Msg\n ' + statements_msg + '}\n ';

  var code = '';
  return code;
};

Blockly.Arduino['_09imi_espgoods_ismqtttopic'] = function(block) {
  var dropdown_mqtt_topic = block.getFieldValue('mqtt_topic');
  // TODO: Assemble javascript into code variable.
  var code = 'String(topic) ==' +dropdown_mqtt_topic;

  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.Arduino.ORDER_NONE];
};

Blockly.Arduino['_10imi_espgoods_readsheet'] = function(block) {
  var value_field = Blockly.Arduino.valueToCode(block, 'field', Blockly.Arduino.ORDER_ATOMIC);
  var value_name = Blockly.Arduino.valueToCode(block, 'name', Blockly.Arduino.ORDER_ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code = '//google表單查詢收貨人'+'\n'+ 'readGoogleSheet('+value_field+','+value_name+');'+'\n';

  return code;
};

Blockly.Arduino['_11imi_espgoods_sendarduino_pick'] = function(block) {
  // TODO: Assemble javascript into code variable.
  var code = '//傳送訊息至UNO:依商品xy座標 自動撿貨'+'\n'+ 'pickGoods(recipient[4],recipient[5]);'  +'\n';

  return code;
};

Blockly.Arduino['_12imi_espgoods_getarduino_func'] = function(block) {
  var statements_msg = Blockly.Arduino.statementToCode	(block, 'msg');
  // TODO: Assemble javascript into code variable.
  Blockly.Arduino.functions_['_12imi_espgoods_getarduino_func'] = '//接收訊息：Arduino→ESP32\n void UartGetFromArduino(){\n   while(ArduinoSerial.available()){\n     String val=ArduinoSerial.readString();\n     Serial.println(val);   \n ' + statements_msg + '  }\n }\n ';

  var code = '';
  return code;
};

Blockly.Arduino['_13imi_espgoods_isarduinomsg'] = function(block) {
  var dropdown_msg = block.getFieldValue('msg');
  // TODO: Assemble javascript into code variable.
  var code = 'val=='+dropdown_msg;

  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.Arduino.ORDER_NONE];
};

Blockly.Arduino['_14imi_espgoods_pubmqtt_goods'] = function(block) {
  // TODO: Assemble javascript into code variable.
  var code = '//發送MQTT：TOPIC_GOODS_LOAD'+'\n'+ 'const char* msg = strRecipient.c_str();'+'\n'+ 'mqttSendMsg = const_cast<char*>(msg);'+'\n';

  return code;
};