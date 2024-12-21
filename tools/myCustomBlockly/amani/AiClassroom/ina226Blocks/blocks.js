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