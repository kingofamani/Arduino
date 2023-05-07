Blockly.Blocks['amani_tm1637_show'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("4位數字顯示模組 顯示數字");
    this.appendValueInput("clk")
        .setCheck("Number")
        .appendField("CLK腳位");
    this.appendValueInput("dio")
        .setCheck("Number")
        .appendField("DIO腳位");
    this.appendValueInput("num")
        .setCheck("Number")
        .appendField("數字");
    this.appendDummyInput()
        .appendField("補零")
        .appendField(new Blockly.FieldDropdown([["true","true"], ["false","false"]]), "leading_zero");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(230);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['amani_tm1637_clear'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("4位數字顯示模組 清除畫面");
    this.appendValueInput("clk")
        .setCheck("Number")
        .appendField("CLK腳位");
    this.appendValueInput("dio")
        .setCheck("Number")
        .appendField("DIO腳位");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(230);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['amani_tm1637_colon'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("4位數字顯示模組 顯示數字(冒號)");
    this.appendValueInput("clk")
        .setCheck("Number")
        .appendField("CLK腳位");
    this.appendValueInput("dio")
        .setCheck("Number")
        .appendField("DIO腳位");
    this.appendValueInput("num1")
        .setCheck("Number")
        .appendField("數字1");
    this.appendValueInput("num2")
        .setCheck("Number")
        .appendField("數字2");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(230);
 this.setTooltip("例如:數字1=12、數字2=34，則顯示12:34");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['amani_st7920lcd_string'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("4x16 LCD螢幕 顯示文字");
    this.appendValueInput("row")
        .setCheck("Number")
        .appendField("列數");
    this.appendValueInput("col")
        .setCheck("Number")
        .appendField("格數");
    this.appendValueInput("str")
        .setCheck("Array")
        .appendField("文字陣列");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(300);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['amani_st7920lcd_clear'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("4x16 LCD螢幕 清除畫面");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(300);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};