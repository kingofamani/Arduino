#include <Wire.h>
#include <Adafruit_MLX90614_2.h>
#include "U8glib.h"

Adafruit_MLX90614_2 mlx = Adafruit_MLX90614_2();
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE); // I2C / TWI ;
float tmax = 0.00;
int buzzer = 4;



void setup() {
  Serial.begin(9600);
  Serial.println("Adafruit MLX90614 test");
  //pinMode(buzzer, OUTPUT);
  //digitalWrite(buzzer, HIGH);
  mlx.multi = .02;
  mlx.offset = 271.70;/*273.15為沒有補償的標準值,數字改小顯示溫度增加*/
  mlx.begin();
  // flip screen, if required
  // u8g.setRot180();
}

void loop() {
  float tempC = mlx.readObjectTempC();
  
    Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC());
    Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
    Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF());
    Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");

    Serial.println();
  delay(1000);


  if (tmax < tempC) {
    tmax = tempC;
  }

    if (tempC > 37)/*到達溫度蜂鳴器鳴叫*/
    {
      //Serial.println(tempC);
    }
    else
    {
      Serial.println("溫度過高");
      //digitalWrite(buzzer, HIGH);
    }
  delay(100);

}
