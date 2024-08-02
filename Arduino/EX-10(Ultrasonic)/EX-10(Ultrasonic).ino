#include <Arduino.h>  // The Arduino core library

// Define pin constants
const int TRIGGER_PIN = 10;  // Digital output pin for the sensor's trigger
const int ECHO_PIN = 11;     // Digital input pin for the sensor's echo

// Define constants for speed of sound in air (in meters per second)
const float SPEED_OF_SOUND = 343.0;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Define trigger pin as an output and echo pin as an input
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  // Generate a 10us pulse on the trigger pin to start the measurement
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  // Measure the time it takes for the echo pin to go HIGH
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate the distance based on the time and speed of sound
  float distance = (duration * 0.5 * SPEED_OF_SOUND) / 10000.0;  // Convert to centimeters

  // Print the distance to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance, 2);  // Print with 2 decimal places
  Serial.println(" cm");

  // Add a delay if needed
  delay(100);  // 100 milliseconds
}
