/*
  Example made by Dejan, How To Mechatronics,
  https://howtomechatronics.com/

*/

#include <NewPing.h>  // https://bitbucket.org/teckel12/arduino-new-ping/wiki/Home
#include "dht.h"      // https://github.com/RobTillaart/DHTlib

#define TRIGGER_PIN  5
#define ECHO_PIN     6
#define MAX_DISTANCE 400
#define dht22 8 // DHT22 temperature and humidity sensor

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
dht DHT; // Creats a DHT object

int readDHT, temp, hum;
float speedOfSound, distance, duration;

void setup() {
  Serial.begin(9600);
}

void loop() {
  delay(100);

  // Read temperature and humidity from DHT22 sensor
  readDHT = DHT.read22(dht22); // Reads the data from the sensor
  temp = DHT.temperature; // Gets the values of the temperature
  hum = DHT.humidity; // Gets the values of the humidity


  speedOfSound = 331.4 + (0.6 * temp) + (0.0124 * hum); // Calculate speed of sound in m/s

  duration = sonar.ping_median(10); // 10 interations - returns duration in microseconds
  duration = duration/1000000; // Convert mircroseconds to seconds
  distance = (speedOfSound * duration)/2;
  distance = distance * 100; // meters to centimeters

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println("cm");

}
