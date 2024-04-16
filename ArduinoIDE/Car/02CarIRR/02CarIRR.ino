#include <IRremote.h>

//紅外線
unsigned long button;
String direct = "";

#define POWER 0x10EFD827
#define A 0x10EFF807
#define B 0x10EF7887
#define C 0x10EF58A7
#define UP 0x10EFA05F
#define DOWN 0x10EF00FF
#define LEFT 0x10EF10EF
#define RIGHT 0x10EF807F
#define SELECT 0x10EF20DF
IRrecv irrecv11(11);
decode_results results11;

//馬達
const int In1 = 4;
const int In2 = 5;
const int In3 = 6;
const int In4 = 7;

void setup() {
  Serial.begin(9600);

  //開始IRR接收器
  irrecv11.enableIRIn();

  //馬達pin
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
}
void loop() {

  //偵測IRR按鈕
  IrrButtonIn();

  if (direct != "") {
    if (direct == "上") {
      mfront();
    } else if (direct == "下") {
      mback();
    } else if (direct == "左") {
      mleft();
    } else if (direct == "右") {
      mright();
    } else if (direct == "停") {
      mstop();
    }

    Serial.println(direct);
    if (direct == "停") {
      direct = "";
    }
  }
}
void mstop() {
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
}
void mfront() {
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
}
void mback() {
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
}

void mright() {
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
}
void mleft() {
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
}

unsigned long getDecodedValue(IRrecv receiver, decode_results results) {
  if (receiver.decode(&results)) {
    receiver.resume();
    return results.value;
  }
  return 0;
}

void IrrButtonIn() {
  button = (getDecodedValue(irrecv11, results11));
  if (button != 0) {
    if (button == 118964952 || button == 3090707456) {
      direct = "上";
    } else if (button == 2882120796  || button == 1558896004 ) {
      direct = "下";
    } else if (button == 143961768 || button == 3115704272) {
      direct = "左";
    } else if (button == 64453  || button == 3178714310) {
      direct = "右";
    } else if (button == 1185221640  || button == 4156964144 ) {
      direct = "停";
    }
  }
}
