Blockly.Blocks['_01amani_simpletimer_setinteval'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("每");
    this.appendValueInput("ms")
        .setCheck(null);
    this.appendDummyInput()
        .appendField("毫秒(ms)執行1次");
    this.appendDummyInput()
        .appendField("編號")
        .appendField(new Blockly.FieldDropdown([ ["0","0"],["1","1"], ["2","2"], ["3","3"], ["4","4"], ["5","5"], ["6","6"], ["7","7"], ["8","8"], ["9","9"]]), "order");
    this.appendStatementInput("msg")
        .setCheck(null);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(230);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_02amani_simpletimer_setinteval_id'] = {
  init: function() { 
	this.appendDummyInput()
        .appendField("預備計時：");       
    this.appendDummyInput()
        .appendField("每");
    this.appendValueInput("ms")
        .setCheck(null);    
    this.appendDummyInput()
        .appendField("毫秒(ms)執行1次");
    this.appendDummyInput()
        .appendField("編號")
        .appendField(new Blockly.FieldDropdown([ ["0","0"],["1","1"], ["2","2"], ["3","3"], ["4","4"], ["5","5"], ["6","6"], ["7","7"], ["8","8"], ["9","9"]]), "order");
    this.appendStatementInput("msg")
        .setCheck(null);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(50);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_03amani_simpletimer_setinteval_enable'] = {
  init: function() {
    this.appendDummyInput()
        .appendField(new Blockly.FieldDropdown([ ["開始","enable"],["暫停","disable"]]), "switch");
    this.appendDummyInput()
        .appendField("計時");
    this.appendDummyInput()
        .appendField("編號")
        .appendField(new Blockly.FieldDropdown([ ["0","0"],["1","1"], ["2","2"], ["3","3"], ["4","4"], ["5","5"], ["6","6"], ["7","7"], ["8","8"], ["9","9"]]), "order");
	this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(50);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_04amani_simpletimer_settimeout'] = {
  init: function() {    
    this.appendDummyInput()
    this.appendValueInput("ms")
        .setCheck(null);    
    this.appendDummyInput()
        .appendField("毫秒(ms)後執行，只執行1次");
    this.appendDummyInput()
        .appendField("編號")
        .appendField(new Blockly.FieldDropdown([ ["0","0"],["1","1"], ["2","2"], ["3","3"], ["4","4"], ["5","5"], ["6","6"], ["7","7"], ["8","8"], ["9","9"]]), "order");
	this.appendStatementInput("msg")
        .setCheck(null);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(170);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_05amani_simpletimer_settimer'] = {
  init: function() {
	this.appendDummyInput()
        .appendField("每隔");
    this.appendValueInput("ms")
        .setCheck(null);    
    this.appendDummyInput()
        .appendField("毫秒(ms)觸發1次，總共");
	this.appendValueInput("times")
        .setCheck(null); 
	this.appendDummyInput()
        .appendField("次");
    this.appendDummyInput()
        .appendField("編號")
        .appendField(new Blockly.FieldDropdown([ ["0","0"],["1","1"], ["2","2"], ["3","3"], ["4","4"], ["5","5"], ["6","6"], ["7","7"], ["8","8"], ["9","9"]]), "order");
	this.appendStatementInput("msg")
        .setCheck(null);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(140);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};