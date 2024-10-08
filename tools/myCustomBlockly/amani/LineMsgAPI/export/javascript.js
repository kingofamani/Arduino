Blockly.Arduino['_01amani_linepushapi_init'] = function(block) {
  var value_userid = Blockly.Arduino.valueToCode(block, 'userid', Blockly.Arduino.ORDER_ATOMIC);
  var value_token = Blockly.Arduino.valueToCode(block, 'token', Blockly.Arduino.ORDER_ATOMIC);
  
  Blockly.Arduino.definitions_['_01amani_linepushapi_init'] = '#include <WiFiClientSecure.h>\n// Line Push API \nconst char* line_host = "api.line.me";\nconst char* line_url = "/v2/bot/message/push";\nconst char* line_token = '+value_token+';\nconst char* line_userid = '+value_userid+';\nvoid pushLineMessage(String line_msg) {\n  WiFiClientSecure line_client;\n  line_client.setInsecure();\n  if (!line_client.connect(line_host, 443)) {\n    Serial.println("line連接失敗");\n    return;\n  }\n  String payload = "{\\"to\\": \\"" + String(line_userid) + "\\",\\"messages\\": [{\\"type\\": \\"text\\", \\"text\\": \\"" + line_msg + "\\"}]}";\n  String request = String("POST ") + line_url + " HTTP/1.1\\r\\n" +\n                   "Host: " + line_host + "\\r\\n" +\n                   "Authorization: Bearer " + line_token + "\\r\\n" +\n                   "Content-Type: application/json\\r\\n" +\n                   "Content-Length: " + payload.length() + "\\r\\n" +\n                   "\\r\\n" + payload;\n  line_client.print(request);\n}\n';
  var code = '';
  return code;
};

Blockly.Arduino['_02amani_linepushapi_msg'] = function(block) {
  var value_msg = Blockly.Arduino.valueToCode(block, 'msg', Blockly.Arduino.ORDER_ATOMIC);
  
  var code = 'pushLineMessage('+value_msg+');'+'\n';
  return code;
};