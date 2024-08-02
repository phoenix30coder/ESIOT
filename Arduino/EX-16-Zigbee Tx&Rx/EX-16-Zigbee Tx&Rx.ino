#include <SoftwareSerial.h>

SoftwareSerial xbee(2, 3); // RX, TX

void setup() {
  Serial.begin(9600);
  xbee.begin(9600); // Set the baud rate to match your XBee module
}

void loop() {
  if (Serial.available()) {
    String dataToSend = Serial.readString();
    xbee.println(dataToSend); // Send the data to XBee
  }

  if (xbee.available()) {
    String receivedData = "";
    while (xbee.available()) {
      char c = xbee.read();
      receivedData += c;
    }
    Serial.println("Received: " + receivedData);
  }
}
