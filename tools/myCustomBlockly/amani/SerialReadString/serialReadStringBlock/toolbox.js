'use strict';

if (typeof toolbox_custom == 'undefined')
  var toolbox_custom = [];

toolbox_custom.push(''
+'<category id="category_custom" name="%{BKY_MYBLOCKS}" colour="%{BKY_MYBLOCKS_HUE}">'
+'	  <block type="_01amani_serial_avail">'
+'    <field name="serial">Serial</field>'
+'  </block>'
+'  <block type="_02amani_serial_readstring">'
+'    <field name="serial">Serial</field>'
+'  </block>'
+'</category>');