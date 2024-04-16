Blockly.Arduino['_01imi_espmap_init'] = function(block) {
  var statements_wifi = Blockly.Arduino.statementToCode(block, 'wifi');
  var statements_mqtt = Blockly.Arduino.statementToCode(block, 'mqtt');
  var statements_button = Blockly.Arduino.statementToCode(block, 'button');
  var statements_map = Blockly.Arduino.statementToCode(block, 'map');
  // TODO: Assemble javascript into code variable.
  Blockly.Arduino.definitions_['_01imi_espmap_init'] = '#include <WiFi.h>\n #include <PubSubClient.h>\n #include <WiFiClientSecure.h>\n //===設定變數 Start===\n ' + statements_wifi+statements_mqtt+statements_button+statements_map  + '//===設定變數 End===\n String strGrid="";\n //Topic主題\n const char* TOPIC_MAP_SET = "imiRobot/map/set";\n const char* TOPIC_CAR_STANDBY = "imiRobot/car/standby";\n const char* TOPIC_CAR_GPS = "imiRobot/car/gps";\n const char* TOPIC_GOODS_LOAD = "imiRobot/goods/load";\n const char* TOPIC_CAR_LOWPOWER = "imiRobot/car/lowPower";\n //發佈者 傳送的消息內容\n char* mqttSendMsg = "";\n //訂閱者 接收的消息內容\n String mqttGetMsg = "";\n WiFiClientSecure espClient;\n PubSubClient client(espClient);\n // HiveMQ Cloud\n static const char* root_ca PROGMEM = R"EOF(\n -----BEGIN CERTIFICATE-----\n MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw\n TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh\n cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMTUwNjA0MTEwNDM4\n WhcNMzUwNjA0MTEwNDM4WjBPMQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJu\n ZXQgU2VjdXJpdHkgUmVzZWFyY2ggR3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBY\n MTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAK3oJHP0FDfzm54rVygc\n h77ct984kIxuPOZXoHj3dcKi/vVqbvYATyjb3miGbESTtrFj/RQSa78f0uoxmyF+\n 0TM8ukj13Xnfs7j/EvEhmkvBioZxaUpmZmyPfjxwv60pIgbz5MDmgK7iS4+3mX6U\n A5/TR5d8mUgjU+g4rk8Kb4Mu0UlXjIB0ttov0DiNewNwIRt18jA8+o+u3dpjq+sW\n T8KOEUt+zwvo/7V3LvSye0rgTBIlDHCNAymg4VMk7BPZ7hm/ELNKjD+Jo2FR3qyH\n B5T0Y3HsLuJvW5iB4YlcNHlsdu87kGJ55tukmi8mxdAQ4Q7e2RCOFvu396j3x+UC\n B5iPNgiV5+I3lg02dZ77DnKxHZu8A/lJBdiB3QW0KtZB6awBdpUKD9jf1b0SHzUv\n KBds0pjBqAlkd25HN7rOrFleaJ1/ctaJxQZBKT5ZPt0m9STJEadao0xAH0ahmbWn\n OlFuhjuefXKnEgV4We0+UXgVCwOPjdAvBbI+e0ocS3MFEvzG6uBQE3xDk3SzynTn\n jh8BCNAw1FtxNrQHusEwMFxIt4I7mKZ9YIqioymCzLq9gwQbooMDQaHWBfEbwrbw\n qHyGO0aoSCqI3Haadr8faqU9GY/rOPNk3sgrDQoo//fb4hVC1CLQJ13hef4Y53CI\n rU7m2Ys6xt0nUW7/vGT1M0NPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNV\n HRMBAf8EBTADAQH/MB0GA1UdDgQWBBR5tFnme7bl5AFzgAiIyBpY9umbbjANBgkq\n hkiG9w0BAQsFAAOCAgEAVR9YqbyyqFDQDLHYGmkgJykIrGF1XIpu+ILlaS/V9lZL\n ubhzEFnTIZd+50xx+7LSYK05qAvqFyFWhfFQDlnrzuBZ6brJFe+GnY+EgPbk6ZGQ\n 3BebYhtF8GaV0nxvwuo77x/Py9auJ/GpsMiu/X1+mvoiBOv/2X/qkSsisRcOj/KK\n NFtY2PwByVS5uCbMiogziUwthDyC3+6WVwW6LLv3xLfHTjuCvjHIInNzktHCgKQ5\n ORAzI4JMPJ+GslWYHb4phowim57iaztXOoJwTdwJx4nLCgdNbOhdjsnvzqvHu7Ur\n TkXWStAmzOVyyghqpZXjFaH3pO3JLF+l+/+sKAIuvtd7u+Nxe5AW0wdeRlN8NwdC\n jNPElpzVmbUq4JUagEiuTDkHzsxHpFKVK7q4+63SM1N95R1NbdWhscdCb+ZAJzVc\n oyi3B43njTOQ5yOf+1CceWxG1bQVs5ZufpsMljq4Ui0/1lvh+wjChP4kqKOJ2qxq\n 4RgqsahDYVvTH9w7jXbyLeiNdd8XM2w9U/t7y0Ff/9yi0GE44Za4rF2LN9d11TPA\n mRGunUHBcnWEvgJBQl9nJEiU0Zsnvgc/ubhPgXRR4Xq37Z0j4r7g1SgEEzwxA57d\n emyPxgcYxn/eR44/KJ4EBs+lVDR3veyJm+kXQ99b21/+jh5Xos1AnX5iItreGCc=\n -----END CERTIFICATE-----\n )EOF";\n ';
  
  Blockly.Arduino.setups_['_01imi_espmap_init'] = '  delay(500);\n  Serial.begin(9600);\n  delay(500);\n  setup_wifi();\n  //按鈕I/O\n  pinMode(BUTTON_PIN, INPUT);\n  //MQTT初始\n  espClient.setCACert(root_ca);\n  client.setServer(mqtt_server, mqtt_port);\n  client.setCallback(callback);\n  if (!client.connected()) {\n    reconnect();\n  }\n  //取得佈置地圖陣列(Seeds)\n  // 地圖表示，0表示障礙物，1表示可通行  \n  strGrid = "";\n  for (int i = 0; i < 4; i++) {\n    for (int j = 0; j < 6; j++) {\n      strGrid += grid[i][j] +",";\n    }\n  }\n';
  
  Blockly.Arduino.functions_['_01imi_espmap_init'] = 'void setup_wifi() {\n  delay(10);\n  Serial.println();\n  Serial.print("Connecting to ");\n  Serial.println(ssid);\n  WiFi.mode(WIFI_STA);\n  WiFi.begin(ssid, password);\n  while (WiFi.status() != WL_CONNECTED) {\n    delay(500);\n    Serial.print(".");\n  }\n  Serial.println("");\n  Serial.println("WiFi connected");\n  Serial.println("IP address: ");\n  Serial.println(WiFi.localIP());\n}\n//MQTT訂閱的主題回覆\nvoid callback(char* topic, byte* payload, unsigned int length) {\n}\nvoid reconnect() {\n  while (!client.connected()) {\n    Serial.print("Attempting MQTT connection… ");\n    String clientId = "ESP32Client";\n    if (client.connect(clientId.c_str(), mqtt_username, mqtt_password)) {\n      Serial.println("connected!");      \n    } else {\n      Serial.print("failed, rc = ");\n      Serial.print(client.state());\n      Serial.println(" try again in 5 seconds");\n      delay(5000);\n    }\n  }\n}\n';

  var code = '';
  return code;
};

