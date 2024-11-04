
int spd = 255;               // 設定速度值0-255
int timer = 1000;           // 定義整數 timer

const int IN1 = 4;          //L298N IN1 pin 連接 Arduino pin 10
const int IN2 = 5;          //L298N IN2 pin 連接 Arduino pin 11
const int IN3 = 6;           //L298N IN3 pin 連接 Arduino pin 5
const int IN4 = 7;            //L298N IN4 pin 連接 Arduino pin 6

void setup()
{
  Serial.begin(9600);     //確認藍牙傳輸速率 9600 bits/second
  pinMode(IN1, OUTPUT);     // Arduino 輸出電壓控制車子
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  Stop();
  delay(500);
}

void loop() {            //主程式：車子前進1秒 (1000 ms)，後退1秒，左轉1秒，右轉1秒，停止1秒，如此再連續循環
  Forward ();
  delay(timer);
  Stop();
  delay(timer);
  
  Back();
  delay(timer);
  Stop();
  delay(timer);
  
  Left();
  delay(timer);
  Stop();
  delay(timer);
  
  Right();
  delay(timer);
  Stop();
  delay(5000);
}

void Forward()          //車子前進子程式
{
  analogWrite(IN1, spd);
  analogWrite(IN2, 0);
  analogWrite(IN3, 0);
  analogWrite(IN4, spd);
}

void Back()              //車子後退子程式
{
  analogWrite(IN1, 0);
  analogWrite(IN2, spd);
  analogWrite(IN3, spd);
  analogWrite(IN4, 0);
}

void Stop()              //車子停止子程式
{
  analogWrite(IN1, 0);
  analogWrite(IN2, 0);
  analogWrite(IN3, 0);
  analogWrite(IN4, 0);
}

void Left()              //車子左轉子程式
{
  analogWrite(IN1, spd);
  analogWrite(IN2, 0);
  analogWrite(IN3, spd);
  analogWrite(IN4, 0);
}

void Right()             //車子右轉子程式
{
  analogWrite(IN1, 0);
  analogWrite(IN2, spd);
  analogWrite(IN3, 0);
  analogWrite(IN4, spd);

}
