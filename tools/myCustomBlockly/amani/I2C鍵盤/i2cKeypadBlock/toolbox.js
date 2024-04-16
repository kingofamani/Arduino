'use strict';

if (typeof toolbox_custom == 'undefined')
  var toolbox_custom = [];

toolbox_custom.push(''
+'  <category name="4x4鍵盤(I2C)" colour="#a55b80">'
+'    <block type="_01amani_i2ckeypad_init"></block>'
+'    <block type="_02amani_i2ckeypad_loop"></block>'
+'    <block type="_03amani_i2ckeypad_iskey"></block>'
+'    <block type="_04amani_i2ckeypad_key"></block>'
+'    <block type="_05amani_i2ckeypad_keynull"></block>'
+'    <block type="_06amani_i2ckeypad_funcnum"></block>'
+'	<block type="_07amani_i2ckeypad_isnum"></block>'
+'  </category>');