#include <Arduino.h>

// Define the relay control pin
const int relayPin = 8; // Change to the pin where your relay module's control pin is connected

void setup() {
  // Initialize the relay control pin as an output
  pinMode(relayPin, OUTPUT);
  
  // Initialize serial communication
  Serial.begin(9600);
  Serial.println("Relay Control for 230V Appliance:");
  
  // Turn off the relay initially for safety
  digitalWrite(relayPin, LOW);
}

void loop() {
  // Prompt the user to control the appliance
  Serial.println("Enter '1' to turn ON, '0' to turn OFF:");
  
  while (Serial.available() <= 0);
  char command = Serial.read();
  
  if (command == '1') {
    Serial.println("Turning ON the Relay...");
    digitalWrite(relayPin, HIGH); // Turn ON the relay
  } else if (command == '0') {
    Serial.println("Turning OFF the Relay...");
    digitalWrite(relayPin, LOW); // Turn OFF the relay
  } else {
    Serial.println("Enter '1' to turn ON, '0' to turn OFF.");
  }
  
  // Wait for a moment
  delay(1000);
}
