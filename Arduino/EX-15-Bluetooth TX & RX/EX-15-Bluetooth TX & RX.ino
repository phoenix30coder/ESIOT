#include <SoftwareSerial.h>

#define LED_pin 13

SoftwareSerial bluetooth(2, 3); // RX, TX
float data=25.98;
char charArray[10]; 


void setup() {
  Serial.begin(9600); // Initialize the serial monitor
  bluetooth.begin(9600); // Initialize the Bluetooth communication
  pinMode(LED_pin,OUTPUT);
}

void loop() {
  // Check if data is available from Bluetooth module
  if (bluetooth.available()) {
    char receivedChar = bluetooth.read(); // Read the character received via Bluetooth
    Serial.print("Received: ");
    Serial.println(receivedChar);

    // Example: Send a response back to the Bluetooth module
    if (receivedChar == '1') {
      digitalWrite(LED_pin, HIGH);
      Serial.print("LED_ON");
    }
    else if(receivedChar == '0')
    {
     digitalWrite(LED_pin, LOW);
      Serial.print("LED_OFF");
    }
    else if(receivedChar == '2'){
      dtostrf(data, 6, 2, charArray); // float to char convertion 
      bluetooth.write(charArray);
      delay(100);      
    }
  }
}
