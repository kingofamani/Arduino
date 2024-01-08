Blockly.Arduino['01imi_esp32car_init'] = function(block) {
  var statements_uart = Blockly.Arduino.statementToCode(block, 'uart');
  var statements_wifi = Blockly.Arduino.statementToCode(block, 'wifi');
  var statements_line = Blockly.Arduino.statementToCode(block, 'line');
  var statements_mqtt = Blockly.Arduino.statementToCode(block, 'mqtt');
  // TODO: Assemble javascript into code variable.
  Blockly.Arduino.definitions_['01imi_esp32car_init'] = '#include <SoftwareSerial.h>\n#include <WiFi.h>\n#include <PubSubClient.h>\n#include <WiFiClientSecure.h>\n//與Mega通訊\nconst char* MAP_SET = "mapSet";\nconst char* GOODS_LOAD = "goodsLoad";\nconst char* LINE_NOTIFY = "lineNotify";\nconst char* CAR_GPS = "carGps";\n//===設定程式碼input Start===\n//===設定程式碼input End===\n//Topic主題\nconst char* TOPIC_MAP_SET = "imiRobot/map/set";\nconst char* TOPIC_CAR_STANDBY = "imiRobot/car/standby";\nconst char* TOPIC_CAR_GPS = "imiRobot/car/gps";\nconst char* TOPIC_GOODS_LOAD = "imiRobot/goods/load";\nconst char* TOPIC_CAR_LOWPOWER = "imiRobot/car/lowPower";\n//發佈者 傳送的消息內容\nchar* mqttSendMsg = "";\n//訂閱者 接收的消息內容\nString mqttGetMsg = "";\nWiFiClientSecure espClient;\nPubSubClient client(espClient);\n// HiveMQ Cloud\nstatic const char* root_ca PROGMEM = R"EOF(\n-----BEGIN CERTIFICATE-----\nMIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw\nTzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh\ncmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMTUwNjA0MTEwNDM4\nWhcNMzUwNjA0MTEwNDM4WjBPMQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJu\nZXQgU2VjdXJpdHkgUmVzZWFyY2ggR3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBY\nMTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAK3oJHP0FDfzm54rVygc\nh77ct984kIxuPOZXoHj3dcKi/vVqbvYATyjb3miGbESTtrFj/RQSa78f0uoxmyF+\n0TM8ukj13Xnfs7j/EvEhmkvBioZxaUpmZmyPfjxwv60pIgbz5MDmgK7iS4+3mX6U\nA5/TR5d8mUgjU+g4rk8Kb4Mu0UlXjIB0ttov0DiNewNwIRt18jA8+o+u3dpjq+sW\nT8KOEUt+zwvo/7V3LvSye0rgTBIlDHCNAymg4VMk7BPZ7hm/ELNKjD+Jo2FR3qyH\nB5T0Y3HsLuJvW5iB4YlcNHlsdu87kGJ55tukmi8mxdAQ4Q7e2RCOFvu396j3x+UC\nB5iPNgiV5+I3lg02dZ77DnKxHZu8A/lJBdiB3QW0KtZB6awBdpUKD9jf1b0SHzUv\nKBds0pjBqAlkd25HN7rOrFleaJ1/ctaJxQZBKT5ZPt0m9STJEadao0xAH0ahmbWn\nOlFuhjuefXKnEgV4We0+UXgVCwOPjdAvBbI+e0ocS3MFEvzG6uBQE3xDk3SzynTn\njh8BCNAw1FtxNrQHusEwMFxIt4I7mKZ9YIqioymCzLq9gwQbooMDQaHWBfEbwrbw\nqHyGO0aoSCqI3Haadr8faqU9GY/rOPNk3sgrDQoo//fb4hVC1CLQJ13hef4Y53CI\nrU7m2Ys6xt0nUW7/vGT1M0NPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNV\nHRMBAf8EBTADAQH/MB0GA1UdDgQWBBR5tFnme7bl5AFzgAiIyBpY9umbbjANBgkq\nhkiG9w0BAQsFAAOCAgEAVR9YqbyyqFDQDLHYGmkgJykIrGF1XIpu+ILlaS/V9lZL\nubhzEFnTIZd+50xx+7LSYK05qAvqFyFWhfFQDlnrzuBZ6brJFe+GnY+EgPbk6ZGQ\n3BebYhtF8GaV0nxvwuo77x/Py9auJ/GpsMiu/X1+mvoiBOv/2X/qkSsisRcOj/KK\nNFtY2PwByVS5uCbMiogziUwthDyC3+6WVwW6LLv3xLfHTjuCvjHIInNzktHCgKQ5\nORAzI4JMPJ+GslWYHb4phowim57iaztXOoJwTdwJx4nLCgdNbOhdjsnvzqvHu7Ur\nTkXWStAmzOVyyghqpZXjFaH3pO3JLF+l+/+sKAIuvtd7u+Nxe5AW0wdeRlN8NwdC\njNPElpzVmbUq4JUagEiuTDkHzsxHpFKVK7q4+63SM1N95R1NbdWhscdCb+ZAJzVc\noyi3B43njTOQ5yOf+1CceWxG1bQVs5ZufpsMljq4Ui0/1lvh+wjChP4kqKOJ2qxq\n4RgqsahDYVvTH9w7jXbyLeiNdd8XM2w9U/t7y0Ff/9yi0GE44Za4rF2LN9d11TPA\nmRGunUHBcnWEvgJBQl9nJEiU0Zsnvgc/ubhPgXRR4Xq37Z0j4r7g1SgEEzwxA57d\nemyPxgcYxn/eR44/KJ4EBs+lVDR3veyJm+kXQ99b21/+jh5Xos1AnX5iItreGCc=\n-----END CERTIFICATE-----\n)EOF";\n'+statements_uart +statements_wifi +statements_line +statements_mqtt ;

	
	Blockly.Arduino.functions_['01imi_esp32car_init'] = 'void reconnect() {\n  while (!client.connected()) {\n    Serial.print("Attempting MQTT connection… ");\n    String clientId = "ESP32Client";\n    if (client.connect(clientId.c_str(), mqtt_username, mqtt_password)) {\n      Serial.println("connected!");\n    } else {\n      Serial.print("failed, rc = ");\n      Serial.print(client.state());\n      Serial.println(" try again in 5 seconds");\n      delay(5000);\n    }\n  }\n}\nvoid sendLineMsg(String myMsg) {\n  static WiFiClientSecure line_client;\n  line_client.setInsecure();\n  myMsg.replace("%", "%25");\n  myMsg.replace("&", "%26");\n  myMsg.replace("§", "&");\n  myMsg.replace("\\\\n", "\\n");\n  if (line_client.connect("notify-api.line.me", 443)) {\n    line_client.println("POST /api/notify HTTP/1.1");\n    line_client.println("Connection: close");\n    line_client.println("Host: notify-api.line.me");\n    line_client.println("Authorization: Bearer " + lineToken);\n    line_client.println("Content-Type: application/x-www-form-urlencoded");\n    line_client.println("Content-Length: " + String(myMsg.length()));\n    line_client.println();\n    line_client.println(myMsg);\n    line_client.println();\n    line_client.stop();\n  } else {\n    Serial.println("Line Notify failed");\n  }\n}\nvoid setup_wifi() {\n  delay(10);\n  Serial.println();\n  Serial.print("Connecting to ");\n  Serial.println(ssid);\n  WiFi.mode(WIFI_STA);\n  WiFi.begin(ssid, password);\n  while (WiFi.status() != WL_CONNECTED) {\n    delay(500);\n    Serial.print(".");\n  }\n  Serial.println("");\n  Serial.println("WiFi connected");\n  Serial.println("IP address: ");\n  Serial.println(WiFi.localIP());\n}\n//傳送訊息：ESP32→Mega\nvoid UartSentToMega(String msg) {\n  MegaSerial.print(msg);\n}\n';

	Blockly.Arduino.setups_['01imi_esp32car_init'] = '  delay(500);\n  Serial.begin(9600);\n  delay(500);\n  MegaSerial.begin(9600);\n  delay(500);\n  setup_wifi();\n  //MQTT初始\n  espClient.setCACert(root_ca);\n  client.setServer(mqtt_server, mqtt_port);\n  client.setCallback(callback);\n  if (!client.connected()) {\n    reconnect();\n  }\n';

	
  var code = '';
  return code;
};

