Blockly.Blocks['_01amani_serial_avail'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("如果")
        .appendField(new Blockly.FieldDropdown([["Serial","Serial"], ["Serial1","Serial1"], ["Serial2","Serial2"]]), "serial");
    this.appendDummyInput()
        .appendField("讀取到字串");
    this.appendStatementInput("msg")
        .setCheck(null);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(195);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_02amani_serial_readstring'] = {
  init: function() {
    this.appendDummyInput()
        .appendField(new Blockly.FieldDropdown([["Serial","Serial"], ["Serial1","Serial1"], ["Serial2","Serial2"]]), "serial");
    this.appendDummyInput()
        .appendField("讀取到的完整字串內容");
    this.setInputsInline(true);
    this.setOutput(true, null);
    this.setColour(195);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};