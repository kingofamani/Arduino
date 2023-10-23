#include <Wire.h>
#include <MCP23017.h>

#define MCP23017_ADDR 0x27
MCP23017 mcp = MCP23017(MCP23017_ADDR);

void setup() {
  Wire.begin();
  Serial.begin(115200);

  mcp.init();
  mcp.portMode(MCP23017Port::A, 0b11111111);  //Port A as output
  mcp.portMode(MCP23017Port::B, 0b11111111);  //Port B as input

  mcp.writeRegister(MCP23017Register::GPIO_A, 0x00);  //Reset port A
  mcp.writeRegister(MCP23017Register::GPIO_B, 0x00);  //Reset port B

  // GPIO_B reflects the same logic as the input pins state
  mcp.writeRegister(MCP23017Register::GPIO_A, 0x00);
  mcp.writeRegister(MCP23017Register::IPOL_B, 0x00);
  // Uncomment this line to invert inputs (press a button to lit a led)
  //mcp.writeRegister(MCP23017Register::IPOL_B, 0xFF);
}

void loop() {
  int currentA;+
  currentA = mcp.readPort(MCP23017Port::A);
  currentA += pow(2, 8);          //2^8，在8位進位最前最加第9位，避免第8個感測值0時變成7位數。
  Serial.println(currentA, BIN);  //BIN列印成2進位

  int currentB;
  currentB = mcp.readPort(MCP23017Port::B);
  currentB += pow(2, 8);          //2^8，在8位進位最前最加第9位，避免第8個感測值0時變成7位數。
  Serial.println(currentB, BIN);  //BIN列印成2進位

  // String strCurrentB = String(currentB, BIN);
  // for(int i=0;i<strCurrentB.length();i++){
  //   char currentChar = strCurrentB.charAt(i);
  //   Serial.println(currentChar);
  // }


  Serial.println("-");
  //mcp.writePort(MCP23017Port::A, currentB);
  delay(200);
}
