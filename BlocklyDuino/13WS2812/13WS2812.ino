/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Tue, 12 Oct 2021 07:25:54 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


String matrixString = "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";

int MatrixLed_marquee_time = 500;

int MatrixLed_marquee_rotate = 0;

#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(8, 6, NEO_GRB + NEO_KHZ800);

String strTemp_ = "";

int HextoRGB(char val) {
  String hex ="0123456789abcdef";
  return hex.indexOf(val);
}

void MatrixLed(String color) {
  color.replace("#","");
  matrixString = color;
  int R,G,B;
  int range;
  range = color.length()/6;
  for (int i=0;i<range;i++) {
    R = (HextoRGB(color[i*6])*16+HextoRGB(color[i*6+1]));
    G = (HextoRGB(color[i*6+2])*16+HextoRGB(color[i*6+3]));
    B = (HextoRGB(color[i*6+4])*16+HextoRGB(color[i*6+5]));
    pixels.setPixelColor(i, pixels.Color(R, G, B));
  }
  pixels.show();
}

String MatrixLedColorRandom() {
  String s = "0123456789abcdef";
  String color = "#000000";
  int R = random(0, 255);
  int G = random(0, 255);
  int B = random(0, 255);
  int r1 = (R-R%16)/16;
  int r2 = R%16;
  int g1 = (G-G%16)/16;
  int g2 = G%16;
  int b1 = (B-B%16)/16;
  int b2 = B%16;
  color[1] = s[r1];
  color[2] = s[r2];
  color[3] = s[g1];
  color[4] = s[g2];
  color[5] = s[b1];
  color[6] = s[b2];
  return color;
}

void setup()
{
  pixels.begin();
  pixels.show();

  pixels.setBrightness(5);
}


void loop()
{
  MatrixLed(String(MatrixLedColorRandom())+String(MatrixLedColorRandom())+String(MatrixLedColorRandom())+String(MatrixLedColorRandom())+String(MatrixLedColorRandom())+String(MatrixLedColorRandom())+String(MatrixLedColorRandom())+String(MatrixLedColorRandom())+"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
  delay(100);
  MatrixLed("000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
}