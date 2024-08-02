// Include necessary libraries
#include <Arduino.h>  // The Arduino core library

// Define pin constants
const int POTENTIOMETER_PIN = A1;  // Analog input pin

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Read the voltage from the potentiometer
  uint16_t sensorValue = analogRead(POTENTIOMETER_PIN);
  
  Serial.print("RAWDATA:");
  Serial.print(sensorValue);

  // Convert the sensor value to voltage (0-5V)
  float voltage = (sensorValue / 1023.0) * 5.0;

  // Print the voltage to the serial monitor
  Serial.print("Voltage: ");
  Serial.print(voltage, 2);  // Print with 2 decimal places
  Serial.println(" V");

  // Add a delay if needed
  delay(500);  // 500 milliseconds
}