Blockly.Arduino['02imi_esp32car_init_uart'] = function(block) {
  var value_rx = Blockly.Arduino.valueToCode(block, 'rx', Blockly.Arduino.ORDER_ATOMIC);
  var value_tx = Blockly.Arduino.valueToCode(block, 'tx', Blockly.Arduino.ORDER_ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code ='//UART通訊'+'\n '+'SoftwareSerial MegaSerial('+value_rx+',' +value_tx+');'+'\n ';
  return code;
};

Blockly.Arduino['03imi_esp32car_init_wifi'] = function(block) {
  var value_ssid = Blockly.Arduino.valueToCode(block, 'ssid', Blockly.Arduino.ORDER_ATOMIC);
  var value_wifi_pwd = Blockly.Arduino.valueToCode(block, 'wifi_pwd', Blockly.Arduino.ORDER_ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code ='//WiFi設定'+'\n '+'const char* ssid =' +value_ssid+';'+'\n '+'const char* password =' +value_wifi_pwd+';'+'\n ';
  return code;
};

Blockly.Arduino['04imi_esp32car_init_line'] = function(block) {
  var value_line_token = Blockly.Arduino.valueToCode(block, 'line_token', Blockly.Arduino.ORDER_ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code ='//LINE權杖'+'\n '+'String lineToken =' +value_line_token+';'+'\n ';
  return code;
};

Blockly.Arduino['05imi_esp32car_init_mqtt'] = function(block) {
  var value_mqtt_user = Blockly.Arduino.valueToCode(block, 'mqtt_user', Blockly.Arduino.ORDER_ATOMIC);
  var value_mqtt_pwd = Blockly.Arduino.valueToCode(block, 'mqtt_pwd', Blockly.Arduino.ORDER_ATOMIC);
  var value_mqtt_port = Blockly.Arduino.valueToCode(block, 'mqtt_port', Blockly.Arduino.ORDER_ATOMIC);
  var value_mqtt_server = Blockly.Arduino.valueToCode(block, 'mqtt_server', Blockly.Arduino.ORDER_ATOMIC);
  // TODO: Assemble javascript into code variable.
   var code ='//---- HiveMQ設定 Start -----'+'\n '+'const char* mqtt_server = ' +value_mqtt_server +';'+'\n '+'const char* mqtt_username =' +value_mqtt_user+';'+'\n '+'const char* mqtt_password =' +value_mqtt_pwd+';'+'\n '+'const int mqtt_port =' +value_mqtt_port+';'+'\n ';
  return code;
};

Blockly.Arduino['06imi_esp32car_loop'] = function(block) {
  // TODO: Assemble javascript into code variable.
  var code ='//MQTT啟動\n  client.loop();\n  //接收訊息：Mega→ESP32\n    UartGetFromMega();\n';

  return code;
};

Blockly.Arduino['07imi_esp32car_getarduino_func'] = function(block) {
  var statements_msg = Blockly.Arduino.statementToCode(block, 'msg');
  Blockly.Arduino.functions_['imi_esp32car_getArduino_func'] = '//接收訊息：Mega→ESP32\n void UartGetFromMega() {  \n   while (MegaSerial.available()) {\n     String str = MegaSerial.readString();\n     Serial.println(str);\n ' + statements_msg + '}//while\n }\n ';


  var code = '';
  return code;
};




Blockly.Arduino['08imi_esp32car_submqtt'] = function(block) {
  var dropdown_mqtt_topic = block.getFieldValue('mqtt_topic');
  // TODO: Assemble javascript into code variable.
  Blockly.Arduino.setups_['imi_esp32car_submqtt'+dropdown_mqtt_topic] = 'client.subscribe('+dropdown_mqtt_topic+');\n';

  var code = '';
  return code;
};

Blockly.Arduino['09imi_esp32car_mqttcallback_func'] = function(block) {
  var statements_msg = Blockly.Arduino.statementToCode(block, 'msg');
  Blockly.Arduino.functions_['imi_esp32car_mqttcallback_func'] = '//訂閱的主題回覆\n void callback(char* topic, byte* payload, unsigned int length) {\n   mqttGetMsg = "";\n   for (int i = 0; i < length; i++) {\n     mqttGetMsg += (char)payload[i];\n   }\n   mqttGetMsg.trim();\n   Serial.println(String(topic));\n   Serial.println(mqttGetMsg);\n ' + statements_msg + '}\n ';

  var code = '';
  return code;
};

Blockly.Arduino['10imi_esp32car_ismqtttopic'] = function(block) {
  var dropdown_mqtt_topic = block.getFieldValue('mqtt_topic');
  var code ='String(topic) ==' +dropdown_mqtt_topic;

  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.Arduino.ORDER_NONE];
};


Blockly.Arduino['11imi_esp32car_sendarduino_mapset'] = function(block) {
  var code ='//儲存地圖陣列(格式:MAP_SET,4x6地圖陣列)\n     UartSentToMega(String(MAP_SET) + "," + mqttGetMsg);\n     delay(1000);\n ';

  return code;
};

Blockly.Arduino['12imi_esp32car_pubmqtt_carstandby'] = function(block) {
  var code ='//發送MQTT：TOPIC_CAR_STANDBY\n     mqttSendMsg = "1";\n     client.publish(TOPIC_CAR_STANDBY, mqttSendMsg);\n ';

  return code;
};

Blockly.Arduino['13imi_esp32car_sendarduino_goodsload'] = function(block) {
  var code ='//開始送貨(格式:GOODS_LOAD,姓名,商品,倉庫X,倉庫Y,收件人X,收件人Y)\n     UartSentToMega(String(GOODS_LOAD) + "," + mqttGetMsg);\n ';

  return code;
};

Blockly.Arduino['14imi_esp32car_isarduinomsg'] = function(block) {
  var dropdown_uart_topic = block.getFieldValue('uart_topic');
  // TODO: Assemble javascript into code variable.
  var code ='str.indexOf('+dropdown_uart_topic+') != -1';

  return [code, Blockly.Arduino.ORDER_NONE];
};

Blockly.Arduino['15imi_esp32car_getarduino_recipient'] = function(block) {
  var code ='//收貨人資料字串轉陣列\n       String tmpArray[3];\n       char* token = strtok((char*)str.c_str(), ",");\n       int tokenLen = 0;\n       while (token != NULL && tokenLen < 3) {\n         tmpArray[tokenLen] = token;\n         token = strtok(NULL, ",");\n         tokenLen++;\n       }\n ';

  return code;
};

Blockly.Arduino['16imi_esp32car_line_recipient'] = function(block) {
  // TODO: Assemble javascript into code variable.
  var code ='//發送LINE\n       sendLineMsg(tmpArray[1] + "您好：您的商品：「" + tmpArray[2] + "」已送達，請至門口進行人臉識別簽收。");\n ';

  return code;
};

Blockly.Arduino['17imi_esp32car_getarduino_gps'] = function(block) {
  // TODO: Assemble javascript into code variable.
  var code ='//座標字串轉陣列\n       String arryGps[3];\n       char* token = strtok((char*)str.c_str(), ",");\n       int tokenLen = 0;\n       while (token != NULL && tokenLen < 3) {\n         arryGps[tokenLen] = token;\n         token = strtok(NULL, ",");\n         tokenLen++;\n       }\n ';

  return code;
};

Blockly.Arduino['18imi_esp32car_pubmqtt_cargps'] = function(block) {
  // TODO: Assemble javascript into code variable.
  var code ='//發送MQTT：TOPIC_CAR_GPS(格式:xy)\n       //    使用String結合x和y的內容\n       String xy = arryGps[1] + arryGps[2];\n       //    將String轉換為const char*\n       const char* msg = (xy).c_str();\n       //    const char*轉char*\n       mqttSendMsg = const_cast<char*>(msg);\n       client.publish(TOPIC_CAR_GPS, mqttSendMsg);\n ';

  return code;
};