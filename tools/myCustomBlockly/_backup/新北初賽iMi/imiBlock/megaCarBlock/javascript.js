Blockly.Arduino['_01imi_megacar_init'] = function(block) {
  var statements_uart = Blockly.Arduino.statementToCode(block, 'uart');
  var statements_track = Blockly.Arduino.statementToCode(block, 'track');
  var statements_trig = Blockly.Arduino.statementToCode(block, 'trig');
  var statements_carbox = Blockly.Arduino.statementToCode(block, 'carbox');
  var statements_aicam = Blockly.Arduino.statementToCode(block, 'aicam');
  var statements_sign = Blockly.Arduino.statementToCode(block, 'sign');
  var statements_l298n = Blockly.Arduino.statementToCode(block, 'l298n');
  var statements_l298n2 = Blockly.Arduino.statementToCode(block, 'l298n2');
  // TODO: Assemble javascript into code variable.
  Blockly.Arduino.definitions_['_01imi_megacar_init'] = '#include <Arduino.h>\n #include <SoftwareSerial.h>\n #include <Servo.h>\n #include "HUSKYLENS.h"\n #include <Wire.h>\n #include <Adafruit_INA219.h>\n //====插入變數Start====\n ' + statements_uart+statements_track+statements_trig+statements_carbox+statements_aicam+statements_sign+statements_l298n+statements_l298n2 + '//====插入變數End====\n //★★★車頭初始向下\n char CAR_INIT_DIRECT = \'D\';\n // 定義地圖大小\n const int numRows = 4;\n const int numCols = 6;\n //地圖陣列，0表示障礙物，1表示可通行\n int grid[numRows][numCols];\n //位置\n const char* GOODS_POINT = "goodsStation";\n const char* CHARGE_POINT = "chargeStation";\n const char* Recipient_POINT = "recipientHome";\n //目前位置\n String currentPoint = GOODS_POINT;\n //起點位置\n String startPoint = GOODS_POINT;\n int startRow = 0;\n int startCol = 0;\n //終點位置\n String endPoint = Recipient_POINT;\n int endRow = 3;\n int endCol = 5;\n //儲存座標結果\n String pathXY[numRows * numCols];\n //int pathXYCount = 0;\n //儲存地圖方向結果URDL\n char pathMapDirect[numRows * numCols];\n char MAP_DIRECT[4] = { \'U\', \'R\', \'D\', \'L\' };\n int pathCount = 0;\n //儲存車子(順時針)轉動角度\n int pathCarDegree[numRows * numCols];\n //儲存車子移動方向\n char* pathCarMove[numRows * numCols];\n char* CAR_MOVE[4] = { "F,", "R,F,", "R,R,F,", "L,F," };\n //與Esp32通訊\n const char* MAP_SET = "mapSet";\n const char* GOODS_LOAD = "goodsLoad";\n const char* LINE_NOTIFY = "lineNotify";\n const char* CAR_GPS = "carGps";\n //收貨人\n String recipient[6];\n //4way循跡感測器陣列\n int trackSensor[4];\n #define TRACK_LEFT 0\n #define TRACK_FRONT 1\n #define TRACK_BACK 2\n #define TRACK_RIGHT 3\n //是否走完一格\n bool isFrontArrive = false;\n Servo servoCarBox;\n Servo servoAiCam;\n //HsukyLens AI鏡頭\n HUSKYLENS huskylens;\n int readData[5] = {};\n byte dataType = 0;\n byte idCount = 0;\n bool detection_now = 0;\n int aiId = 0;\n int aiX = 0;  //中心點X座標\n int aiY = 0;  //中心點Y座標\n int aiWidth = 0;\n int aiHeight = 0;\n const int PERSON_ID = 1;                             //物體識別模式:人(透過AI鏡頭訓練)\n const int CAR_ID = 2;                                //物體識別模式:車子(透過AI鏡頭訓練)\n const int FACE_ID1 = 1;                              //人臉識別模式:車子(透過AI鏡頭訓練)\n char* CurrentAlgo = "ALGORITHM_OBJECT_RECOGNITION";  //目前的演算法\n //測電壓電流\n Adafruit_INA219 ina219;\n float busvoltage = 0;  //電池電壓\n float shuntvoltage = 0;\n float loadvoltage = 0;  //負載電壓\n float current_mA = 0;   //負載電流\n float power_mW = 0;     //負載功率\n //轉速(120~255)\n const int FSpeed = 120;\n const int BSpeed = 120;\n const int RSpeed = 120;\n const int LSpeed = 120;\n //轉動時間(毫秒)\n const int FTimer = 2000;\n const int BTimer = 1000;\n const int RTimer = 1000;\n const int LTimer = 1000;\n const int STimer = 3000;\n ';
  
  Blockly.Arduino.setups_['_01imi_megacar_init'] = '  Serial.begin(9600);\n  //UART\n  ESP32Serial.begin(9600);\n  //按鈕I/O\n  pinMode(BUTTON_SIGN_PIN, INPUT);\n  //伺服馬達初始\n  servoCarBox.attach(SERVO_CAR_BOX_PIN);\n  servoCarBox.write(ANGLE_CAR_BOX_CLOSE);\n  delay(1000);\n  servoAiCam.attach(SERVO_AI_CAM_PIN);\n  servoAiCam.write(ANGLE_AI_CAM_FRONT);\n  delay(1000);\n  //HuskyLens鏡頭初始化\n  Wire.begin();\n  while (!huskylens.begin(Wire)) {\n    Serial.println(F("Begin failed!"));\n    Serial.println(F("1.Please recheck the Protocol Type in HUSKYLENS (General Settings>>Protocol Type>>I2C)"));\n    Serial.println(F("2.Please recheck the connection."));\n    delay(100);\n  }\n  huskylens.writeAlgorithm(ALGORITHM_OBJECT_RECOGNITION);  //物體辨識模式\n  CurrentAlgo = "ALGORITHM_OBJECT_RECOGNITION";\n  //測電壓電流初始\n  if (!ina219.begin()) {\n    Serial.println("Failed to find INA219 chip");\n    while (1) { delay(10); }\n  }\n  //小車初始化\n  pinMode(L298N_IN1, OUTPUT);\n  pinMode(L298N_IN2, OUTPUT);\n  pinMode(L298N_IN3, OUTPUT);\n  pinMode(L298N_IN4, OUTPUT);\n  pinMode(L298N_IN5, OUTPUT);\n  pinMode(L298N_IN6, OUTPUT);\n  pinMode(L298N_IN7, OUTPUT);\n  pinMode(L298N_IN8, OUTPUT);\n  pinMode(L298N_EN1, OUTPUT);\n  pinMode(L298N_EN2, OUTPUT);\n  pinMode(L298N_EN3, OUTPUT);\n  pinMode(L298N_EN4, OUTPUT);\n  digitalWrite(L298N_IN1, LOW);\n  digitalWrite(L298N_IN2, LOW);\n  digitalWrite(L298N_IN3, LOW);\n  digitalWrite(L298N_IN4, LOW);\n  digitalWrite(L298N_IN5, LOW);\n  digitalWrite(L298N_IN6, LOW);\n  digitalWrite(L298N_IN7, LOW);\n  digitalWrite(L298N_IN8, LOW);\n  digitalWrite(L298N_EN1, LOW);\n  digitalWrite(L298N_EN2, LOW);\n  digitalWrite(L298N_EN3, LOW);\n  digitalWrite(L298N_EN4, LOW);\n  //循跡感測器初始化\n  pinMode(TRACK_LEFT_PIN, INPUT);\n  pinMode(TRACK_FRONT_PIN, INPUT);\n  pinMode(TRACK_BACK_PIN, INPUT);\n  pinMode(TRACK_RIGHT_PIN, INPUT);\n  stopCar();\n  delay(2000);\n';
  
  Blockly.Arduino.functions_['_01imi_megacar_init'] = 'void diagonalRight() {\n  digitalWrite(L298N_IN1, HIGH);\n  digitalWrite(L298N_IN2, LOW);\n  analogWrite(L298N_EN1, FSpeed);\n  digitalWrite(L298N_IN3, LOW);\n  digitalWrite(L298N_IN4, LOW);\n  analogWrite(L298N_EN2, FSpeed);\n  digitalWrite(L298N_IN5, LOW);\n  digitalWrite(L298N_IN6, LOW);\n  analogWrite(L298N_EN3, FSpeed);\n  digitalWrite(L298N_IN7, HIGH);\n  digitalWrite(L298N_IN8, LOW);\n  analogWrite(L298N_EN4, FSpeed);\n}\nvoid diagonalLeft() {\n  digitalWrite(L298N_IN1, LOW);\n  digitalWrite(L298N_IN2, LOW);\n  analogWrite(L298N_EN1, FSpeed);\n  digitalWrite(L298N_IN3, HIGH);\n  digitalWrite(L298N_IN4, LOW);\n  analogWrite(L298N_EN2, FSpeed);\n  digitalWrite(L298N_IN5, HIGH);\n  digitalWrite(L298N_IN6, LOW);\n  analogWrite(L298N_EN3, FSpeed);\n  digitalWrite(L298N_IN7, LOW);\n  digitalWrite(L298N_IN8, LOW);\n  analogWrite(L298N_EN4, FSpeed);\n}\nvoid forward() {\n  digitalWrite(L298N_IN1, HIGH);\n  digitalWrite(L298N_IN2, LOW);\n  analogWrite(L298N_EN1, FSpeed);\n  digitalWrite(L298N_IN3, HIGH);\n  digitalWrite(L298N_IN4, LOW);\n  analogWrite(L298N_EN2, FSpeed);\n  digitalWrite(L298N_IN5, HIGH);\n  digitalWrite(L298N_IN6, LOW);\n  analogWrite(L298N_EN3, FSpeed);\n  digitalWrite(L298N_IN7, HIGH);\n  digitalWrite(L298N_IN8, LOW);\n  analogWrite(L298N_EN4, FSpeed);\n}\nvoid backward() {\n  digitalWrite(L298N_IN1, LOW);\n  digitalWrite(L298N_IN2, HIGH);\n  analogWrite(L298N_EN1, BSpeed);\n  digitalWrite(L298N_IN3, LOW);\n  digitalWrite(L298N_IN4, HIGH);\n  analogWrite(L298N_EN2, BSpeed);\n  digitalWrite(L298N_IN5, LOW);\n  digitalWrite(L298N_IN6, HIGH);\n  analogWrite(L298N_EN3, BSpeed);\n  digitalWrite(L298N_IN7, LOW);\n  digitalWrite(L298N_IN8, HIGH);\n  analogWrite(L298N_EN4, BSpeed);\n}\nvoid turnRight() {\n  digitalWrite(L298N_IN1, HIGH);\n  digitalWrite(L298N_IN2, LOW);\n  analogWrite(L298N_EN1, RSpeed);\n  digitalWrite(L298N_IN3, HIGH);\n  digitalWrite(L298N_IN4, LOW);\n  analogWrite(L298N_EN2, RSpeed);\n  digitalWrite(L298N_IN5, LOW);\n  digitalWrite(L298N_IN6, HIGH);\n  analogWrite(L298N_EN3, RSpeed);\n  digitalWrite(L298N_IN7, LOW);\n  digitalWrite(L298N_IN8, HIGH);\n  analogWrite(L298N_EN4, RSpeed);\n}\nvoid turnLeft() {\n  digitalWrite(L298N_IN1, LOW);\n  digitalWrite(L298N_IN2, HIGH);\n  analogWrite(L298N_EN1, LSpeed);\n  digitalWrite(L298N_IN3, LOW);\n  digitalWrite(L298N_IN4, HIGH);\n  analogWrite(L298N_EN2, LSpeed);\n  digitalWrite(L298N_IN5, HIGH);\n  digitalWrite(L298N_IN6, LOW);\n  analogWrite(L298N_EN3, LSpeed);\n  digitalWrite(L298N_IN7, HIGH);\n  digitalWrite(L298N_IN8, LOW);\n  analogWrite(L298N_EN4, LSpeed);\n}\nvoid stopCar() {\n  digitalWrite(L298N_IN1, LOW);\n  digitalWrite(L298N_IN2, LOW);\n  analogWrite(L298N_EN1, FSpeed);\n  digitalWrite(L298N_IN3, LOW);\n  digitalWrite(L298N_IN4, LOW);\n  analogWrite(L298N_EN2, FSpeed);\n  digitalWrite(L298N_IN5, LOW);\n  digitalWrite(L298N_IN6, LOW);\n  analogWrite(L298N_EN3, FSpeed);\n  digitalWrite(L298N_IN7, LOW);\n  digitalWrite(L298N_IN8, LOW);\n  analogWrite(L298N_EN4, FSpeed);\n}\nvoid carHeadTurn(char targetDirect) {\n  //車頭轉向\n  int degree = mapDirectToCarDegree(CAR_INIT_DIRECT, targetDirect);\n  char* CAR_MOVE_NO_FRONT[4] = { "", "R", "RR", "L" };\n  int index = degree / 90;\n  if (CAR_MOVE_NO_FRONT[index] == "R") {\n    turnRight();\n    delay(RTimer);\n    stopCar();\n    delay(RTimer);\n    Serial.println("右轉,");\n  } else if (CAR_MOVE_NO_FRONT[index] == "RR") {\n    for (int i = 0; i < 2; i++) {\n      turnRight();\n      delay(RTimer);\n      stopCar();\n      delay(RTimer);\n      Serial.println("右轉,");\n    }\n  } else if (CAR_MOVE_NO_FRONT[index] == "L") {\n    turnLeft();\n    delay(LTimer);\n    stopCar();\n    delay(LTimer);\n    Serial.println("左轉,");\n  }\n  //紀錄車頭方向\n  CAR_INIT_DIRECT = targetDirect;\n}\n//取得循跡感測器值\nvoid getTracks() {\n  //格式：左前後右(ex:0101)\n  trackSensor[TRACK_LEFT] = digitalRead(TRACK_LEFT_PIN);\n  trackSensor[TRACK_FRONT] = digitalRead(TRACK_FRONT_PIN);\n  trackSensor[TRACK_BACK] = digitalRead(TRACK_BACK_PIN);\n  trackSensor[TRACK_RIGHT] = digitalRead(TRACK_RIGHT_PIN);\n}\nvoid AiDetect() {\n  bool isDetectPerson = false;\n  bool isDetectCar = false;\n  //直到沒有偵側到人or車才離開迴圈\n  do {\n    //開始AI識別物體\n    startDetectObject();\n    //在範圍內偵測到人,車才算\n    if ((aiX >= 100 && aiX <= 220) && (aiY >= 60 && aiY <= 180)) {\n      if (aiId == PERSON_ID) {\n        isDetectPerson = true;\n        Serial.println("人");\n      } else if (aiId == CAR_ID) {\n        isDetectCar = true;\n        Serial.println("車");\n      }\n    }\n    delay(500);\n  } while (isDetectPerson || isDetectCar);\n}\nvoid startDetectObject() {\n  if (!huskylens.request()) {\n    Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));\n  } else {\n    if (huskylens.available()) {\n      detection_now = true;\n      HUSKYLENSResult result = huskylens.read();\n      idCount = huskylens.countLearned();\n      if (result.command == COMMAND_RETURN_BLOCK) {\n        dataType = 0;\n        readData[0] = result.xCenter;\n        readData[1] = result.yCenter;\n        readData[2] = result.width;\n        readData[3] = result.height;\n        readData[4] = result.ID;\n      } else if (result.command == COMMAND_RETURN_ARROW) {\n        dataType = 1;\n        readData[0] = result.xOrigin;\n        readData[1] = result.yOrigin;\n        readData[2] = result.xTarget;\n        readData[3] = result.yTarget;\n        readData[4] = result.ID;\n      } else {\n        for (byte i = 0; i < 5; i++) {\n          readData[i] = 0;\n        }\n      }\n    } else {\n      detection_now = false;\n    }\n  }\n  if (detection_now) {\n    aiId = readData[4];\n    aiX = readData[0];\n    aiY = readData[1];\n    aiWidth = readData[2];\n    aiHeight = readData[3];\n    //id=0表示有辨識到物體，但該物體沒有被學習\n    if (aiId > 0) {\n      Serial.print(aiId);\n    }\n  } else {\n    aiId = 0;\n    aiX = 0;\n    aiY = 0;\n    aiWidth = 0;\n    aiHeight = 0;\n  }\n}\nint mapDirectToIndex(char direct) {\n  for (int i = 0; i < 4; i++) {\n    if (MAP_DIRECT[i] == direct) {\n      return i;\n    };\n  }\n  return 0;\n}\nchar* carDegreeToMove(int degree) {\n  int index = degree / 90;\n  return CAR_MOVE[index];\n}\nint mapDirectToCarDegree(char firstDirect, char NextDirect) {\n  int firstIndex = mapDirectToIndex(firstDirect);\n  int NextIndex = mapDirectToIndex(NextDirect);\n  if (NextIndex < firstIndex) {\n    NextIndex += 4;\n  };\n  int degree = (NextIndex - firstIndex) * 90;\n  return degree;\n}\nvoid convertXyToCarMove() {\n  //反轉陣列(原本A*輸出結果相反)\n  reverseStringArray(pathXY, pathCount + 1);\n  reverseCharArray(pathMapDirect, pathCount + 1);\n  //將地圖方向URDL轉成順時針角度90°,180°,270°\n  for (int i = 0; i < pathCount + 1; i++) {\n    pathCarDegree[i] = mapDirectToCarDegree(pathMapDirect[i], pathMapDirect[i + 1]);\n  }\n  //將角度轉換成車子移動F,RF,RRF,LF\n  for (int i = 0; i < pathCount; i++) {\n    pathCarMove[i] = carDegreeToMove(pathCarDegree[i]);\n  }\n}\nvoid printAStarResult() {\n  //印出地圖座標\n  for (int i = 0; i < pathCount + 1; i++) {\n    Serial.print(pathXY[i]);\n    Serial.print("→");\n  }\n  Serial.println("");\n  //印出地圖上下左右方向\n  for (int i = 0; i < pathCount + 1; i++) {\n    Serial.print(pathMapDirect[i]);\n    Serial.print(\',\');\n  }\n  Serial.println("");\n  //印出角度\n  for (int i = 0; i < pathCount; i++) {\n    Serial.print(pathCarDegree[i]);\n    Serial.print(\',\');\n  }\n  Serial.println("");\n  //印出車子移動指令\n  for (int i = 0; i < pathCount; i++) {\n    Serial.print(pathCarMove[i]);\n  }\n  Serial.println("");\n}\nvoid reverseCharArray(char arr[], int length) {\n  int start = 0;\n  int end = length - 1;\n  while (start < end) {\n    // 交換陣列中的元素\n    char temp = arr[start];\n    arr[start] = arr[end];\n    arr[end] = temp;\n    // 移動指標以繼續反轉\n    start++;\n    end--;\n  }\n}\nvoid reverseStringArray(String arr[], int length) {\n  int start = 0;\n  int end = length - 1;\n  while (start < end) {\n    // 交換陣列中的元素\n    String temp = arr[start];\n    arr[start] = arr[end];\n    arr[end] = temp;\n    // 移動指標以繼續反轉\n    start++;\n    end--;\n  }\n}\n//設起訖點\nvoid setStartEndPoint(String start, String end) {\n  startPoint = start;\n  endPoint = end;\n  if (startPoint == GOODS_POINT) {\n    startRow = 0;\n    startCol = 0;\n  } else if (startPoint == CHARGE_POINT) {\n    startRow = 3;\n    startCol = 0;\n  } else if (startPoint == Recipient_POINT) {\n    startRow = 3;\n    startCol = 5;\n  }\n  if (endPoint == GOODS_POINT) {\n    endRow = 0;\n    endCol = 0;\n  } else if (endPoint == CHARGE_POINT) {\n    endRow = 3;\n    endCol = 0;\n  } else if (endPoint == Recipient_POINT) {\n    endRow = 3;\n    endCol = 5;\n  }\n}\nbool starAStarPlan(char* target) {\n  setStartEndPoint(currentPoint, target);                             //設起訖點\n  bool isFindPath = aStar(grid, startRow, startCol, endRow, endCol);  //A*演算\n  return isFindPath;\n}\nvoid starNav(bool isFindPath, char* target) {\n  if (isFindPath) {\n    Serial.println("找到路徑!");\n    //座標起點\n    pathXY[pathCount] = String(startRow) + "," + String(startCol);\n    //車頭初始方向\n    pathMapDirect[pathCount] = CAR_INIT_DIRECT;\n    //座標轉換成車子移動指令\n    convertXyToCarMove();\n    //印出結果\n    printAStarResult();\n    //開始移動實際車子(含雲端平台GPS模擬)\n    goCar();\n    //紀錄\n    CAR_INIT_DIRECT = pathMapDirect[pathCount];  //最後車頭方向,當成下次導航車頭起始方向\n    currentPoint = target;                       //目前車子位置\n  } else {\n    Serial.println("未找到路徑.");\n  }\n}\nvoid standByAiCam() {\n  //A鏡頭上\n  servoAiCam.write(ANGLE_AI_CAM_UP);\n  delay(1000);\n  //Hsukylens人臉識別模式\n  huskylens.writeAlgorithm(ALGORITHM_FACE_RECOGNITION);\n  CurrentAlgo = "ALGORITHM_FACE_RECOGNITION";\n}\nfloat getBusPowerPercent() {\n  const float minVolt = 6.3;  //以7.4v鋰電池為準\n  const float maxVolt = 8.2;  //以7.4v鋰電池為準\n  //測電壓電流\n  shuntvoltage = ina219.getShuntVoltage_mV();\n  busvoltage = ina219.getBusVoltage_V();\n  current_mA = ina219.getCurrent_mA();\n  power_mW = ina219.getPower_mW();\n  loadvoltage = busvoltage + (shuntvoltage / 1000);\n  return ((busvoltage - minVolt) / (maxVolt - minVolt));\n}\nvoid startCharge() {\n  //導航至充電站\n  bool isFindPath = starAStarPlan(CHARGE_POINT);\n  starNav(isFindPath, CHARGE_POINT);\n  //進充電站前，車子原地轉向，車頭要朝左L\n  carHeadTurn(\'L\');\n  //接著倒車進入充電站\n  backward();\n  delay(2000);  //倒車2秒\n  stopCar();\n  //充電中……\n  float percent = 0.0;\n  while (percent < 1) {  //100%\n    percent = getBusPowerPercent();\n    delay(10000);\n  }\n  //充電完成，車子往前開出充電站\n  forward();\n  delay(2000);  //往前2秒\n  stopCar();\n  //完成充電，導航回物流站\n  isFindPath = starAStarPlan(GOODS_POINT);\n  starNav(isFindPath, GOODS_POINT);\n}\n';

  var code = '';
  return code;
};

