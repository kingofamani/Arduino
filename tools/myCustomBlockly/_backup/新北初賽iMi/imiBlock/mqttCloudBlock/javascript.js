Blockly.Arduino['_01imi_mqttcloud_init'] = function(block) {
  var statements_uart = Blockly.Arduino.statementToCode(block, 'uart');
  var statements_wifi = Blockly.Arduino.statementToCode(block, 'wifi');
  var statements_mqtt = Blockly.Arduino.statementToCode(block, 'mqtt');
  Blockly.Arduino.definitions_['_01imi_mqttcloud_init'] = '#include <WiFi.h>\n #include <PubSubClient.h>\n #include <WiFiClientSecure.h>\n #include <SoftwareSerial.h>\n //=====變數設定 Start=====\n ' + statements_uart+statements_wifi+statements_mqtt + '//=====變數設定 End=====\n const char* TOPIC_CAR_GPS = "imiRobot/car/gps";\n //車子的格子座標xy(例:35)\n int carX=0;\n int carY=0;\n char msgXY[3];\n WiFiClientSecure espClient;\n PubSubClient client(espClient);\n //HiveMQ Cloud\n static const char* root_ca PROGMEM = R"EOF(\n -----BEGIN CERTIFICATE-----\n MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw\n TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh\n cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMTUwNjA0MTEwNDM4\n WhcNMzUwNjA0MTEwNDM4WjBPMQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJu\n ZXQgU2VjdXJpdHkgUmVzZWFyY2ggR3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBY\n MTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAK3oJHP0FDfzm54rVygc\n h77ct984kIxuPOZXoHj3dcKi/vVqbvYATyjb3miGbESTtrFj/RQSa78f0uoxmyF+\n 0TM8ukj13Xnfs7j/EvEhmkvBioZxaUpmZmyPfjxwv60pIgbz5MDmgK7iS4+3mX6U\n A5/TR5d8mUgjU+g4rk8Kb4Mu0UlXjIB0ttov0DiNewNwIRt18jA8+o+u3dpjq+sW\n T8KOEUt+zwvo/7V3LvSye0rgTBIlDHCNAymg4VMk7BPZ7hm/ELNKjD+Jo2FR3qyH\n B5T0Y3HsLuJvW5iB4YlcNHlsdu87kGJ55tukmi8mxdAQ4Q7e2RCOFvu396j3x+UC\n B5iPNgiV5+I3lg02dZ77DnKxHZu8A/lJBdiB3QW0KtZB6awBdpUKD9jf1b0SHzUv\n KBds0pjBqAlkd25HN7rOrFleaJ1/ctaJxQZBKT5ZPt0m9STJEadao0xAH0ahmbWn\n OlFuhjuefXKnEgV4We0+UXgVCwOPjdAvBbI+e0ocS3MFEvzG6uBQE3xDk3SzynTn\n jh8BCNAw1FtxNrQHusEwMFxIt4I7mKZ9YIqioymCzLq9gwQbooMDQaHWBfEbwrbw\n qHyGO0aoSCqI3Haadr8faqU9GY/rOPNk3sgrDQoo//fb4hVC1CLQJ13hef4Y53CI\n rU7m2Ys6xt0nUW7/vGT1M0NPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNV\n HRMBAf8EBTADAQH/MB0GA1UdDgQWBBR5tFnme7bl5AFzgAiIyBpY9umbbjANBgkq\n hkiG9w0BAQsFAAOCAgEAVR9YqbyyqFDQDLHYGmkgJykIrGF1XIpu+ILlaS/V9lZL\n ubhzEFnTIZd+50xx+7LSYK05qAvqFyFWhfFQDlnrzuBZ6brJFe+GnY+EgPbk6ZGQ\n 3BebYhtF8GaV0nxvwuo77x/Py9auJ/GpsMiu/X1+mvoiBOv/2X/qkSsisRcOj/KK\n NFtY2PwByVS5uCbMiogziUwthDyC3+6WVwW6LLv3xLfHTjuCvjHIInNzktHCgKQ5\n ORAzI4JMPJ+GslWYHb4phowim57iaztXOoJwTdwJx4nLCgdNbOhdjsnvzqvHu7Ur\n TkXWStAmzOVyyghqpZXjFaH3pO3JLF+l+/+sKAIuvtd7u+Nxe5AW0wdeRlN8NwdC\n jNPElpzVmbUq4JUagEiuTDkHzsxHpFKVK7q4+63SM1N95R1NbdWhscdCb+ZAJzVc\n oyi3B43njTOQ5yOf+1CceWxG1bQVs5ZufpsMljq4Ui0/1lvh+wjChP4kqKOJ2qxq\n 4RgqsahDYVvTH9w7jXbyLeiNdd8XM2w9U/t7y0Ff/9yi0GE44Za4rF2LN9d11TPA\n mRGunUHBcnWEvgJBQl9nJEiU0Zsnvgc/ubhPgXRR4Xq37Z0j4r7g1SgEEzwxA57d\n emyPxgcYxn/eR44/KJ4EBs+lVDR3veyJm+kXQ99b21/+jh5Xos1AnX5iItreGCc=\n -----END CERTIFICATE-----\n )EOF";\n ';
  
  Blockly.Arduino.functions_['_01imi_mqttcloud_init'] = 'void reconnect() {\n  while (!client.connected()) {\n    Serial.print("Attempting MQTT connection… ");\n    String clientId = "ESP32Client";\n    if (client.connect(clientId.c_str(), mqtt_username, mqtt_password)) {\n      Serial.println("connected!");\n    } else {\n      Serial.print("failed, rc = ");\n      Serial.print(client.state());\n      Serial.println(" try again in 5 seconds");\n      delay(5000);\n    }\n  }\n}\nvoid setup_wifi() {\n  delay(10);\n  Serial.println();\n  Serial.print("Connecting to ");\n  Serial.println(ssid);\n  WiFi.mode(WIFI_STA);\n  WiFi.begin(ssid, password);\n  while (WiFi.status() != WL_CONNECTED) {\n    delay(500);\n    Serial.print(".");\n  }\n  Serial.println("");\n  Serial.println("WiFi connected");\n  Serial.println("IP address: ");\n  Serial.println(WiFi.localIP());\n}\n';
  
  Blockly.Arduino.setups_['_01imi_mqttcloud_init'] = 'delay(500);\n  Serial.begin(9600);\n  delay(500);\n  Esp32GpsSerial.begin(9600);\n  delay(500);\n  setup_wifi();\n  espClient.setCACert(root_ca);\n  client.setServer(mqtt_server, mqtt_port);\n  client.setCallback(callback);\n  if (!client.connected()) {\n    reconnect();\n  }\n';

  var code = '';
  return code;
};

