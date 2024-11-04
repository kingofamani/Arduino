Blockly.Blocks['_01amani_uart_init'] = {
  init: function() {
	this.appendDummyInput()
        .appendField("如果序列埠");
    this.appendDummyInput()	 
		.setAlign(Blockly.ALIGN_RIGHT)	
		.appendField(new Blockly.FieldDropdown([
			["Serial","Serial"],
			["Serial1","Serial1"],
			["Serial2","Serial2"],
			["SoftwareSerial","softSerial"]				
		], this.validate), "serial");
    this.appendValueInput("rx","rx")
        .setCheck("Number")
		.appendField("RX");
    this.appendValueInput("tx","tx")
        .setCheck("Number")
		.appendField("TX");
	this.getInput("rx").setVisible(false);
	this.getInput("tx").setVisible(false);		
    this.appendDummyInput()	 
		.setAlign(Blockly.ALIGN_RIGHT)		
		.appendField("鮑率")	
		.appendField(new Blockly.FieldDropdown([
			["300","300"],
			["1200","1200"],
			["2400","2400"],
			["4800","4800"],
			["9600","9600"],	    
			["19200","19200"],
			["38400","38400"],
			["57600","57600"],
			["74880","74880"],
			["115200","115200"],	
			["230400","230400"],
			["250000","250000"],
			["500000","500000"],
			["1000000","1000000"],	
			["2000000","2000000"]
		]), "baudrate");
	this.appendDummyInput()
        .appendField("取得字串");			
    this.appendStatementInput("statement")
        .setCheck(null);
	this.setInputsInline(true);
	this.setPreviousStatement(!0);
	this.setNextStatement(!0);
	this.setColour(225);
  },
  validate: function(newValue) {
	 const block = this.sourceBlock_;
	 if (newValue=="Serial") {
		 block.getInput("rx").setVisible(false);
		 block.getInput("tx").setVisible(false);		 
	 }
	 else {
		 block.getInput("rx").setVisible(true);
		 block.getInput("tx").setVisible(true);		 
	 } 
  }
};

Blockly.Blocks['_02amani_uart_get'] = {
  init: function() {
	this.appendDummyInput()
        .appendField("序列埠");	  
	this.appendDummyInput()
        .appendField("讀取完整的字串");   
	this.setInputsInline(true);
    this.setOutput(true, null);  
    this.setColour(225);
  }
};

Blockly.Blocks['_03amani_uart_send'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("序列埠");
    this.appendDummyInput()	 
		.setAlign(Blockly.ALIGN_RIGHT)	
		.appendField(new Blockly.FieldDropdown([
			["Serial","Serial"],
			["Serial1","Serial1"],
			["Serial2","Serial2"],
			["SoftwareSerial","softSerial"]
		]), "serial");
	this.appendDummyInput()	 
		.setAlign(Blockly.ALIGN_RIGHT)	
		.appendField(new Blockly.FieldDropdown([
			["傳送資料(print)","print"],
			["傳送資料(print換行)","println"],
			["傳送資料(write)","write"]
		]), "send");
	this.appendValueInput("msg")
        .setCheck(null)
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(225);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};