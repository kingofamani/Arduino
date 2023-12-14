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

Blockly.Blocks['amani_random'] = {
  init: function() {
    this.appendValueInput("min")
        .setCheck("Number")
        .appendField("隨機 最小整數");
    this.appendValueInput("max")
        .setCheck("Number")
        .appendField("最大整數");
    this.setInputsInline(true);
    this.setOutput(true, null);
    this.setColour(15);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['amani_stepmoter_go'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("步進馬達 開始轉動");
    this.appendValueInput("in1")
        .setCheck("Number")
        .appendField("IN1腳位");
    this.appendValueInput("in2")
        .setCheck("Number")
        .appendField("IN2腳位");
    this.appendValueInput("in3")
        .setCheck("Number")
        .appendField("IN3腳位");
    this.appendValueInput("in4")
        .setCheck("Number")
        .appendField("IN4腳位");
    this.appendValueInput("c")
        .setCheck(null)
        .appendField("圈數");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(60);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['amani_joystick_init'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("Joystick搖桿 初始化");
    this.appendDummyInput()
        .appendField("vX腳位")
        .appendField(new Blockly.FieldDropdown([["A0","A0"], ["A1","A1"], ["A2","A2"], ["A3","A3"], ["A4","A4"], ["A5","A5"]]), "xPin");
    this.appendDummyInput()
        .appendField("vY腳位")
        .appendField(new Blockly.FieldDropdown([["A0","A0"], ["A1","A1"], ["A2","A2"], ["A3","A3"], ["A4","A4"], ["A5","A5"]]), "yPin");
    this.appendValueInput("swPin")
        .setCheck("Number")
        .appendField("SW腳位");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(90);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['amani_joystick_switch'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("Joystick搖桿 已按下按鈕");
    this.setInputsInline(true);
    this.setOutput(true, null);
    this.setColour(90);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['amani_joystick_direct'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("Joystick搖桿 方向是")
        .appendField(new Blockly.FieldDropdown([["↑","Up"], ["↓","Down"], ["←","Left"], ["→","Right"], ["↖","LeftUp"], ["↙","LeftDown"], ["↘","RightDown"], ["↗","RightUp"], ["中間",""]]), "direct");
    this.setInputsInline(true);
    this.setOutput(true, null);
    this.setColour(90);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};