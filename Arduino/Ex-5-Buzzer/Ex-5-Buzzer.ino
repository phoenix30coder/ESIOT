#include <Arduino.h>  // The Arduino core library

// Define pin constants
#define  IR_SENSOR_PIN  11  // Digital input pin for the IR sensor

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Define IR sensor pin as an input
  pinMode(IR_SENSOR_PIN, INPUT);
}

void loop() {
  // Read the digital output from the IR sensor
  bool sensorValue = digitalRead(IR_SENSOR_PIN);

  // Print the sensor value to the serial monitor
  Serial.print("IR Sensor Output: ");
  Serial.println(sensorValue);

  // Add a delay if needed
  delay(1000);  // 1000 milliseconds
}
