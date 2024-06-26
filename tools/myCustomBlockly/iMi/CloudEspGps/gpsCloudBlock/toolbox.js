'use strict';

if (typeof toolbox_custom == 'undefined')
  var toolbox_custom = [];

toolbox_custom.push(''
+'  <category name="雲端GPS" colour="#5b67a5">'
+'    <block type="_01imi_gpscloud_init">'
+'      <statement name="uart">'
+'        <block type="_02imi_gpscloud_uart">'
+'          <value name="rx">'
+'            <block type="math_number">'
+'              <field name="NUM">0</field>'
+'            </block>'
+'          </value>'
+'          <value name="tx">'
+'            <block type="math_number">'
+'              <field name="NUM">0</field>'
+'            </block>'
+'          </value>'
+'        </block>'
+'      </statement>'
+'    </block>'
+'    <block type="_03imi_gpscloud_setup"></block>'
+'    <block type="_04imi_gpscloud_loop"></block>'
+'    <block type="_05imi_gpscloud_getesp32xy"></block>'
+'    <block type="_06imi_gpscloud_googlemap"></block>'
+'  </category>');