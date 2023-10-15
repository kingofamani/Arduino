//車頭初始向右邊

//小烏龜移動矩陣
 char* matrix[3][3] = {
  {"-", "LF", "-"},
  {"RRF", "-", "F"},
  {"-", "RF", "-"}
};

const int pathCount=8;
//範例
//char pathDirect[pathCount]={'R','D','L','U'};//F,RF,RF,RF,
//char pathDirect[pathCount]={'U','L','D','R'};//LF,LF,LF,LF,
//char pathDirect[pathCount]={'R','R','D','L','L','D','R','R'};//F,F,RF,RF,F,LF,LF,F,
char pathDirect[pathCount]={'L','L','U','R','R','U','L','L'};//RRF,F,RF,RF,F,LF,LF,F,

char* pathTurtle[pathCount];

// 函数：旋转二维数组
void rotateMatrix(int degrees) {
   char* temp[3][3];
  
  // 顺时针旋转90度
  if (degrees == 90) {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        temp[i][j] = matrix[3 - 1 - j][i];
      }
    }
    // 旋转180度
  } else if (degrees == 180) {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        temp[i][j] = matrix[3 - 1 - i][3 - 1 - j];
      }
    }
    // 逆时针旋转90度
  } else if (degrees == 270) {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        temp[i][j] = matrix[j][3 - 1 - i];
      }
    }
  }

  // 更新原始数组
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix[i][j] = temp[i][j];
      //Serial.print(matrix[i][j]);
      //Serial.print(",");
    }
    //Serial.println("");
  }
}

void rotateMatrixByTurtle(char* turtle){
  if(turtle=="RF"){
    rotateMatrix(90);
  }else if(turtle=="RRF"){
    rotateMatrix(180);
  }else if(turtle=="LF"){
    rotateMatrix(270);
  }
}

char* directToTurtle(char direct){
  char* tur="";
  if(direct=='U'){
    tur=matrix[0][1];
  }else if(direct=='D'){
    tur=matrix[2][1];
  }else if(direct=='L'){
    tur=matrix[1][0];
  }else if(direct=='R'){
    tur=matrix[1][2];
  }
  return tur;
}

void setup() {
  Serial.begin(9600);
  //將上下左右方向轉成Turtle移動方向
  for(int i=0;i<pathCount;i++){
    pathTurtle[i]= directToTurtle(pathDirect[i]);
    rotateMatrixByTurtle(pathTurtle[i]);
  }

  for(int i=0;i<pathCount;i++){
    Serial.print(pathTurtle[i]);
    Serial.print(',');
  }
  
}

void loop() {
  // 选择旋转操作

  // 在这里可以添加打印数组的代码，以验证旋转操作
}
