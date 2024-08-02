#include <Arduino.h>

// Define the slide switch pin
const int switchPin = 2; // Change to the pin where your slide switch is connected

void setup() {
  // Initialize the slide switch pin as an input
  pinMode(switchPin, INPUT_PULLUP);
  
  // Initialize serial communication
  Serial.begin(9600);
  Serial.println("Slide Switch Status:");
}

void loop() {
  // Read the status of the slide switch (LOW when switched, HIGH when not switched)
  int switchState = digitalRead(switchPin);
  
  // Check if the slide switch is in the ON position (switched)
  if (switchState == LOW) {
    Serial.println("Switch ON");
  } else {
    Serial.println("Switch OFF");
  }
  
  delay(500); // Add a small delay to avoid rapid toggling of status
}
