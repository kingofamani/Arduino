Blockly.Blocks['fu_ez_digitalwrite'] = {
  init: function() {
    this.appendDummyInput()
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("EZ+")
        .appendField(new Blockly.FieldDropdown([["紅燈","0"], ["黃燈","1"], ["綠燈","2"]]), "led");
    this.appendDummyInput()
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("狀態")
        .appendField(new Blockly.FieldDropdown([["開","1"], ["關","0"]]), "value");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(20);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks['fu_ez_digitalwrite_input'] = {
  init: function() {
    this.appendDummyInput()
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("EZ+")
        .appendField(new Blockly.FieldDropdown([["紅燈","0"], ["黃燈","1"], ["綠燈","2"]]), "led");
    this.appendValueInput("value")
        .setCheck("Number")
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("數位輸出值");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(20);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks['fu_ez_digitalwrite_input_relay'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("EZ+")
        .appendField("繼電器")
        .appendField("數位輸出值"); 
   this.appendValueInput("value")
        .setCheck("Number")
        .setAlign(Blockly.ALIGN_RIGHT);     
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(20);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks['fu_ez_analogwrite_input'] = {
  init: function() {
    this.appendDummyInput()
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("EZ+")
        .appendField(new Blockly.FieldDropdown([["紅燈","0"], ["黃燈","1"], ["綠燈","2"]]), "led");
    this.appendValueInput("value")
        .setCheck("Number")
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("類比輸出值");
    this.appendDummyInput()
        .appendField("(LinkIt7697)");		
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(50);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks['fu_ez_analogwrite_input_esp'] = {
  init: function() {
    this.appendDummyInput()
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("EZ+")
        .appendField(new Blockly.FieldDropdown([["紅燈","0"], ["黃燈","1"], ["綠燈","2"]]), "led");
    this.appendValueInput("value")
        .setCheck("Number")
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("類比輸出值");
    this.appendValueInput("channel")
        .setCheck("Number")
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("通道");
    this.appendDummyInput()
        .appendField("(ESP32)");		
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(65);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks['fu_ez_digitalread'] = {
  init: function() {
    this.appendDummyInput()
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("EZ+")
        .appendField(new Blockly.FieldDropdown([["按鈕A","0"],["按鈕B","1"]]), "button")
        .appendField("數位輸入值");
    this.setInputsInline(true);
    this.setOutput(true, null);
    this.setColour(80);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks['fu_ez_digitalread_button'] = {
  init: function() {
    this.appendDummyInput()
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("EZ+")
        .appendField(new Blockly.FieldDropdown([["按鈕A","A"],["按鈕B","B"],["按鈕A+B","AB"]]), "type")
        .appendField("按下");
    this.setInputsInline(true);
    this.setOutput(true, null);
    this.setColour(80);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks['fu_ez_analogread_potentiometer'] = {
  init: function() {
    this.appendDummyInput()
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("EZ+")
        .appendField("可變電阻")
        .appendField("類比輸入值");         
    this.setInputsInline(true);
    this.setOutput(true, null);
    this.setColour(110);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks['fu_ez_analogread_photoresistor'] = {
  init: function() {
    this.appendDummyInput()
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("EZ+")
        .appendField("光感測器")
        .appendField("類比輸入值");         
    this.setInputsInline(true);
    this.setOutput(true, null);
    this.setColour(110);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks['fu_ez_buzzer_tone'] = {
  init: function() {
    this.appendDummyInput()
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("EZ+")
        .appendField("蜂鳴器");
    this.appendValueInput("frequency")
        .setCheck("Number")
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("頻率");
    this.appendDummyInput()
        .appendField("(LinkIt7697)");		
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(140);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks['fu_ez_buzzer_tone_duration'] = {
  init: function() {
    this.appendDummyInput()
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("EZ+")
        .appendField("蜂鳴器");
    this.appendValueInput("frequency")
        .setCheck("Number")
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("頻率");
    this.appendValueInput("duration")
        .setCheck("Number")
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("持續時間(ms)");
    this.appendDummyInput()
        .appendField("(LinkIt7697)");		
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(140);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks['fu_ez_buzzer_notone'] = {
  init: function() {
    this.appendDummyInput()
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("EZ+")
        .appendField("蜂鳴器")
        .appendField("停止");
    this.appendDummyInput()
        .appendField("(LinkIt7697)");		
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(140);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['fu_ez_buzzer_tone_duration_esp'] = {
  init: function() {
    this.appendDummyInput()
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("EZ+")
        .appendField("蜂鳴器");
    this.appendValueInput("frequency")
        .setCheck("Number")
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("頻率");
    this.appendValueInput("duration")
        .setCheck("Number")
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("持續時間(ms)");
    this.appendValueInput("channel")
        .setCheck("Number")
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("通道");		
    this.appendDummyInput()
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("(ESP32)");		
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(155);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks['fu_ez_buzzer_tone_duration_esp_array'] = {
  init: function() {
    this.appendDummyInput()
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("EZ+")
        .appendField("蜂鳴器");
    this.appendValueInput("frequency")
        .setCheck(null)
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("頻率");
    this.appendValueInput("duration")
        .setCheck(null)
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("持續時間(ms)");
    this.appendValueInput("channel")
        .setCheck("Number")
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("通道");		
    this.appendDummyInput()
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("(ESP32)");		
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(155);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks['fu_ez_dht11'] = {
  init: function() {
    this.appendDummyInput()
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("EZ+")
        .appendField("DHT11");
    this.appendDummyInput()
        .appendField(new Blockly.FieldDropdown([
         ["相對溼度%","dht.readHumidity()"], 
         ["溫度°C","dht.readTemperature()"]
         ]), "type");
    this.setInputsInline(true);
    this.setOutput(true, null);
    this.setColour(170);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['fu_ez_pixel_rgb'] = {
  init: function() {
    this.appendDummyInput()
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("EZ+")
        .appendField("全彩LED");
    this.appendDummyInput()
        .appendField("燈號")
        .appendField(new Blockly.FieldDropdown([["第1顆","0"], ["第2顆","1"], ["第3顆","2"]]), "no");
    this.appendDummyInput()
        .appendField("顏色");		
    this.appendValueInput("R")
        .setCheck("Number")
        .appendField("R");
    this.appendValueInput("G")
        .setCheck("Number")
        .appendField("G");
    this.appendValueInput("B")
        .setCheck("Number")
        .appendField("B");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(200);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['fu_ez_pixel_picker'] = {
  init: function() {
    this.appendDummyInput()
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("EZ+")
        .appendField("全彩LED");
    this.appendDummyInput()
        .appendField("燈號")
        .appendField(new Blockly.FieldDropdown([["第1顆","0"], ["第2顆","1"], ["第3顆","2"]]), "no");
    this.appendDummyInput()
        .appendField("顏色")
        .appendField(new Blockly.FieldColour("#ff0000"), "value");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(200);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['fu_ez_pixel_clear'] = {
  init: function() {
    this.appendDummyInput()
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("EZ+")
        .appendField("全彩LED")
        .appendField("清除亮燈");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(200);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['fu_ez_ir_receive'] = {
  init: function() {
    this.appendDummyInput()
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("EZ+")
        .appendField("紅外線接收器")
        .appendField("讀取到訊號時執行");
    this.appendDummyInput()
        .appendField(new Blockly.FieldVariable("irValue"), "value")
        .appendField("取得訊號編碼(字串)");
    this.appendDummyInput()
        .appendField(new Blockly.FieldVariable("irType"), "type")
        .appendField("取得訊號協定(字串)");
    this.appendStatementInput("execute")
        .setCheck(null);
    this.setInputsInline(false);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(230);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};


Blockly.Blocks['fu_ez_oled_draw'] = {
  init: function() {
    this.appendDummyInput()
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("EZ+")
        .appendField("OLED")
        .appendField("開始繪圖");
    this.appendStatementInput("draw")
        .setCheck(null);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(260);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['fu_ez_oled_drawstr'] = {
  init: function() {
    this.appendDummyInput()
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("EZ+")
        .appendField("OLED")
        .appendField("描繪文字");
    this.appendValueInput("x")
        .setCheck("Number")
        .appendField("x");
    this.appendValueInput("y")
        .setCheck("Number")
        .appendField("y");
    this.appendValueInput("str")
        .setCheck(null)
        .appendField("文字");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(260);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};