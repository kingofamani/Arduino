Blockly.Arduino['amani_adafruitio_init'] = function(block) {
  var value_ssid = Blockly.Arduino.valueToCode(block, 'ssid', Blockly.Arduino.ORDER_ATOMIC) || '""';
  var value_wifipwd = Blockly.Arduino.valueToCode(block, 'wifipwd', Blockly.Arduino.ORDER_ATOMIC) || '""';
  var value_port = Blockly.Arduino.valueToCode(block, 'port', Blockly.Arduino.ORDER_ATOMIC) || '1883';
  var value_username = Blockly.Arduino.valueToCode(block, 'username', Blockly.Arduino.ORDER_ATOMIC) || '""';
  var value_iokey = Blockly.Arduino.valueToCode(block, 'iokey', Blockly.Arduino.ORDER_ATOMIC) || '""';

  // 定義區
  Blockly.Arduino.definitions_['include_adafruitio_wifi'] = '#include <AdafruitIO_WiFi.h>';
  Blockly.Arduino.definitions_['include_wifi'] = '#include <WiFi.h>';
  Blockly.Arduino.definitions_['define_io_username'] = `#define IO_USERNAME ${value_username}`;
  Blockly.Arduino.definitions_['define_io_key'] = `#define IO_KEY ${value_iokey}`;
  Blockly.Arduino.definitions_['define_wifi_ssid'] = `#define WIFI_SSID ${value_ssid}`;
  Blockly.Arduino.definitions_['define_wifi_pass'] = `#define WIFI_PASS ${value_wifipwd}`;
  Blockly.Arduino.definitions_['declare_adafruitio_wifi'] = 'AdafruitIO_WiFi adafruitio_io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);';

  // setup區
  Blockly.Arduino.setups_['serial_begin'] = 'Serial.begin(9600);';
  Blockly.Arduino.setups_['io_connect'] = 'adafruitio_io.connect();';
  Blockly.Arduino.setups_['io_wait_connection'] = `
  while (adafruitio_io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }`;

  // loop區
  Blockly.Arduino.loops_['io_run'] = 'adafruitio_io.run();';
  return '';
};