Blockly.Arduino['_02imi_megacar_init_uart'] = function(block) {
  var value_rx = Blockly.Arduino.valueToCode(block, 'rx', Blockly.Arduino.ORDER_ATOMIC);
  var value_tx = Blockly.Arduino.valueToCode(block, 'tx', Blockly.Arduino.ORDER_ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code ='//UART通訊(接收ESP32傳來的MQTT訊息)'+'\n '+'SoftwareSerial ESP32Serial('+value_rx+',' +value_tx+');'+'\n ';

  return code;
};

Blockly.Arduino['_03imi_megacar_init_track'] = function(block) {
  var value_left = Blockly.Arduino.valueToCode(block, 'left', Blockly.Arduino.ORDER_ATOMIC);
  var value_front = Blockly.Arduino.valueToCode(block, 'front', Blockly.Arduino.ORDER_ATOMIC);
  var value_back = Blockly.Arduino.valueToCode(block, 'back', Blockly.Arduino.ORDER_ATOMIC);
  var value_right = Blockly.Arduino.valueToCode(block, 'right', Blockly.Arduino.ORDER_ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code ='//4way循跡感測器腳位'+'\n '+'#define TRACK_LEFT_PIN ' +value_left   +'//左邊 id1'+'\n '+'#define TRACK_FRONT_PIN ' +value_front  +'//前面 id2'+'\n '+'#define TRACK_BACK_PIN ' +value_back   +'//後面 id3'+'\n '+'#define TRACK_RIGHT_PIN ' +value_right  +'//右邊 id4'+'\n ';

  return code;
};

Blockly.Arduino['_04imi_megacar_init_trig'] = function(block) {
  var value_trig = Blockly.Arduino.valueToCode(block, 'trig', Blockly.Arduino.ORDER_ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code ='//觸發到白線回傳0或1'+'\n '+'#define TRIGGLED ' +value_trig+'\n ';

  return code;
};

Blockly.Arduino['_05imi_megacar_init_carbox'] = function(block) {
  var value_carbox = Blockly.Arduino.valueToCode(block, 'carbox', Blockly.Arduino.ORDER_ATOMIC);
  var value_open = Blockly.Arduino.valueToCode(block, 'open', Blockly.Arduino.ORDER_ATOMIC);
  var value_close = Blockly.Arduino.valueToCode(block, 'close', Blockly.Arduino.ORDER_ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code ='//貨斗伺服馬達腳位,角度'+'\n '+'#define SERVO_CAR_BOX_PIN ' +value_carbox+'\n '+'#define ANGLE_CAR_BOX_OPEN ' +value_open + '//開啟貨斗'+'\n '+'#define ANGLE_CAR_BOX_CLOSE ' +value_close + '//關閉貨斗'+'\n ';

  return code;
};

Blockly.Arduino['_06imi_megacar_init_aicam'] = function(block) {
  var value_aicam = Blockly.Arduino.valueToCode(block, 'aicam', Blockly.Arduino.ORDER_ATOMIC);
  var value_front = Blockly.Arduino.valueToCode(block, 'front', Blockly.Arduino.ORDER_ATOMIC);
  var value_up = Blockly.Arduino.valueToCode(block, 'up', Blockly.Arduino.ORDER_ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code ='//AI鏡頭伺服馬達腳位,角度'+'\n '+'#define SERVO_AI_CAM_PIN ' +value_aicam+'\n '+'#define ANGLE_AI_CAM_FRONT ' +value_front  +'//鏡頭向前'+'\n '+'#define ANGLE_AI_CAM_UP ' +value_up     +'//鏡頭朝上'+'\n ';

  return code;
};

Blockly.Arduino['_07imi_megacar_init_sign'] = function(block) {
  var value_sign = Blockly.Arduino.valueToCode(block, 'sign', Blockly.Arduino.ORDER_ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code ='//簽收鈕'+'\n '+'#define BUTTON_SIGN_PIN ' +value_sign+'\n ';

  return code;
};

Blockly.Arduino['_08imi_megacar_init_l298n'] = function(block) {
  var value_in1 = Blockly.Arduino.valueToCode(block, 'in1', Blockly.Arduino.ORDER_ATOMIC);
  var value_in2 = Blockly.Arduino.valueToCode(block, 'in2', Blockly.Arduino.ORDER_ATOMIC);
  var value_in3 = Blockly.Arduino.valueToCode(block, 'in3', Blockly.Arduino.ORDER_ATOMIC);
  var value_in4 = Blockly.Arduino.valueToCode(block, 'in4', Blockly.Arduino.ORDER_ATOMIC);
  var value_in5 = Blockly.Arduino.valueToCode(block, 'in5', Blockly.Arduino.ORDER_ATOMIC);
  var value_in6 = Blockly.Arduino.valueToCode(block, 'in6', Blockly.Arduino.ORDER_ATOMIC);
  var value_in7 = Blockly.Arduino.valueToCode(block, 'in7', Blockly.Arduino.ORDER_ATOMIC);
  var value_in8 = Blockly.Arduino.valueToCode(block, 'in8', Blockly.Arduino.ORDER_ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code ='//L298N腳位'+'\n '+'#define L298N_IN1 ' +value_in1+'\n '+'#define L298N_IN2 ' +value_in2+'\n '+'#define L298N_IN3 ' +value_in3+'\n '+'#define L298N_IN4 ' +value_in4+'\n '+'#define L298N_IN5 ' +value_in5+'\n '+'#define L298N_IN6 ' +value_in6+'\n '+'#define L298N_IN7 ' +value_in7+'\n '+'#define L298N_IN8 ' +value_in8+'\n ';

  return code;
};

Blockly.Arduino['_09imi_megacar_init_l298n2'] = function(block) {
  var value_en1 = Blockly.Arduino.valueToCode(block, 'en1', Blockly.Arduino.ORDER_ATOMIC);
  var value_en2 = Blockly.Arduino.valueToCode(block, 'en2', Blockly.Arduino.ORDER_ATOMIC);
  var value_en3 = Blockly.Arduino.valueToCode(block, 'en3', Blockly.Arduino.ORDER_ATOMIC);
  var value_en4 = Blockly.Arduino.valueToCode(block, 'en4', Blockly.Arduino.ORDER_ATOMIC);
  // TODO: Assemble javascript into code variable.
  var code ='#define L298N_EN1 ' +value_en1+'\n '+'#define L298N_EN2 ' +value_en2+'\n '+'#define L298N_EN3 ' +value_en3+'\n '+'#define L298N_EN4 ' +value_en4+'\n ';

  return code;
};

Blockly.Arduino['_10imi_megacar_astar'] = function(block) {
  // TODO: Assemble javascript into code variable.
  Blockly.Arduino.functions_['_10imi_megacar_astar'] = '// ===========A*演算法 Start===========\n// 表示地圖上的節點的類別\nclass Node {\npublic:\n  int row;\n  int col;\n  int f;  // f = g + h，表示節點的總代價\n  int g;  // 從起點到當前節點的實際代價\n  int h;  // 從當前節點到目標節點的估算代價\n  Node* parent;\n  Node(int r, int c)\n    : row(r), col(c), f(0), g(0), h(0), parent(nullptr) {}\n  // 計算當前節點到目標節點的估算代價（這裡使用曼哈頓距離）\n  void calculateH(int targetRow, int targetCol) {\n    h = abs(targetRow - row) + abs(targetCol - col);\n  }\n};\nbool aStar(int grid[numRows][numCols], int startRow, int startCol, int endRow, int endCol) {\n  Node* openList[numRows * numCols];\n  Node* closedList[numRows * numCols];\n  int openListCount = 0;\n  int closedListCount = 0;\n  Node* startNode = new Node(startRow, startCol);\n  Node* endNode = new Node(endRow, endCol);\n  startNode->calculateH(endRow, endCol);\n  startNode->f = startNode->g + startNode->h;\n  openList[openListCount++] = startNode;\n  while (openListCount > 0) {\n    // 找到f值最小的節點\n    int minFIndex = 0;\n    for (int i = 1; i < openListCount; i++) {\n      if (openList[i]->f < openList[minFIndex]->f) {\n        minFIndex = i;\n      }\n    }\n    Node* currentNode = openList[minFIndex];\n    // 將當前節點移到關閉列表\n    for (int i = minFIndex; i < openListCount - 1; i++) {\n      openList[i] = openList[i + 1];\n    }\n    openListCount--;\n    closedList[closedListCount++] = currentNode;\n    // 如果當前節點是目標節點，找到路徑並返回\n    if (currentNode->row == endRow && currentNode->col == endCol) {\n      Node* current = currentNode;\n      while (current->parent != nullptr) {\n        pathXY[pathCount] = String(current->row) + "," + String(current->col);\n        int deltaX = current->col - current->parent->col;\n        int deltaY = current->row - current->parent->row;\n        if (deltaX == 1) {\n          pathMapDirect[pathCount++] = \'R\';\n        } else if (deltaX == -1) {\n          pathMapDirect[pathCount++] = \'L\';\n        } else if (deltaY == 1) {\n          pathMapDirect[pathCount++] = \'D\';\n        } else if (deltaY == -1) {\n          pathMapDirect[pathCount++] = \'U\';\n        }\n        current = current->parent;\n      }\n      return true;\n    }\n    // 獲取當前節點的相鄰節點\n    int neighbors[4][2] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };\n    for (int i = 0; i < 4; i++) {\n      int newRow = currentNode->row + neighbors[i][0];\n      int newCol = currentNode->col + neighbors[i][1];\n      // 檢查新節點是否在地圖範圍內\n      if (newRow >= 0 && newRow < numRows && newCol >= 0 && newCol < numCols) {\n        // 檢查新節點是否是障礙物\n        if (grid[newRow][newCol] == 0) {\n          continue;\n        }\n        Node* neighbor = new Node(newRow, newCol);\n        neighbor->calculateH(endRow, endCol);\n        neighbor->g = currentNode->g + 1;  // 假設每個步驟的代價都是1\n        neighbor->f = neighbor->g + neighbor->h;\n        neighbor->parent = currentNode;\n        // 檢查新節點是否在關閉列表中\n        bool inClosedList = false;\n        for (int j = 0; j < closedListCount; j++) {\n          if (closedList[j]->row == neighbor->row && closedList[j]->col == neighbor->col) {\n            inClosedList = true;\n            break;\n          }\n        }\n        if (inClosedList) {\n          delete neighbor;\n          continue;\n        }\n        // 檢查新節點是否已經在開放列表中\n        bool inOpenList = false;\n        for (int j = 0; j < openListCount; j++) {\n          if (openList[j]->row == neighbor->row && openList[j]->col == neighbor->col) {\n            inOpenList = true;\n            if (neighbor->g < openList[j]->g) {\n              openList[j]->g = neighbor->g;\n              openList[j]->f = neighbor->f;\n              openList[j]->parent = neighbor->parent;\n            }\n            delete neighbor;\n            break;\n          }\n        }\n        if (!inOpenList) {\n          openList[openListCount++] = neighbor;\n        }\n      }\n    }\n  }\n  // 如果開放列表為空，表示沒有找到路徑\n  return false;\n}\n// ===========A*演算法 End===========\n';

  var code = '';
  return code;
};

Blockly.Arduino['_11imi_megacar_esp32'] = function(block) {
  var statements_msg = Blockly.Arduino.statementToCode(block, 'msg');
  // TODO: Assemble javascript into code variable.
  var code ='//接收訊息：ESP32→Mega\n   while (ESP32Serial.available()) {\n     String str = ESP32Serial.readString();\n     Serial.println(str);\n ' + statements_msg + '}//end while\n ';

  return code;
};

Blockly.Arduino['_12imi_megacar_isesp32msg'] = function(block) {
  var dropdown_msg = block.getFieldValue('msg');
  // TODO: Assemble javascript into code variable.
  var code ='str.indexOf('+dropdown_msg+') != -1';

  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.Arduino.ORDER_NONE];
};

Blockly.Arduino['_13imi_megacar_servo'] = function(block) {
  var dropdown_servo = block.getFieldValue('servo');
  var dropdown_angle = block.getFieldValue('angle');
  // TODO: Assemble javascript into code variable.
  var code =''+      dropdown_servo+'.write('+dropdown_angle+');'+'      delay(1000);\n';

  return code;
};

Blockly.Arduino['_14imi_megacar_savemap'] = function(block) {
  // TODO: Assemble javascript into code variable.
  var code ='//儲存地圖陣列(格式:MAP_SET,4x6地圖陣列)\n       String tmpArray[25];\n       char* token = strtok((char*)str.c_str(), ",");\n       int tokenLen = 0;\n       while (token != NULL && tokenLen < 25) {\n         tmpArray[tokenLen] = token;\n         token = strtok(NULL, ",");\n         tokenLen++;\n       }\n       int count = 1;  //第0個MAP_SET不用放入\n       for (int i = 0; i < 4; i++) {\n         for (int j = 0; j < 6; j++) {\n           grid[i][j] = tmpArray[count++].toInt();\n         }\n       }\n ';

  return code;
};

Blockly.Arduino['_15imi_megacar_savereci'] = function(block) {
  // TODO: Assemble javascript into code variable.
  var code ='//儲存收件人陣列(格式:goodsLoad,姓名,商品,倉庫X,倉庫Y,收件人X,收件人Y)\n       String tmpArray[7];\n       char* token = strtok((char*)str.c_str(), ",");\n       int tokenLen = 0;\n       while (token != NULL && tokenLen < 7) {\n         tmpArray[tokenLen] = token;\n         token = strtok(NULL, ",");\n         tokenLen++;\n       }\n       //第0個goodsLoad不用放入\n       int count = 0;\n       for (int i = 1; i < 7; i++) {\n         recipient[count++] = tmpArray[i];\n       }\n ';

  return code;
};

Blockly.Arduino['_16imi_megacar_startastar'] = function(block) {
  var dropdown_point = block.getFieldValue('point');
  // TODO: Assemble javascript into code variable.
  var code ='//A*路徑歸劃\n'+      'bool isFindPath = starAStarPlan('+dropdown_point+');'+'      //開始導航\n'+      'starNav(isFindPath,' +dropdown_point+');';

  return code;
};

Blockly.Arduino['_17imi_megacar_standbyaicam'] = function(block) {
  // TODO: Assemble javascript into code variable.
  var code ='//抵達目的地,AI鏡頭朝向,準備人臉識別收貨人\n       if (isFindPath) {\n         standByAiCam();\n       }\n ';

  return code;
};

Blockly.Arduino['_18imi_megacar_esp32line'] = function(block) {
  // TODO: Assemble javascript into code variable.
  var code ='//完成送貨，發送LINE通知收貨人(格式:LINE_NOTIFY,姓名,商品)\n       if (isFindPath) {\n         ESP32Serial.print(String(LINE_NOTIFY) + "," + recipient[0] + recipient[1]);\n       }\n ';

  return code;
};

Blockly.Arduino['_19imi_megacar_startdetectobject'] = function(block) {
  var statements_msg = Blockly.Arduino.statementToCode(block, 'msg');
  // TODO: Assemble javascript into code variable.
  var code ='//等待AI人臉識別\n   if (CurrentAlgo == "ALGORITHM_FACE_RECOGNITION") {\n     //開始AI人臉識別\n     startDetectObject();\n ' + statements_msg + '  }\n ';

  return code;
};

Blockly.Arduino['_20imi_megacar_isfaceid'] = function(block) {
  var dropdown_id = block.getFieldValue('id');
  // TODO: Assemble javascript into code variable.
  var code ='aiId == FACE_ID1';

  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.Arduino.ORDER_NONE];
};

Blockly.Arduino['_21imi_megacar_currentalgo'] = function(block) {
  var dropdown_algo = block.getFieldValue('algo');
  // TODO: Assemble javascript into code variable.
  var code ='currentAlgo ="'+ dropdown_algo+'";';

  return code;
};

Blockly.Arduino['_22imi_megacar_issign'] = function(block) {
  // TODO: Assemble javascript into code variable.
  var code ='digitalRead(BUTTON_SIGN_PIN) == 1';

  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.Arduino.ORDER_NONE];
};

Blockly.Arduino['_23imi_megacar_carheadturn'] = function(block) {
  var dropdown_direct = block.getFieldValue('direct');
  // TODO: Assemble javascript into code variable.
  var code ='//抵達物流站，車子原地轉向(車頭要朝下D，否則貨斗開啟方向會卡住)'+'\n '+    'carHeadTurn('+dropdown_direct+');'+'\n ';

  return code;
};

Blockly.Arduino['_24imi_megacar_getpower'] = function(block) {
  // TODO: Assemble javascript into code variable.
  var code ='float percent = getBusPowerPercent();  //取得電池當前電壓百分比(小數)\n';

  return code;
};

Blockly.Arduino['_25imi_megacar_islowpower'] = function(block) {
  var dropdown_percent = block.getFieldValue('percent');
  // TODO: Assemble javascript into code variable.
  var code ='currentPoint == GOODS_POINT && percent <=' +dropdown_percent;

  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.Arduino.ORDER_NONE];
};

Blockly.Arduino['_26imi_megacar_startcharge'] = function(block) {
  // TODO: Assemble javascript into code variable.
  var code ='startCharge();\n';

  return code;
};

Blockly.Arduino['_27imi_megacar_track_func'] = function(block) {
  var statements_msg = Blockly.Arduino.statementToCode(block, 'msg');
  // TODO: Assemble javascript into code variable.
  Blockly.Arduino.functions_['_27imi_megacar_track_func'] = 'void trackForward() {\n   //先往前300ms,越過前方白線\n   forward();\n   delay(300);\n   //開始前進,直循跡感測踫到前方白線\n   while (!isFrontArrive) {\n     //取得循跡感測值\n     getTracks();\n ' + statements_msg + '  }  //end while\n }//end trackForward\n ';

  var code = '';
  return code;
};

Blockly.Arduino['_28imi_megacar_tracksensor'] = function(block) {
  var dropdown_direct = block.getFieldValue('direct');
  // TODO: Assemble javascript into code variable.
  var code ='trackSensor['+dropdown_direct+'] == TRIGGLED';

  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.Arduino.ORDER_NONE];
};

Blockly.Arduino['_29imi_megacar_stopfront'] = function(block) {
  var dropdown_name = block.getFieldValue('NAME');
  // TODO: Assemble javascript into code variable.
  var code ='      backward();\n       delay(50);\n       stopCar();\n       //結束此格行走\n       isFrontArrive = true;\n       break;\n ';

  return code;
};

Blockly.Arduino['_30imi_megacar_direct'] = function(block) {
  var dropdown_direct = block.getFieldValue('direct');
  // TODO: Assemble javascript into code variable.
  var code ="";
	if(dropdown_direct=="right"){
	  code = "diagonalRight();";
	}else if(dropdown_direct=="left"){
	  code = "diagonalLeft();";
	}else if(dropdown_direct=="forward"){
	  code = "forward();";
	}

  return code;
};

Blockly.Arduino['_31imi_megacar_isfindpath'] = function(block) {
  // TODO: Assemble javascript into code variable.
  var code ='isFindPath';

  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.Arduino.ORDER_NONE];
};

Blockly.Arduino['_32imi_megacar_gocar_func'] = function(block) {
  var statements_msg = Blockly.Arduino.statementToCode(block, 'msg');
  // TODO: Assemble javascript into code variable.
  Blockly.Arduino.functions_['_32imi_megacar_gocar_func'] = 'void goCar() {\n   //1.先將移動指令轉成字串\n   String stringPathCarMotor = "";\n   for (int i = 0; i < pathCount; i++) {\n     stringPathCarMotor += pathCarMove[i];\n   }\n   //2.字串轉成陣列\n   //使用 strtok() 函数分割字符串\n   int cacheLength = 200;  //太小會裝不下\n   String pathCarMotor[cacheLength];\n   char* token = strtok((char*)stringPathCarMotor.c_str(), ",");\n   int tokenLen = 0;\n   //字串轉成陣列\n   while (token != NULL && tokenLen < cacheLength) {\n     pathCarMotor[tokenLen] = token;\n     token = strtok(NULL, ",");\n     tokenLen++;\n   }\n   //3.開始移動車子\n   int countPathXY = 1;\n   for (int i = 0; i < tokenLen; i++) { \n     if (pathCarMotor[i] == "F") {\n       //AI識別行人,車子\n       //循跡感測\n       //雲端平台模擬GPS\n ' + statements_msg + '      isFrontArrive = false;\n       delay(FTimer);\n       Serial.println("前,"); \n     } else if (pathCarMotor[i] == "R") {\n       turnRight();\n       delay(RTimer);\n       stopCar();\n       delay(RTimer);\n       Serial.println("右轉,");\n     } else if (pathCarMotor[i] == "L") {\n       turnLeft();\n       delay(LTimer);\n       stopCar();\n       delay(LTimer);\n       Serial.println("左轉,");\n     }\n   }//end for\n }//end goCar\n ';


  var code = '';
  return code;
};

Blockly.Arduino['_33imi_megacar_aidetect'] = function(block) {
  // TODO: Assemble javascript into code variable.
  var code ='AiDetect();';

  return code;
};

Blockly.Arduino['_34imi_megacar_trackforward'] = function(block) {
  // TODO: Assemble javascript into code variable.
  var code ='trackForward();';

  return code;
};

Blockly.Arduino['_35imi_megacar_esp32gps'] = function(block) {
  // TODO: Assemble javascript into code variable.
  var code ='ESP32Serial.print(String(CAR_GPS) + "," + pathXY[countPathXY++]);';

  return code;
};