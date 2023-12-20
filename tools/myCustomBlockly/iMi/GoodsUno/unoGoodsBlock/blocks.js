Blockly.Blocks['_01imi_unogoods_init'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("iMi物流模組UNO初始化");
    this.appendStatementInput("cnc")
        .setCheck(null)
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("CNC腳位");
    this.appendStatementInput("uart")
        .setCheck(null)
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("UART通訊");
    this.appendStatementInput("servopin")
        .setCheck(null)
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("撿貨伺服馬達");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(170);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_02imi_unogoods_cnc'] = {
  init: function() {
    this.appendValueInput("en")
        .setCheck(null)
        .appendField("致能");
    this.appendValueInput("xdir")
        .setCheck(null)
        .appendField("x方向");
    this.appendValueInput("xstep")
        .setCheck(null)
        .appendField("x步進");
    this.appendValueInput("ydir")
        .setCheck(null)
        .appendField("y方向");
    this.appendValueInput("ystep")
        .setCheck(null)
        .appendField("y步進");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(170);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_03imi_unogoods_uart'] = {
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
    this.setColour(170);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_04imi_unogoods_servopin'] = {
  init: function() {
    this.appendValueInput("servo")
        .setCheck(null)
        .appendField("腳位");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(170);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_05imi_unogoods_esp32'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("當接收ESP32訊息時");
    this.appendStatementInput("msg")
        .setCheck(null)
        .appendField("");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(170);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_06imi_unogoods_xy'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("取得貨物在倉庫xy座標");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(170);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_07imi_unogoods_findgoods'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("CNC開始依座標找尋貨物");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(170);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_08imi_unogoods_servo'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldDropdown([["撿貨伺服馬達","servoPick"]]), "servo");
    this.appendDummyInput()
        .appendField("設定為");
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldDropdown([["推貨","180"], ["拉回","0"]]), "angle");
    this.appendDummyInput()
        .appendField("角度");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(170);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_09imi_unogoods_reset'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("電機位置歸零");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(170);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_10imi_unogoods_sendesp32'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("[傳送]訊息至ESP32")
        .appendField(new Blockly.FieldDropdown([["GOODS_LOAD","GOODS_LOAD"]]), "NAME");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(170);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};