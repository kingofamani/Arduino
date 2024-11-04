Blockly.Blocks['_01amani_esp32joystick_init'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("ESP32 Joystick(3.3v)搖桿 初始化X");
    this.appendValueInput("xpin")
        .setCheck(null);
    this.appendDummyInput()
        .appendField(",Y");
    this.appendValueInput("ypin")
        .setCheck(null);
    this.appendDummyInput()
        .appendField(",按鈕");
    this.appendValueInput("swpin")
        .setCheck(null);
    this.appendDummyInput()
        .appendField(",旋轉")
        .appendField(new Blockly.FieldDropdown([["0°","0"], ["90°","90"], ["180°","180"], ["270°","270"]]), "angle");
    this.appendDummyInput()
        .appendField(",編號")
        .appendField(new Blockly.FieldDropdown([["第1個搖桿","1"], ["第2個搖桿","2"], ["第3個搖桿","3"], ["第4個搖桿","4"]]), "order");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(270);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_02amani_esp32joystick_dir'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("取得搖桿方向");
    this.appendDummyInput()
        .appendField(",編號")
        .appendField(new Blockly.FieldDropdown([["第1個搖桿","1"], ["第2個搖桿","2"], ["第3個搖桿","3"], ["第4個搖桿","4"]]), "order");
    this.setInputsInline(true);
    this.setOutput(true, null);
    this.setColour(270);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_03amani_esp32joystick_isdir'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("如果搖桿 方向是")
        .appendField(new Blockly.FieldDropdown([["↑","u"], ["↓","d"], ["←","l"], ["→","r"], ["↖","ul"], ["↙","dl"], ["↘","dr"], ["↗","ur"], ["中間",""]]), "direct");
    this.appendDummyInput()
        .appendField(",編號")
        .appendField(new Blockly.FieldDropdown([["第1個搖桿","1"], ["第2個搖桿","2"], ["第3個搖桿","3"], ["第4個搖桿","4"]]), "order");
    this.setInputsInline(true);
    this.setOutput(true, null);
    this.setColour(270);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_04amani_esp32joystick_sw'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("取得按鈕值,編號")
        .appendField(new Blockly.FieldDropdown([["第1個搖桿","1"], ["第2個搖桿","2"], ["第3個搖桿","3"], ["第4個搖桿","4"]]), "order");
    this.setOutput(true, null);
    this.setColour(270);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};