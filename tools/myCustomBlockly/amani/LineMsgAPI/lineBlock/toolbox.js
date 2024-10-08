'use strict';

if (typeof toolbox_custom == 'undefined')
  var toolbox_custom = [];

toolbox_custom.push(''
+'<category id="category_custom" name="test" >'
+'  <block type="_01amani_linepushapi_init">'
+'    <value name="userid">'
+'      <block type="text">'
+'        <field name="TEXT"></field>'
+'      </block>'
+'    </value>'
+'    <value name="token">'
+'      <block type="text">'
+'        <field name="TEXT"></field>'
+'      </block>'
+'    </value>'
+'  </block>'
+'  <block type="_02amani_linepushapi_msg">'
+'    <value name="msg">'
+'      <block type="text">'
+'        <field name="TEXT"></field>'
+'      </block>'
+'    </value>'
+'  </block>'
+'</category>');