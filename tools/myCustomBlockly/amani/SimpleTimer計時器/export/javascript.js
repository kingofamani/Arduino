Blockly.Arduino['_01amani_simpletimer_setinteval'] = function(block) {
  var dropdown_order = block.getFieldValue('order');  
  var value_ms = Blockly.Arduino.valueToCode(block, 'ms', Blockly.Arduino.ORDER_ATOMIC);
  var statements_msg = Blockly.Arduino.statementToCode(block, 'msg');

  //定義區
  Blockly.Arduino.definitions_['_00amani_simpletimer'] =
`#include <SimpleTimer.h>
SimpleTimer timer;`;
  
  //loop區
  Blockly.Arduino.loops_['_00amani_simpletimer'] =   'timer.run();\n';  

  //每隔n秒觸發1次
  Blockly.Arduino.setups_['_01amani_simpletimer_setinteval'+dropdown_order] =   'timer.setInterval('+value_ms+', timerFunc'+dropdown_order+');\n';

  Blockly.Arduino.functions_['_01amani_simpletimer_setinteval'+dropdown_order] =   'void timerFunc'+dropdown_order+'(){\n ' + statements_msg + '  }\n ';
  
  
  var code = '';
  return code;
};

Blockly.Arduino['_02amani_simpletimer_setinteval_id'] = function(block) {
  
  var value_ms = Blockly.Arduino.valueToCode(block, 'ms', Blockly.Arduino.ORDER_ATOMIC);
  var dropdown_order = block.getFieldValue('order');  
  var statements_msg = Blockly.Arduino.statementToCode(block, 'msg');
  //計算總共拖曳幾個timer積木
  let intevalFunc = "intevalFunc"+dropdown_order;
  let intevalId = "inteval_ID"+dropdown_order;
  
  //定義區
  Blockly.Arduino.definitions_['_00amani_simpletimer'] =
`#include <SimpleTimer.h>
SimpleTimer timer;`;
  
  Blockly.Arduino.definitions_['_02amani_simpletimer_setinteval_id'+dropdown_order] =
`int ${intevalId} = 0;`;
  
  //loop區
  Blockly.Arduino.loops_['_00amani_simpletimer'] =
  `timer.run();`;
  

  //每隔n秒觸發1次，且可設定enable、disable
  Blockly.Arduino.setups_['_02amani_simpletimer_setinteval_id'+dropdown_order] =
`${intevalId} = timer.setInterval(${value_ms}, ${intevalFunc});
timer.disable(${intevalId});  
`;

  Blockly.Arduino.functions_['_02amani_simpletimer_setinteval_id'+dropdown_order] =   'void '+intevalFunc+'(){\n ' + statements_msg + '  }\n ';
  
  
  
  var code = '';
  return code;
};

Blockly.Arduino['_03amani_simpletimer_setinteval_enable'] = function(block) {
  var dropdown_order = block.getFieldValue('order');  
  var dropdown_switch = block.getFieldValue('switch');
  
  let intevalId = "inteval_ID"+dropdown_order;
  
  //loop區
  Blockly.Arduino.loops_['_00amani_simpletimer'] =
  `timer.run();`;
  
  var code = '';
  if(dropdown_switch=="enable"){
	code = 
`timer.enable(${intevalId});
`;
  }else if(dropdown_switch=="disable"){
	code = 
`timer.disable(${intevalId});
`;
  }  
  
  return code;
};

Blockly.Arduino['_04amani_simpletimer_settimeout'] = function(block) {
  
  var value_ms = Blockly.Arduino.valueToCode(block, 'ms', Blockly.Arduino.ORDER_ATOMIC);
  var dropdown_order = block.getFieldValue('order');  
  var statements_msg = Blockly.Arduino.statementToCode(block, 'msg');
  //計算總共拖曳幾個timer積木
  let func = "timeoutFunc"+dropdown_order;
  let intevalId = "timeout_ID"+dropdown_order;
  
  //定義區
  Blockly.Arduino.definitions_['_00amani_simpletimer'] =
`#include <SimpleTimer.h>
SimpleTimer timer;`;
  
  //loop區
  Blockly.Arduino.loops_['_00amani_simpletimer'] =
  `timer.run();`;
  

  //n秒後觸發1次，只有1次
  Blockly.Arduino.setups_['_04amani_simpletimer_settimeout'+dropdown_order] =
`timer.setTimeout(${value_ms}, ${func});`;

  Blockly.Arduino.functions_['_04amani_simpletimer_settimeout'+dropdown_order] =   'void '+func+'(){\n ' + statements_msg + '  }\n ';
    
  
  var code = '';
  return code;
};

Blockly.Arduino['_05amani_simpletimer_settimer'] = function(block) {
  
  var value_ms = Blockly.Arduino.valueToCode(block, 'ms', Blockly.Arduino.ORDER_ATOMIC);
  var value_times = Blockly.Arduino.valueToCode(block, 'times', Blockly.Arduino.ORDER_ATOMIC);
  var dropdown_order = block.getFieldValue('order');  
  var statements_msg = Blockly.Arduino.statementToCode(block, 'msg');
  //計算總共拖曳幾個timer積木
  let func = "setTimerFunc"+dropdown_order;
  
  //定義區
  Blockly.Arduino.definitions_['_00amani_simpletimer'] =
`#include <SimpleTimer.h>
SimpleTimer timer;`;
  
  //loop區
  Blockly.Arduino.loops_['_00amani_simpletimer'] =
  `timer.run();`;
  

  //n秒後觸發1次，只有1次
  Blockly.Arduino.setups_['_05amani_simpletimer_settimer'+dropdown_order] =
`timer.setTimer(${value_ms}, ${func}, ${value_times});`;

  Blockly.Arduino.functions_['_05amani_simpletimer_settimer'+dropdown_order] =   'void '+func+'(){\n ' + statements_msg + '  }\n ';
    
  
  var code = '';
  return code;
};