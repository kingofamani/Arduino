Blockly.Blocks['_01imi_mqttcloud_init'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("iMi雲端平台ESP32 MQTT板初始化");
    this.appendStatementInput("uart")
        .setCheck(null)
        .appendField("UART通訊");
    this.appendStatementInput("wifi")
        .setCheck(null)
        .appendField("WiFi設定");
    this.appendStatementInput("mqtt")
        .setCheck(null)
        .appendField("MQTT設定");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(80);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_02imi_mqttcloud_uart'] = {
  init: function() {
    this.appendValueInput("rx")
        .setCheck(null)
        .appendField("RX");
    this.appendValueInput("tx")
        .setCheck(null)
        .appendField("TX");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(80);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_03imi_mqttcloud_wifi'] = {
  init: function() {
    this.appendValueInput("ssid")
        .setCheck(null)
        .appendField("ssid");
    this.appendValueInput("wifipwd")
        .setCheck(null)
        .appendField("密碼");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(80);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_04imi_mqttcloud_mqtt'] = {
  init: function() {
    this.appendValueInput("mqtt_user")
        .setCheck(null)
        .appendField("帳號");
    this.appendValueInput("mqtt_pwd")
        .setCheck(null)
        .appendField("密碼");
    this.appendValueInput("port")
        .setCheck(null)
        .appendField("port");
    this.appendValueInput("mqtt_server")
        .setCheck(null)
        .appendField("服務器");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(80);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_05imi_mqttcloud_loop'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("Arduino Cloud雲端平台 loop區設定");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(80);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_06imi_mqttcloud_submqtt'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("[訂閱]MQTT主題")
        .appendField(new Blockly.FieldDropdown([["CAR_GPS","TOPIC_CAR_GPS"]]), "NAME");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(80);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_07imi_mqttcloud_mqttcallback_func'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("MQTT回覆函式");
    this.appendStatementInput("msg")
        .setCheck(null);
    this.setColour(80);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_08imi_mqttcloud_sendarduino_gps'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("[傳送]訊息至ESP32 GPS板:地圖xy座標");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(80);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};