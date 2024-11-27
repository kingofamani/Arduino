Blockly.Blocks['amani_adafruitio_init'] = {
    init: function () {
        this.appendDummyInput()
            .appendField("連線到 MQTT");
        this.appendValueInput("ssid")
            .setCheck("String")
            .appendField("WIFI ID");
        this.appendValueInput("wifipwd")
            .setCheck("String")
            .appendField("WIFI 密碼");
        this.appendValueInput("port")
            .setCheck("Number")
            .appendField("連接埠");
        this.appendValueInput("username")
            .setCheck("String")
            .appendField("使用者名稱");
        this.appendValueInput("iokey")
            .setCheck("String")
            .appendField("IO_KEY");
        this.setColour(15); // 設定顏色
        this.setPreviousStatement(true, null); // 允許積木上接
        this.setNextStatement(true, null); // 允許積木下接
        this.setTooltip(""); // 提示文字
        this.setHelpUrl(""); // 說明文件網址
    }
};
