#include <Arduino.h>  // The Arduino core library

// Define pin constants
const int LED_PIN = 13;  // Digital output pin for the LED

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Define LED pin as an output
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Check if data is available in the serial buffer
  if (Serial.available() > 0) {
    // Read the incoming command
    char command = Serial.read();

    // Perform actions based on the received command
    switch (command) {
      case 'ON':
      case 'on':
      case '1':
        digitalWrite(LED_PIN, HIGH);  // Turn on the LED
        Serial.println("LED is ON");
        break;
        
      case 'OFF':
      case 'off':
      case '0':
        digitalWrite(LED_PIN, LOW);  // Turn off the LED
        Serial.println("LED is OFF");
        break;

      default:
        Serial.println("Use 'ON'/'1' or 'OFF'/'0' to control the LED.");
        break;
    }
  }
}
