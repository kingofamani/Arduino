Blockly.Blocks['01imi_esp32car_init'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("iMi小車模組ESP32初始化");
    this.appendStatementInput("uart")
        .setCheck(null)
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("UART通訊");
    this.appendStatementInput("wifi")
        .setCheck(null)
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("WiFi設定");
    this.appendStatementInput("line")
        .setCheck(null)
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("LINE設定");
    this.appendStatementInput("mqtt")
        .setCheck(null)
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("MQTT設定");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(230);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['02imi_esp32car_init_uart'] = {
  init: function() {
    this.appendValueInput("rx")
        .setCheck(null)
        .appendField("RX:");
    this.appendValueInput("tx")
        .setCheck(null)
        .appendField("TX:");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(230);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['03imi_esp32car_init_wifi'] = {
  init: function() {
    this.appendValueInput("ssid")
        .setCheck(null)
        .appendField("ssid:");
    this.appendValueInput("wifi_pwd")
        .setCheck(null)
        .appendField("密碼:");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(230);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['04imi_esp32car_init_line'] = {
  init: function() {
    this.appendValueInput("line_token")
        .setCheck(null)
        .appendField("權杖");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(230);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['05imi_esp32car_init_mqtt'] = {
  init: function() {
    this.appendValueInput("mqtt_user")
        .setCheck(null)
        .appendField("帳號");
    this.appendValueInput("mqtt_pwd")
        .setCheck(null)
        .appendField("密碼");
    this.appendValueInput("mqtt_port")
        .setCheck(null)
        .appendField("port");
    this.appendValueInput("mqtt_server")
        .setCheck(null)
        .appendField("服務器");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(230);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['06imi_esp32car_loop'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("iMi小車模組ESP32 重複區");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(230);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['07imi_esp32car_getarduino_func'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("接收Arduino訊息函數");
    this.appendStatementInput("msg")
        .setCheck(null);
	this.setInputsInline(true);
    this.setColour(230);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};




Blockly.Blocks['08imi_esp32car_submqtt'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("[訂閱]MQTT主題")
        .appendField(new Blockly.FieldDropdown([["MAP_SET","TOPIC_MAP_SET"], ["CAR_STANDBY","TOPIC_CAR_STANDBY"], ["CAR_GPS","TOPIC_CAR_GPS"], ["GOODS_LOAD","TOPIC_GOODS_LOAD"], ["CAR_LOWPOWER","TOPIC_CAR_LOWPOWER"]]), "mqtt_topic");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(230);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['09imi_esp32car_mqttcallback_func'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("MQTT回覆函數");
    this.appendStatementInput("msg")
        .setCheck(null);
    this.setColour(230);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['10imi_esp32car_ismqtttopic'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("MQTT主題是")
        .appendField(new Blockly.FieldDropdown([["MAP_SET","TOPIC_MAP_SET"], ["CAR_STANDBY","TOPIC_CAR_STANDBY"], ["CAR_GPS","TOPIC_CAR_GPS"], ["GOODS_LOAD","TOPIC_GOODS_LOAD"], ["CAR_LOWPOWER","TOPIC_CAR_LOWPOWER"]]), "mqtt_topic");
    this.setOutput(true, null);
    this.setColour(230);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['11imi_esp32car_sendarduino_mapset'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("[傳送]至Arduino 類型：MAP_SET");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(230);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['12imi_esp32car_pubmqtt_carstandby'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("[發佈]MQTT主題：CAR_STANDBY");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(230);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['13imi_esp32car_sendarduino_goodsload'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("[傳送]至Arduino 類型：GOODS_LOAD");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(230);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['14imi_esp32car_isarduinomsg'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("Arduino傳來類型是")
        .appendField(new Blockly.FieldDropdown([["MAP_SET","MAP_SET"], ["GOODS_LOAD","GOODS_LOAD"], ["LINE_NOTIFY","LINE_NOTIFY"], ["CAR_GPS","CAR_GPS"]]), "uart_topic");
    this.setOutput(true, null);
    this.setColour(230);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['15imi_esp32car_getarduino_recipient'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("[接收]Arduion傳來的收貨人資料");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(230);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['16imi_esp32car_line_recipient'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("發送LINE通知收貨人");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(230);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['17imi_esp32car_getarduino_gps'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("[接收]Arduino傳來的GPS座標");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(230);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['18imi_esp32car_pubmqtt_cargps'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("[發佈]MQTT主題：TOPIC_CAR_GPS");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(230);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};