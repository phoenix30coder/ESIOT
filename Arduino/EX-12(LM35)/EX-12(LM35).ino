// Include necessary libraries
#include <Arduino.h>  // The Arduino core library

// Define pin constants
const int TEMPERATURE_SENSOR_PIN = A0;  // Analog input pin for the LM35 sensor

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Read the analog voltage from the LM35 sensor
  int sensorValue = analogRead(TEMPERATURE_SENSOR_PIN);

  // Convert the sensor value to temperature in degrees Celsius
  float voltage = (sensorValue / 1023.0) * 5.0;  // Use 5V reference
  float temperatureCelsius = (voltage) * 100.0;  // LM35 output is 10 mV per degree Celsius

  // Print the temperature to the serial monitor
  Serial.print("Voltage: ");
  Serial.print(voltage, 2); // Print voltage with 2 decimal places
  Serial.println(" V");

  Serial.print("Temperature (Celsius): ");
  Serial.print(temperatureCelsius, 2); // Print temperature with 2 decimal places
  Serial.println(" °C");

  // Add a delay if needed
  delay(1000);  // 1000 milliseconds (1 second)
}
