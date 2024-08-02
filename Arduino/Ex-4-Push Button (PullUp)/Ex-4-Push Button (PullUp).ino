#include <Arduino.h>

#define buttonPin  2

void setup() {
  // Initialize the button pin as an input
  pinMode(buttonPin, INPUT);
  // Initialize serial communication
  Serial.begin(9600);
  Serial.println("Active-High Push Button Status:");
}

void loop() {
  /*Read the status of the button*/
  bool buttonState = digitalRead(buttonPin);

  // Check for valid button state
  if (buttonState == HIGH || buttonState == LOW) {
    // Print the button status
    if (buttonState == LOW) {
      Serial.println("Button is pressed (Active-High)");
    } else {
      Serial.println("Button is not pressed");
    }
  } else {
    // Handle invalid button state
    Serial.println("Error: Invalid button state");
  }

  delay(1000); 
}
