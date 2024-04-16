#include <Ultrasonic.h>
#include <DFRobot_DF1201S.h>
#include <SoftwareSerial.h>

//超音波
Ultrasonic ultrasonicUp(10, 11);
Ultrasonic ultrasonicDown(12, 13);
int distanceUp;
int distancDown;
int disUpCount;
int disDownCount;
boolean isSetUp;
boolean isSetDown;

//MP3播放器
SoftwareSerial DF1201SSerial(2, 3);  //RX  TX
DFRobot_DF1201S DF1201S;

//燈號
int UpLightPin = 4;
int DownLightPin = 5;
int CrossLightPin = 6;
//按鈕
int BtnStartPin = 7;//重開始鈕
int BtnVolPin = 8;//聲音鈕
int volLoop = 0;//音量循環

//下一步
String NEXT_STEP = "UP";//UP,DOWN

//03穿梭子mp3只播一次
boolean isCrossPlayed = false;


void setup() {
  Serial.begin(115200);

  //初始MP3播放器
  DF1201SSerial.begin(115200);
  while (!DF1201S.begin(DF1201SSerial)) {
    Serial.println("Init failed, please check the wire connection!");
    delay(1000);
  }
  DF1201S.setVol(30);/*max val 30*/
  DF1201S.switchFunction(DF1201S.MUSIC);
  delay(100);

  //燈號
  pinMode(UpLightPin, OUTPUT);
  pinMode(DownLightPin, OUTPUT);
  pinMode(CrossLightPin, OUTPUT);
  pinMode(BtnStartPin, INPUT);
  pinMode(BtnVolPin, INPUT);

  //白色這款RGB LED燈的HIGH(關)、LOW(開)相反
  digitalWrite(UpLightPin, HIGH);
  digitalWrite(DownLightPin, HIGH);
  digitalWrite(CrossLightPin, HIGH);

  DF1201S.playSpecFile("/04.mp3");//04檢查編織板有沒有放在下面。預備。開始。
  delay(4000);

}

void loop() {
  //重置鈕
  if(digitalRead(BtnStartPin)){
    NEXT_STEP = "UP";
    digitalWrite(UpLightPin, HIGH);
    digitalWrite(DownLightPin, HIGH);
    digitalWrite(CrossLightPin, HIGH);

    isCrossPlayed = false;
    
    DF1201S.playSpecFile("/04.mp3");//04檢查編織板有沒有放在下面。預備。開始。
    delay(4000);
  }

  //音量鈕
  if(digitalRead(BtnVolPin)){
    DF1201S.setVol((volLoop%4)*10);
    volLoop++;
  }
  
  //開始MP3播放器
  DF1201S.start();

  //測量是否穩定在距離內
  judgeSetUpDown();

  if (isSetUp && !isSetDown) {
    Serial.println("Up扣住");
    
    digitalWrite(UpLightPin, HIGH);
    digitalWrite(DownLightPin, HIGH);
    digitalWrite(CrossLightPin, LOW);
    
    NEXT_STEP = "DOWN";

    if(!isCrossPlayed){
      isCrossPlayed = true;
      DF1201S.playSpecFile("/03.mp3");//03請將梭子穿過經線
      delay(2000); 
    }       

  } else if (isSetUp && isSetDown) {
    Serial.println("Down扣住");
    
    digitalWrite(UpLightPin, HIGH);
    digitalWrite(DownLightPin, HIGH);
    digitalWrite(CrossLightPin, LOW);

    NEXT_STEP = "UP";
    
    if(!isCrossPlayed){
      isCrossPlayed = true;
      DF1201S.playSpecFile("/03.mp3");//03請將梭子穿過經線
      delay(2000); 
    }  

  } else if (!isSetUp && !isSetDown) {
    Serial.println("拿起支架中");

    isCrossPlayed = false;
    
    if(NEXT_STEP == "UP"){
      digitalWrite(UpLightPin, LOW);
      digitalWrite(DownLightPin, HIGH);
      digitalWrite(CrossLightPin, HIGH);
      
      DF1201S.playSpecFile("/01.mp3");//01請將編織板放在上面
    }else if(NEXT_STEP == "DOWN"){
      digitalWrite(UpLightPin, HIGH);
      digitalWrite(DownLightPin, LOW);
      digitalWrite(CrossLightPin, HIGH);
      
      DF1201S.playSpecFile("/02.mp3");//02請將編織板放在下面
    }    
    delay(2000);

  }

}

void judgeSetUpDown() {
  disUpCount = 0;
  disDownCount = 0;

  for (int i = 0; i < 10; i++) {
    distanceUp = ultrasonicUp.read();
    distancDown = ultrasonicDown.read();

    if (distanceUp <= 5) {
      disUpCount++;
    }
    if (distancDown <= 5) {
      disDownCount++;
    }
    delay(50);
  }

  Serial.print("Up: ");
  Serial.println(disUpCount);
  Serial.print("Down: ");
  Serial.println(disDownCount);

  isSetUp = (disUpCount >= 8); //10次有8次ok就可以
  isSetDown = (disDownCount >= 8);
}
