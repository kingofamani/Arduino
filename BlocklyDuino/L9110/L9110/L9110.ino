#define A_1A 8 // A_1A控制A馬達的前進（HIGH）、後退（LOW）
#define A_1B 9 // A_1B控制A馬達的速度 0~255 ，LOW表示停止
#define B_1A 10 // B_1A控制B馬達的前進（HIGH）、後退（LOW）
#define B_1B 11 // B_1B控制B馬達的速度 0~255，LOW表示停止

int A_Speed = 200; //設定前進速度
int B_Speed = 200; //設定前進速度

bool A_REVERSE = false;//A馬達前進,後退線路裝相反
bool B_REVERSE = true;//B馬達前進,後退線路裝相反
bool RIGHT_LEFT_REVERSE = false;//A,B馬達裝相反

bool A_Fo = HIGH == A_REVERSE;
bool A_Ba = LOW == A_REVERSE;
bool B_Fo = HIGH == B_REVERSE;
bool B_Ba = LOW == B_REVERSE;

int A_Fo_Speed =  (A_REVERSE ? (255 - A_Speed) : A_Speed); //設定A前進速度
int B_Fo_Speed = (B_REVERSE ? (255 - B_Speed) : B_Speed); //設定B前進速度
int A_Ba_Speed =  (A_REVERSE ? A_Speed : (255 - A_Speed)); //設定A後退速度
int B_Ba_Speed =  (B_REVERSE ? B_Speed : (255 - B_Speed) ); //設定B後退速度

void setup() {

  pinMode(A_1A, OUTPUT);
  pinMode(A_1B, OUTPUT);
  pinMode(B_1A, OUTPUT);
  pinMode(B_1B, OUTPUT);
  digitalWrite(A_1A, LOW);
  digitalWrite(A_1B, LOW);
  digitalWrite(B_1A, LOW);
  digitalWrite(B_1B, LOW);
}

//車子停止
void stopcar() {
  digitalWrite(A_1A, LOW);
  digitalWrite(A_1B, LOW);
  digitalWrite(B_1A, LOW);
  digitalWrite(B_1B, LOW);
}

//車子向前走
void forward() {
  digitalWrite(A_1A, A_Fo);
  analogWrite(A_1B, A_Fo_Speed);
  digitalWrite(B_1A, B_Fo);
  analogWrite(B_1B, B_Fo_Speed);
}

//車子向後走
void backward() {
  digitalWrite(A_1A, A_Ba);
  analogWrite(A_1B, A_Ba_Speed);
  digitalWrite(B_1A, B_Ba);
  analogWrite(B_1B, B_Ba_Speed);
}

//車子右轉
void turnRight() {
  if (RIGHT_LEFT_REVERSE) {
    digitalWrite(A_1A, LOW);
    analogWrite(A_1B, LOW);
    digitalWrite(B_1A, B_Fo);
    analogWrite(B_1B, B_Fo_Speed);
  } else {
    digitalWrite(A_1A, A_Fo);
    analogWrite(A_1B, A_Fo_Speed);
    digitalWrite(B_1A, LOW);
    analogWrite(B_1B, LOW);
  }
}

//車子左轉
void turnLeft() {
  if (RIGHT_LEFT_REVERSE) {
    digitalWrite(A_1A, A_Fo);
    analogWrite(A_1B, A_Fo_Speed);
    digitalWrite(B_1A, LOW);
    analogWrite(B_1B, LOW);
  } else {
    digitalWrite(A_1A, LOW);
    analogWrite(A_1B, LOW);
    digitalWrite(B_1A, B_Fo);
    analogWrite(B_1B, B_Fo_Speed);
  }
}

void loop() {
  forward();
  delay(1000);
  stopcar();
  delay(100);
  
  backward();
  delay(1000);
  stopcar();
  delay(100);

  turnRight();
  delay(500);
  stopcar();
  delay(100);
  
  turnLeft();
  delay(500);
  stopcar();
  delay(100);

//  stopcar();
//  delay(2000);
}