Blockly.Arduino['_02imi_mqttcloud_uart'] = function(block) {
  var value_rx = Blockly.Arduino.valueToCode(block, 'rx', Blockly.Arduino.ORDER_ATOMIC);
  var value_tx = Blockly.Arduino.valueToCode(block, 'tx', Blockly.Arduino.ORDER_ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code = '//UART通訊'+'\n'+ 'SoftwareSerial Esp32GpsSerial('+value_rx+','+value_tx+');'+'\n';

  return code;
};

Blockly.Arduino['_03imi_mqttcloud_wifi'] = function(block) {
  var value_ssid = Blockly.Arduino.valueToCode(block, 'ssid', Blockly.Arduino.ORDER_ATOMIC);
  var value_wifipwd = Blockly.Arduino.valueToCode(block, 'wifipwd', Blockly.Arduino.ORDER_ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code = '//WiFi設定'+'\n'+ 'const char* ssid = '+value_ssid+';'+'\n'+ 'const char* password = '+value_wifipwd+';'+'\n';

  return code;
};

Blockly.Arduino['_04imi_mqttcloud_mqtt'] = function(block) {
  var value_mqtt_user = Blockly.Arduino.valueToCode(block, 'mqtt_user', Blockly.Arduino.ORDER_ATOMIC);
  var value_mqtt_pwd = Blockly.Arduino.valueToCode(block, 'mqtt_pwd', Blockly.Arduino.ORDER_ATOMIC);
  var value_port = Blockly.Arduino.valueToCode(block, 'port', Blockly.Arduino.ORDER_ATOMIC);
  var value_mqtt_server = Blockly.Arduino.valueToCode(block, 'mqtt_server', Blockly.Arduino.ORDER_ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code = '//HiveMQ設定'+'\n'+ 'const char* mqtt_server =' +value_mqtt_server+';'+'\n'+ 'const char* mqtt_username =' +value_mqtt_user+';'                                        +'\n'+ 'const char* mqtt_password =' +value_mqtt_pwd+';'                                    +'\n'+ 'const int mqtt_port =' +value_port+';'+'\n';

  return code;
};

Blockly.Arduino['_05imi_mqttcloud_loop'] = function(block) {
  // TODO: Assemble javascript into code variable.
  var code = 'client.loop();'+'\n';

  return code;
};

Blockly.Arduino['_06imi_mqttcloud_submqtt'] = function(block) {
  var dropdown_name = block.getFieldValue('NAME');
  // TODO: Assemble javascript into code variable.
  Blockly.Arduino.setups_['_06imi_mqttcloud_submqtt'] = '  //訂閱\n  client.subscribe(TOPIC_CAR_GPS);\n  Serial.println(String(TOPIC_CAR_GPS)+"已訂閱成功！請開啟https://console.hivemq.cloud/，並用Publish Message來測試！");\n';

  var code = '';
  return code;
};

Blockly.Arduino['_07imi_mqttcloud_mqttcallback_func'] = function(block) {
  var statements_msg = Blockly.Arduino.statementToCode(block, 'msg');
  // TODO: Assemble javascript into code variable.
  Blockly.Arduino.functions_['_07imi_mqttcloud_mqttcallback_func'] = '//MQTT訂閱的主題回覆\n void callback(char* topic, byte* payload, unsigned int length) {\n   //傳送至ESP32 GPS板(格式:xy)\n   msgXY[0] = (char)payload[0];\n   msgXY[1] = (char)payload[1]; \n   msgXY[2] = \'\\0\';\n   Serial.println(msgXY);\n ' + statements_msg + '}\n ';

  var code = '';
  return code;
};

Blockly.Arduino['_08imi_mqttcloud_sendarduino_gps'] = function(block) {
  // TODO: Assemble javascript into code variable.
  var code = 'Esp32GpsSerial.write(msgXY);'+'\n';

  return code;
};