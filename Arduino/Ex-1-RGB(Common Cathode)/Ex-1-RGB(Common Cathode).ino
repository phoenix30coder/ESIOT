#include <Arduino.h>

/*RGB LED pins (Common Cathode)*/
#define Red_Pin 9
#define Green_Pin 10
#define Blue_Pin 11
/*Delay  (in milliseconds)*/
#define COLOR_CHANGE_DELAY 100

void setup() {
  /*Initialize the RGB LED pins as outputs*/
  pinMode(Red_Pin, OUTPUT);
  pinMode(Green_Pin, OUTPUT);
  pinMode(Blue_Pin, OUTPUT);
}

void loop() {
  /*Turn on Red, turn off Green and Blue*/
  digitalWrite(Red_Pin, HIGH);
  digitalWrite(Green_Pin, LOW);
  digitalWrite(Blue_Pin, LOW);
  delay(COLOR_CHANGE_DELAY); 

  /*Turn off Red, turn on Green, turn off Blue*/
  digitalWrite(Red_Pin, LOW);
  digitalWrite(Green_Pin, HIGH);
  digitalWrite(Blue_Pin, LOW);
  delay(COLOR_CHANGE_DELAY); 

  /*Turn off Red, turn off Green, turn on Blue*/
  digitalWrite(Red_Pin, LOW);
  digitalWrite(Green_Pin, LOW);
  digitalWrite(Blue_Pin, HIGH);
  delay(COLOR_CHANGE_DELAY); 
  
  /*Turn ON Red,Green,Blue*/
  digitalWrite(Red_Pin, HIGH);
  digitalWrite(Green_Pin, HIGH);
  digitalWrite(Blue_Pin, HIGH);
  delay(COLOR_CHANGE_DELAY); 
}

