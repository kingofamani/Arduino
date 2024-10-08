Blockly.Blocks['_01amani_linepushapi_init'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("LinePushAPI通知 使用者ID");
    this.appendValueInput("userid")
        .setCheck(null);
    this.appendDummyInput()
        .appendField("權仗");
    this.appendValueInput("token")
        .setCheck(null);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(135);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_02amani_linepushapi_msg'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("LinePushAPI通知 傳送文字訊息");
    this.appendValueInput("msg")
        .setCheck(null);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(135);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};