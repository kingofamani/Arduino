Blockly.Blocks['_01imi_gpscloud_init'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("iMi雲端平台ESP32 GPS板初始化");
    this.appendStatementInput("uart")
        .setCheck(null)
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("UART通訊");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(50);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_02imi_gpscloud_uart'] = {
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
    this.setColour(50);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_03imi_gpscloud_setup'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("Arduino Cloud雲端平台 setup區設定");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(50);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_04imi_gpscloud_loop'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("Arduino Cloud雲端平台 loop區設定");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(50);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_05imi_gpscloud_getesp32xy'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("[取得]ESP32 MQTT板訊息:XY座標");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(50);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_06imi_gpscloud_googlemap'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("開始模擬Google Map地圖移動");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(50);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};