Blockly.Blocks['_01imi_espcharge_init'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("iMi充電模組ESP32初始化");
    this.appendStatementInput("wifi")
        .setCheck(null)
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("WiFi設定");
    this.appendStatementInput("sheet")
        .setCheck(null)
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("Google試算表");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(20);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_02imi_espcharge_wifi'] = {
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
    this.setColour(20);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_03imi_espcharge_sheet'] = {
  init: function() {
    this.appendValueInput("sheetid")
        .setCheck(null)
        .appendField("ID");
    this.appendValueInput("stag")
        .setCheck(null)
        .appendField("工作表名稱");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(20);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_04mi_espcharge_writesheet'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("寫入Google試算表：")
        .appendField(new Blockly.FieldDropdown([["太陽能板產生能量","sun"], ["小車消耗能量","car"]]), "type");
    this.appendDummyInput()
        .appendField("的瓦數(mW)");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(20);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};