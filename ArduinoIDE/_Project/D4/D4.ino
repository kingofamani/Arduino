//Generated Date: Mon, 30 Oct 2023 23:58:24 GMT

#include "HUSKYLENS.h"

HUSKYLENS huskylens;
int readData[5] = {};
byte dataType = 0;
byte idCount = 0;
bool detection_now = 0;

void playBuzzer(int pin, String frequency, String delaytime) {
  String f="",d="",split=",";
  int s1=0;
  frequency+=",";
  delaytime+=",";
  for (int i=0;i<frequency.length();i++) {
    if (frequency[i]==split[0]) {
  	   f=frequency.substring(s1,i);
  	   s1=i+1;
  	   for (int j=0;j<delaytime.length();j++) {
  	      if (delaytime[j]==split[0]) {
  		    d=delaytime.substring(0,j);
  		    tone(pin, f.toInt(), d.toInt());
  		    delay(d.toInt());
  		    delaytime=delaytime.substring(j+1);
  		    break;
  	      }
  	    }
    }
  }
}

void beep(int id) {
  //1:25%、2:50%、3:75%、4:滿血
  if (id == 1) {
    playBuzzer(3, "988", "100");
  } else if (id == 2) {
    playBuzzer(3, "587", "100");
  } else if (id == 3) {
    playBuzzer(3, "261", "100");
  }
}

void setup()
{
  Serial.begin(9600);

  Wire.begin();
  while (!huskylens.begin(Wire)) {
    Serial.println(F("Begin failed!"));
    Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>I2C)"));
    Serial.println(F("2.Please recheck the connection."));
    delay(100);
  }

  huskylens.writeAlgorithm(ALGORITHM_OBJECT_CLASSIFICATION);
}

void loop()
{
  if (!huskylens.request()) {
    Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
  }
  else {
    if (huskylens.available()) {
      detection_now = true;
      HUSKYLENSResult result = huskylens.read();
      idCount = huskylens.countLearned();
      if (result.command == COMMAND_RETURN_BLOCK){
        dataType = 0;
        readData[0] = result.xCenter;
        readData[1] = result.yCenter;
        readData[2] = result.width;
        readData[3] = result.height;
        readData[4] = result.ID;
      }
      else if (result.command == COMMAND_RETURN_ARROW){
        dataType = 1;
        readData[0] = result.xOrigin;
        readData[1] = result.yOrigin;
        readData[2] = result.xTarget;
        readData[3] = result.yTarget;
        readData[4] = result.ID;
      }
      else {
        for (byte i=0; i<5; i++) {
          readData[i] = 0;
        }
      }
    }
    else {
      detection_now = false;
    }
  }
  if (detection_now) {
    if (readData[4] > 0) {
      beep(readData[4]);
    } else {
    }
  }
  delay(10);
}
