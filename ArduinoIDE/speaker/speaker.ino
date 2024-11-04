
//定義每一個音的頻率，例子："NOTE_C5 523"，C 是音符中的 DO，5 是高八度或低八度，523 是C5 頻率。
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
/*
更換音樂時，要修改的是：
程式 98-103 行，字串 melody[] 內，所有要演奏的音符，
程式 106-111 行，字串 noteDuration [] 內，相對應每一個音符的演奏拍數，
程式 116 行，”46”，要演奏音符的總數目。*/

// 字串 melody 內，含有所有要依序演奏的音符。0 表示休止符。
int melody[] = {                           
 NOTE_C6, NOTE_A5, NOTE_F5, 0, NOTE_C6, 0, NOTE_AS5, 0, NOTE_G5,
 0, 0, 0, NOTE_AS5, NOTE_G5, NOTE_E5, 0, NOTE_AS5, 0, NOTE_A5, 0, NOTE_F5, 
 0, 0, 0, 0, NOTE_CS5, NOTE_F5, NOTE_AS5, NOTE_A5, NOTE_C6, NOTE_F5, 
 0, 0, NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_F5, NOTE_G5, 0, 0, 0, 0
};

// 字串 noteDuration 內，標示每一個音符的演奏長度。4 為一拍，8 為半拍。
int noteDurations[] = {
  4, 8, 8, 8, 8, 8, 8, 8, 8, 
  4,4,4,4,8,8,8,8,8,8,8,8, 
  4, 4, 4, 4, 4, 4, 4, 4, 8, 8, 
  4, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 4, 4, 4
};

void setup() {
}
void loop() {
    for (int thisNote = 0; thisNote < 46; thisNote++) {         //用一個 for loop ，來連續演奏程式上面所定義的音符。46 為要演奏音符的總數目(含休止符)。
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);                    //喇叭＋極接 Arduino pin 8, melody[thisNote] 為要演奏的那個音符的頻率，noteDuration 為要演奏的那個音符的節拍數。
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(8);
  }
}
