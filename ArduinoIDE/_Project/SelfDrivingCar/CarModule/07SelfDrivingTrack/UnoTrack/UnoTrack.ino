/***
循跡感測器
左邊 id1 腳位4
前面 id2 腳位5
後面 id4 腳位6
右邊 id4 腳位7
***/
#define TRACK_LEFT_PIN 4
#define TRACK_FRONT_PIN 5
#define TRACK_BACK_PIN 6
#define TRACKRIGHT_PIN 7

void setup() {
  Serial.begin(9600);

  pinMode(TRACK_LEFT_PIN, INPUT);
  pinMode(TRACK_FRONT_PIN, INPUT);
  pinMode(TRACK_BACK_PIN, INPUT);
  pinMode(TRACKRIGHT_PIN, INPUT);
}
void loop() {
  //左前後右
  String msg = 
    String(digitalRead(4)) +
    String(digitalRead(5)) +
    String(digitalRead(6)) +
    String(digitalRead(7));
  Serial.println(msg);
  delay(200);
}