Blockly.Arduino['_02imi_espmap_wifi'] = function(block) {
  var value_ssid = Blockly.Arduino.valueToCode(block, 'ssid', Blockly.Arduino.ORDER_ATOMIC);
  var value_wifipwd = Blockly.Arduino.valueToCode(block, 'wifipwd', Blockly.Arduino.ORDER_ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code = '//WiFi設定'+'\n'+ 'const char* ssid = '+value_ssid+';'+'\n'+ 'const char* password = '+value_wifipwd+';'+'\n';

  return code;
};

Blockly.Arduino['_03imi_espmap_mqtt'] = function(block) {
  var value_mqtt_user = Blockly.Arduino.valueToCode(block, 'mqtt_user', Blockly.Arduino.ORDER_ATOMIC);
  var value_mqtt_pwd = Blockly.Arduino.valueToCode(block, 'mqtt_pwd', Blockly.Arduino.ORDER_ATOMIC);
  var value_mqtt_port = Blockly.Arduino.valueToCode(block, 'mqtt_port', Blockly.Arduino.ORDER_ATOMIC);
  var value_mqtt_server = Blockly.Arduino.valueToCode(block, 'mqtt_server', Blockly.Arduino.ORDER_ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code = '//HiveMQ設定'+'\n'+ 'const char* mqtt_server = '+value_mqtt_server+';'+'\n'+ 'const char* mqtt_username = '+value_mqtt_user+';'+'\n'+ 'const char* mqtt_password = '+value_mqtt_pwd+';'+'\n'+ 'const int mqtt_port = '+value_mqtt_port+';'+'\n';

  return code;
};

Blockly.Arduino['_04imi_espmap_button'] = function(block) {
  var value_btnpin = Blockly.Arduino.valueToCode(block, 'btnpin', Blockly.Arduino.ORDER_ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code = '//佈置'+'\n'+ '#define BUTTON_PIN '+value_btnpin+'\n';

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
  var code = '    { '+value_00+',' +value_01+',' +value_02+',' +value_03+',' +value_04+',' +value_05+ '},'+'\n';
  return code;
};

Blockly.Arduino['_06imi_espmap_loop'] = function(block) {
  // TODO: Assemble javascript into code variable.
  var code ='//MQTT啟動\n'+'  client.loop();\n';

  return code;
};

Blockly.Arduino['_07imi_espmap_isbutton'] = function(block) {
  // TODO: Assemble javascript into code variable.
  var code ='digitalRead(BUTTON_PIN)==1';

  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.Arduino.ORDER_NONE];
};

Blockly.Arduino['_08imi_espmap_pubmqtt_mapset'] = function(block) {
  // TODO: Assemble javascript into code variable.
  var code ='//發送MQTT：TOPIC_MAP_SET\n'+'    const char* msg = strGrid.c_str();\n'+'    mqttSendMsg = const_cast<char*>(msg);\n'+'    client.publish(TOPIC_MAP_SET, mqttSendMsg);\n';

  return code;
};

Blockly.Arduino['_05imi_espmap_maps'] = function(block) {
  var statements_msg = Blockly.Arduino.statementToCode	(block, 'msg');
  // TODO: Assemble javascript into code variable.
  var code ='int grid[4][6] = {\n ' + statements_msg + '};\n ';
  return code;
};