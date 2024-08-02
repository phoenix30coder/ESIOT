#include <Arduino.h>

/*RGB LED pins (Common Anode)*/
#define Red_Pin 9
#define Green_Pin 10
#define Blue_Pin 11

/*Delay  (in milliseconds)*/
#define COLOR_CHANGE_DELAY 1000

void setup() {
  // Initialize the RGB LED pins as outputs
  pinMode(Red_Pin, OUTPUT);
  pinMode(Green_Pin, OUTPUT);
  pinMode(Blue_Pin, OUTPUT);
}

void loop() {
  /* Pattern 1: Red */
  digitalWrite(Red_Pin, LOW);   // Turn on Red (Common Anode)
  digitalWrite(Green_Pin, HIGH); // Turn off Green
  digitalWrite(Blue_Pin, HIGH);  // Turn off Blue
  delay(COLOR_CHANGE_DELAY); 
  
  /* Pattern 2: Green */
  digitalWrite(Red_Pin, HIGH);   // Turn off Red
  digitalWrite(Green_Pin, LOW);  // Turn on Green (Common Anode)
  digitalWrite(Blue_Pin, HIGH);  // Turn off Blue
  delay(COLOR_CHANGE_DELAY); 

  /* Pattern 3: Blue */
  digitalWrite(Red_Pin, HIGH);   // Turn off Red
  digitalWrite(Green_Pin, HIGH); // Turn off Green
  digitalWrite(Blue_Pin, LOW);   // Turn on Blue (Common Anode)
  delay(COLOR_CHANGE_DELAY); 

  /*Pattern 4: white (Red + Blue+ Green)*/
  digitalWrite(Red_Pin, LOW);    // Turn on Red (Common Anode)
  digitalWrite(Green_Pin, HIGH); // Turn off Green
  digitalWrite(Blue_Pin, LOW);   // Turn on Blue (Common Anode)
  delay(COLOR_CHANGE_DELAY); 
}
