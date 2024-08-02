/*!
 * @file D.ino
 * @brief DHT11 is used to read the temperature and humidity of the current environment. 
 * @Library Need to install DFROBOT LIB 
 */

#include <DFRobot_DHT11.h>
DFRobot_DHT11 DHT;
#define DHT11_PIN 8

void setup() {
  Serial.begin(9600);
}

void loop() {
  DHT.read(DHT11_PIN);
  Serial.print("temp:");
  Serial.print(DHT.temperature);
  Serial.print("  humi:");
  Serial.println(DHT.humidity);
  delay(1000);
}
