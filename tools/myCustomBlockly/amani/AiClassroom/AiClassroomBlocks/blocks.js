Blockly.Blocks['amani_fake_ina226_init'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("初始化INA226數位電表 編號")
        .appendField(new Blockly.FieldDropdown([["0","0"], ["1","1"], ["2","2"]]), "inachannel");
    this.setOutput(true, null);
    this.setColour(75);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['amani_fake_ina226_mv'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("分流電壓mV 編號")
        .appendField(new Blockly.FieldDropdown([["0","0"], ["1","1"], ["2","2"]]), "mvchannel");
    this.setOutput(true, null);
    this.setColour(75);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['amani_fake_ina226_ma'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("電流mV 編號")
        .appendField(new Blockly.FieldDropdown([["0","0"], ["1","1"], ["2","2"]]), "machannel");
    this.setOutput(true, null);
    this.setColour(75);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

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