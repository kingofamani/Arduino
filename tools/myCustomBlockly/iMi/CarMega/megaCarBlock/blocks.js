Blockly.Blocks['_01imi_megacar_init'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("iMi小車模組Mega初始化");
    this.appendStatementInput("uart")
        .setCheck(null)
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("UART通訊");
    this.appendStatementInput("track")
        .setCheck(null)
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("循跡感測器");
    this.appendStatementInput("trig")
        .setCheck(null)
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("循跡感測器");
    this.appendStatementInput("carbox")
        .setCheck(null)
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("貨斗伺服馬達");
    this.appendStatementInput("aicam")
        .setCheck(null)
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("AI鏡頭伺服馬達");
    this.appendStatementInput("sign")
        .setCheck(null)
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("簽收鈕");
    this.appendStatementInput("l298n")
        .setCheck(null)
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("L298N馬達腳位");
    this.appendStatementInput("l298n2")
        .setCheck(null)
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField("L298N PWM腳位");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(200);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_02imi_megacar_init_uart'] = {
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
    this.setColour(200);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_03imi_megacar_init_track'] = {
  init: function() {
    this.appendValueInput("left")
        .setCheck(null)
        .appendField("左");
    this.appendValueInput("front")
        .setCheck(null)
        .appendField("前");
    this.appendValueInput("back")
        .setCheck(null)
        .appendField("後");
    this.appendValueInput("right")
        .setCheck(null)
        .appendField("右");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(200);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_04imi_megacar_init_trig'] = {
  init: function() {
    this.appendValueInput("trig")
        .setCheck(null)
        .appendField("觸發值");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(200);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_05imi_megacar_init_carbox'] = {
  init: function() {
    this.appendValueInput("carbox")
        .setCheck(null)
        .appendField("腳位");
    this.appendValueInput("open")
        .setCheck(null)
        .appendField("打開角度");
    this.appendValueInput("close")
        .setCheck(null)
        .appendField("關閉角度");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(200);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_06imi_megacar_init_aicam'] = {
  init: function() {
    this.appendValueInput("aicam")
        .setCheck(null)
        .appendField("腳位");
    this.appendValueInput("front")
        .setCheck(null)
        .appendField("向前角度");
    this.appendValueInput("up")
        .setCheck(null)
        .appendField("向上角度");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(200);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_07imi_megacar_init_sign'] = {
  init: function() {
    this.appendValueInput("sign")
        .setCheck(null)
        .appendField("腳位");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(200);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_08imi_megacar_init_l298n'] = {
  init: function() {
    this.appendValueInput("in1")
        .setCheck(null)
        .appendField("IN1~IN8");
    this.appendValueInput("in2")
        .setCheck(null)
        .appendField("");
    this.appendValueInput("in3")
        .setCheck(null)
        .appendField("");
    this.appendValueInput("in4")
        .setCheck(null)
        .appendField("");
    this.appendValueInput("in5")
        .setCheck(null)
        .appendField("");
    this.appendValueInput("in6")
        .setCheck(null)
        .appendField("");
    this.appendValueInput("in7")
        .setCheck(null)
        .appendField("");
    this.appendValueInput("in8")
        .setCheck(null)
        .appendField("");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(200);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_09imi_megacar_init_l298n2'] = {
  init: function() {
    this.appendValueInput("en1")
        .setCheck(null)
        .appendField("EN1~EN4");
    this.appendValueInput("en2")
        .setCheck(null)
        .appendField("");
    this.appendValueInput("en3")
        .setCheck(null)
        .appendField("");
    this.appendValueInput("en4")
        .setCheck(null)
        .appendField("");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(200);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_10imi_megacar_astar'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("A*演算法初始化");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(200);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_11imi_megacar_esp32'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("當接收ESP32訊息時");
    this.appendStatementInput("msg")
        .setCheck(null);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(200);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_12imi_megacar_isesp32msg'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("ESP32訊息包含")
        .appendField(new Blockly.FieldDropdown([["MAP_SET","MAP_SET"], ["GOODS_LOAD","GOODS_LOAD"], ["LINE_NOTIFY","LINE_NOTIFY"], ["CAR_GPS","CAR_GPS"]]), "msg");
    this.setOutput(true, null);
    this.setColour(200);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_13imi_megacar_servo'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldDropdown([["貨斗伺服馬達","servoCarBox"], ["AI鏡頭伺服馬達","servoAiCam"]]), "servo");
    this.appendDummyInput()
        .appendField("設定為");
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldDropdown([["打開","ANGLE_CAR_BOX_OPEN"], ["關閉","ANGLE_CAR_BOX_CLOSE"], ["朝前","ANGLE_AI_CAM_FRONT"], ["向上","ANGLE_AI_CAM_UP"]]), "angle");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(200);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_14imi_megacar_savemap'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("儲存地圖陣列");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(200);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_15imi_megacar_savereci'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("儲存收件人陣列");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(200);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_16imi_megacar_startastar'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("開始A*路徑規劃:  終點")
        .appendField(new Blockly.FieldDropdown([["物流站","GOODS_POINT"], ["充電站","CHARGE_POINT"], ["收件人","Recipient_POINT"]]), "point");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(200);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_17imi_megacar_standbyaicam'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("AI鏡頭朝向,準備人臉識別收貨人");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(200);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_18imi_megacar_esp32line'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("[傳送]通知至ESP32：LINE通知收件人");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(200);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_19imi_megacar_startdetectobject'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("等待AI人臉識別");
    this.appendStatementInput("msg")
        .setCheck(null);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(200);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_20imi_megacar_isfaceid'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("人臉ID=")
        .appendField(new Blockly.FieldDropdown([["1","FACE_ID1"]]), "id");
    this.setOutput(true, null);
    this.setColour(200);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_21imi_megacar_currentalgo'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("AI識別模式切換為:")
        .appendField(new Blockly.FieldDropdown([["物件識別","ALGORITHM_OBJECT_RECOGNITION"], ["人臉識別","ALGORITHM_FACE_RECOGNITION"]]), "algo");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(200);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_22imi_megacar_issign'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("按下簽收鈕");
    this.setOutput(true, null);
    this.setColour(200);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_23imi_megacar_carheadturn'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("車頭旋轉")
        .appendField(new Blockly.FieldDropdown([["朝上","'U'"], ["朝右","'R'"], ["朝下","'D'"], ["朝左","'L'"]]), "direct");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(200);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_24imi_megacar_getpower'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("取得小車當前電量");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(200);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_25imi_megacar_islowpower'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("電量低於")
        .appendField(new Blockly.FieldDropdown([["20%","0.2"], ["15%","0.15"], ["10%","0.1"], ["5%","0.05"], ["0%","0"]]), "percent");
    this.setOutput(true, null);
    this.setColour(200);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_26imi_megacar_startcharge'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("導航至[充電站]開始充電");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(200);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_27imi_megacar_track_func'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("循跡感測函式");
    this.appendStatementInput("msg")
        .setCheck(null);
    this.setColour(200);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_28imi_megacar_tracksensor'] = {
  init: function() {
    this.appendDummyInput()
        .appendField(new Blockly.FieldDropdown([["左邊","TRACK_LEFT"], ["前方","TRACK_FRONT"], ["後方","TRACK_BACK"], ["右邊","TRACK_RIGHT"]]), "direct");
    this.appendDummyInput()
        .appendField("循跡感測被觸發");
    this.setInputsInline(true);
    this.setOutput(true, null);
    this.setColour(200);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_29imi_megacar_stopfront'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("車子執行")
        .appendField(new Blockly.FieldDropdown([["結束此格","OPTIONNAME"]]), "NAME");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(200);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_30imi_megacar_direct'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("車子執行")
        .appendField(new Blockly.FieldDropdown([["對角右進","right"], ["對角左進","left"], ["前進","forward"]]), "direct");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(200);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_31imi_megacar_isfindpath'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("A*演算法有找到路徑");
    this.setOutput(true, null);
    this.setColour(200);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_32imi_megacar_gocar_func'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("開始自動駕駛函式");
    this.appendStatementInput("msg")
        .setCheck(null);
    this.setColour(200);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_33imi_megacar_aidetect'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("AI鏡頭開始識別行人、車子避障");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(200);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_34imi_megacar_trackforward'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("循跡感測器開始偵測");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(200);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['_35imi_megacar_esp32gps'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("[傳送]通知至ESP32：模擬GPS座標");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(200);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};