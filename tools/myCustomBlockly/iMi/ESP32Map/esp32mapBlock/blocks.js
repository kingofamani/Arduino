Blockly.Blocks['_01imi_espmap_init'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("iMi地圖模組ESP32初始化");
    this.appendStatementInput("wifi")
        .setCheck(null)
        .appendField("WiFi設定");
    this.appendStatementInput("mqtt")
        .setCheck(null)
        .appendField("MQTT設定");
    this.appendStatementInput("button")
        .setCheck(null)
        .appendField("佈置完成鈕");
    this.appendStatementInput("map")
        .setCheck(null)
        .appendField("地圖陣列");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(110);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_02imi_espmap_wifi'] = {
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
    this.setColour(110);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_03imi_espmap_mqtt'] = {
  init: function() {
    this.appendValueInput("mqtt_user")
        .setCheck(null)
        .appendField("帳號");
    this.appendValueInput("mqtt_pwd")
        .setCheck(null)
        .appendField("密碼");
    this.appendValueInput("mqtt_port")
        .setCheck(null)
        .appendField("port");
    this.appendValueInput("mqtt_server")
        .setCheck(null)
        .appendField("服務器");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(110);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_04imi_espmap_button'] = {
  init: function() {
    this.appendValueInput("btnpin")
        .setCheck(null)
        .appendField("腳位");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(110);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_05imi_espmap_map'] = {
  init: function() {
    this.appendValueInput("00")
        .setCheck(null);
    this.appendValueInput("01")
        .setCheck(null);
    this.appendValueInput("02")
        .setCheck(null);
    this.appendValueInput("03")
        .setCheck(null);
    this.appendValueInput("04")
        .setCheck(null);
    this.appendValueInput("05")
        .setCheck(null);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(110);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_06imi_espmap_loop'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("iMi地圖模組ESP32 重複區");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(110);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_07imi_espmap_isbutton'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("按下佈置完成鈕");
    this.setOutput(true, null);
    this.setColour(110);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_08imi_espmap_pubmqtt_mapset'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("[發佈]MQTT主題：MAP_SET");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(110);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_05imi_espmap_maps'] = {
  init: function() {
    this.appendStatementInput("msg")
        .setCheck(null)
        .appendField("地圖陣列");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(110);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};