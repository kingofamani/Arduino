Blockly.Blocks['amani_fake_cnc_init'] = {
  init: function() {
    this.appendValueInput("cncenable")
        .setCheck(null)
        .appendField("步進馬達 CNC控制板 致能");
    this.appendValueInput("xdir")
        .setCheck(null)
        .appendField("X方向");
    this.appendValueInput("xstep")
        .setCheck(null)
        .appendField("X步進");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(195);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['amani_fake_cnc_xmove'] = {
  init: function() {
    this.appendValueInput("xmove")
        .setCheck(null)
        .appendField("馬達X軸移動至");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(195);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['amani_fake_cnc_xcurrent'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("取得目前步進馬達X軸位置");
    this.setOutput(true, null);
    this.setColour(195);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};