'use strict';

if (typeof toolbox_custom == 'undefined')
  var toolbox_custom = [];

toolbox_custom.push(''
+'<category id="category_custom" name="%{BKY_MYBLOCKS}" colour="%{BKY_MYBLOCKS_HUE}">'
+'<block type="_01amani_uart_init">'
+'	<value name="rx">'
+'	  <block type="math_number">'
+'		<field name="NUM">16</field>'
+'	  </block>'
+'	</value>'
+'	<value name="tx">'
+'	  <block type="math_number">'
+'		<field name="NUM">17</field>'
+'	  </block>'
+'	</value> 		  '
+'	<field name="baudrate">9600</field>'
+'	<statement name="statement"></statement>'
+'</block>'
+''
+'<block type="_02amani_uart_get"></block>'
+''
+'<block type="_03amani_uart_send">'
+'	<field name="serial">Serial</field>'
+'	<field name="send">傳送資料(print)</field>'
+'	<value name="msg">'
+'		<shadow type="text">'
+'			<field name="TEXT"></field>'
+'		</shadow>'
+'	</value>'
+'</block>'
+'</category>');