#include <Wire.h>
#include <MCP23017.h>

#define MCP23017_ADDR 0x27
MCP23017 mcp = MCP23017(MCP23017_ADDR);

//16個磁簧開關狀態
int switchs[16];

void setup() {
  Wire.begin();
  Serial.begin(115200);

  mcp.init();
  mcp.portMode(MCP23017Port::A, 0b11111111);
  mcp.portMode(MCP23017Port::B, 0b11111111);

  mcp.writeRegister(MCP23017Register::GPIO_A, 0x00);
  mcp.writeRegister(MCP23017Register::GPIO_B, 0x00);

  mcp.writeRegister(MCP23017Register::GPIO_A, 0x00);
  mcp.writeRegister(MCP23017Register::IPOL_B, 0x00);
}

void loop() {
  int currentA;
  currentA = mcp.readPort(MCP23017Port::A);
  currentA += pow(2, 8);  //2^8，在8位進位最前最加第9位，避免第8個感測值0時變成7位數。
  //Serial.println(currentA, BIN);  //BIN列印成2進位

  int currentB;
  currentB = mcp.readPort(MCP23017Port::B);
  currentB += pow(2, 8);  //2^8，在8位進位最前最加第9位，避免第8個感測值0時變成7位數。
  //Serial.println(currentB, BIN);  //BIN列印成2進位

  int swCount = 0;

  String strCurrentA = String(currentA, BIN);
  for (int i = 0; i < strCurrentA.length(); i++) {
    if (i > 0) {//第0位(最左邊)是pow(2, 8)加上的，不能算
      char currentChar = strCurrentA.charAt(i);
      int num = String(currentChar).toInt();
      switchs[swCount++] = num;
      //Serial.print(switchs[swCount-1]);
    }
  }

  //Serial.print(",");

  String strCurrentB = String(currentB, BIN);
  for (int i = 0; i < strCurrentB.length(); i++) {
    if (i > 0) {
      char currentChar = strCurrentB.charAt(i);
      int num = String(currentChar).toInt();
      switchs[swCount++] = num;
      //Serial.print(switchs[swCount-1]);
    }
  }

  //印出二維陣列結果
  for(int i=0;i<16;i++){
    Serial.print(switchs[i]);
    if((i+1)%4==0){
      Serial.println("");
    }
  }


  Serial.println("-");
  //mcp.writePort(MCP23017Port::A, currentB);
  delay(200);
}
