Blockly.Blocks['_01amani_i2ckeypad_init'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("I2C的4x4鍵盤 初始化");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(110);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_02amani_i2ckeypad_loop'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("I2C的4x4鍵盤 Loop區");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(110);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_03amani_i2ckeypad_iskey'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("有按下按鍵");
    this.setOutput(true, null);
    this.setColour(110);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_04amani_i2ckeypad_key'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("取得按鍵值");
    this.setOutput(true, null);
    this.setColour(110);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_05amani_i2ckeypad_keynull'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("按鍵值清空");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(110);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_06amani_i2ckeypad_funcnum'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("按鍵值char轉換成數值int");
    this.appendValueInput("c")
        .setCheck(null);
    this.setInputsInline(true);
    this.setOutput(true, null);
    this.setColour(110);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_07amani_i2ckeypad_isnum'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("按鍵值是數字");
    this.appendValueInput("c")
        .setCheck(null);
    this.setInputsInline(true);
    this.setOutput(true, null);
    this.setColour(110);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};