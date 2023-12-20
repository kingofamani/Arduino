Blockly.Blocks['_01imi_espgoods_init'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("iMi物流模組ESP32初始化");
    this.appendStatementInput("wifi")
        .setCheck(null)
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("WiFi設定");
    this.appendStatementInput("mqtt")
        .setCheck(null)
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("MQTT設定");
    this.appendStatementInput("uart")
        .setCheck(null)
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("UART通訊");
    this.appendStatementInput("sheet")
        .setCheck(null)
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("Google試算表");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(140);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_02imi_espgoods_wifi'] = {
  init: function() {
    this.appendValueInput("ssid")
        .setCheck(null)
        .appendField("ssid");
    this.appendValueInput("wifipwd")
        .setCheck(null)
        .appendField("密碼");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(140);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_03imi_espgoods_mqtt'] = {
  init: function() {
    this.appendValueInput("mqtt_user")
        .setCheck(null)
        .appendField("帳號");
    this.appendValueInput("mqtt_pwd")
        .setCheck(null)
        .appendField("密碼");
    this.appendValueInput("port")
        .setCheck(null)
        .appendField("port");
    this.appendValueInput("mqtt_server")
        .setCheck(null)
        .appendField("服務器");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(140);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_04imi_espgoods_uart'] = {
  init: function() {
    this.appendValueInput("rx")
        .setCheck(null)
        .appendField("RX");
    this.appendValueInput("tx")
        .setCheck(null)
        .appendField("TX");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(140);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_05imi_espgoods_sheet'] = {
  init: function() {
    this.appendValueInput("sheetid")
        .setCheck(null)
        .appendField("ID");
    this.appendValueInput("stag")
        .setCheck(null)
        .appendField("工作表名稱");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(140);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_06imi_espgoods_loop'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("iMi物流模組ESP32 重複區");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(140);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_07imi_espgoods_submqtt'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("[訂閱]MQTT主題")
        .appendField(new Blockly.FieldDropdown([["MAP_SET","TOPIC_MAP_SET"], ["CAR_STANDBY","TOPIC_CAR_STANDBY"], ["CAR_GPS","TOPIC_CAR_GPS"], ["GOODS_LOAD","TOPIC_GOODS_LOAD"], ["CAR_LOWPOWER","TOPIC_CAR_LOWPOWER"]]), "mqtt_topic");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(140);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_08imi_espgoods_mqttcallback_func'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("MQTT回覆函數");
    this.appendStatementInput("msg")
        .setCheck(null);
    this.setColour(140);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_09imi_espgoods_ismqtttopic'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("MQTT主題是")
        .appendField(new Blockly.FieldDropdown([["MAP_SET","TOPIC_MAP_SET"], ["CAR_STANDBY","TOPIC_CAR_STANDBY"], ["CAR_GPS","TOPIC_CAR_GPS"], ["GOODS_LOAD","TOPIC_GOODS_LOAD"], ["CAR_LOWPOWER","TOPIC_CAR_LOWPOWER"]]), "mqtt_topic");
    this.setOutput(true, null);
    this.setColour(140);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_10imi_espgoods_readsheet'] = {
  init: function() {
    this.appendValueInput("field")
        .setCheck(null)
        .appendField("讀取Google試算表");
    this.appendValueInput("name")
        .setCheck(null)
        .appendField("欄位 為");
    this.appendDummyInput()
        .appendField("的資料");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(140);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_11imi_espgoods_sendarduino_pick'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("[傳送]訊息至Arduino:依商品xy座標 自動撿貨");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(140);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_12imi_espgoods_getarduino_func'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("接收Arduino訊息函數");
    this.appendStatementInput("msg")
        .setCheck(null);
    this.setColour(140);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_13imi_espgoods_isarduinomsg'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("Arduino傳來類型是")
        .appendField(new Blockly.FieldDropdown([["GOODS_LOAD","GOODS_LOAD"]]), "msg");
    this.setOutput(true, null);
    this.setColour(140);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_14imi_espgoods_pubmqtt_goods'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("[發佈]MQTT主題：GOODS_LOAD");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(140);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};