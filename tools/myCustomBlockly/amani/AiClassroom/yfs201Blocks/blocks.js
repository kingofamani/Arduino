Blockly.Blocks['amani_fake_yfs201_init'] = {
  init: function() {
    this.appendValueInput("yfspin")
        .setCheck(null)
        .appendField("YF-S201水流量感測器 初始化 腳位");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(0);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['amani_fake_yfs201_flow'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("累計出水量(mL/s)");
    this.setOutput(true, null);
    this.setColour(0);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};