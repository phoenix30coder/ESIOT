#include <SoftwareSerial.h>
#include <DFRobot_DHT11.h>
DFRobot_DHT11 DHT;
#define DHT11_PIN 8
#define DEBUG true

SoftwareSerial GSM_Serial(2, 3); // Pin 2 and 3 act as RX and TX. Connect them to TX and RX of ESP8266

/*user Credential*/ 
String Host_URL = "console.thingzmate.com";
String Sub_URL_POST="/api/v1/device-types/thingzmate-basic-kit/devices/demo-1/http-uplink";
String Sub_URL_GET="/api/v1/device-types/thingzmate-basic-kit/devices/demo-1/http-downlink";
String PORT = "80";
String Bearer_Key= "Bearer 4e3dac123dbf812530fe0af613ff4aab";

/*Variables*/
int sendVal;
String response = "";
bool dataStarted=0,RECV=0;
String jsonData="";

void setup() {
  Serial.begin(9600);
  GSM_Serial.begin(9600);
  Serial.println("Thinzkit_Basic_GSM");
  GSM_Module_init();
}

void loop() {
  /*Uplink*/
  Sending_data_to_the_cloud();
  delay(10000);
  /*Downlink*/
  receiveDataFromCloud();
  delay(10000); // Delay before making the next request
}

/*HTTP POST Function*/
void Sending_data_to_the_cloud(){
  RECV=0;
  GSM_Data("AT+CIPMUX=1", 1000, DEBUG);
  delay(2000);
  GSM_Data("AT+CSTT=\"airtelgprs.com\"", 1000, DEBUG); // Connect to WiFi network
  delay(3000);
  GSM_Data("AT+CIICR", 1000, DEBUG); // Connect to WiFi network
  delay(3000);
  GSM_Data("AT+CIFSR", 1000, DEBUG); // Connect to WiFi network
  delay(3000);
  GSM_Data("AT+CIPSPRT=0", 1000, DEBUG); // Connect to WiFi network
  delay(3000);
  Sensor_Data();
  delay(200);
  String sendData = "POST "+Sub_URL_POST+" HTTP/1.1\r\nHost: " + Host_URL + "\r\nAuthorization: "+Bearer_Key+"\r\nContent-Type: application/json\r\nContent-Length: " + String(jsonData.length()) + "\r\n\r\n" + jsonData;
  GSM_Data("AT+CIPSTART=0,\"TCP\",\"" + Host_URL + "\"," + PORT, 1000, DEBUG);
  delay(2000);
  GSM_Data("AT+CIPSEND=0," + String(sendData.length()), 1000, DEBUG);
  delay(2000);
  GSM_Serial.print(sendData);
  GSM_Serial.print((char)26);
  for(int i=0;i<10000;i++);
  GSM_Data("AT+CIPCLOSE=0", 4000, DEBUG);

}

/*HTTP GET Function*/
void receiveDataFromCloud() {
  RECV=1;
  String send_Data = "GET "+Sub_URL_GET+" HTTP/1.1\r\nHost:" + Host_URL + "\r\nAuthorization: "+Bearer_Key+"\r\n\r\n";
  GSM_Data("AT+CIPSTART=0,\"TCP\",\"" + Host_URL + "\"," + PORT, 1000, DEBUG);
  delay(3000);
  GSM_Data("AT+CIPSEND=0," + String(send_Data.length()), 1000, DEBUG);
  delay(2000);
  GSM_Serial.print(send_Data);
  GSM_Serial.print((char)26);
  for(int i=0;i<20000;i++);
  GSM_Data("AT+CIPCLOSE=0", 8000, DEBUG);
  delay(2000);
}
/*We can write our downlink action in this function*/
void Downlinkaction(){
  if(response=="01"){Serial.println("LED_ON");}
  if(response=="02"){Serial.println("LED_OFF");}    
} 
/**/
void GSM_Module_init()
{
  GSM_Data("AT", 1000, DEBUG);  // Reset the ESP8266 module
  delay(3000);
  GSM_Data("AT+CPIN?", 1000, DEBUG); // Set the ESP mode as station mode
  delay(3000);
  GSM_Data("AT+CREG?", 1000, DEBUG); // Connect to WiFi network
  delay(3000);
  GSM_Data("AT+CGATT?", 1000, DEBUG); // Connect to WiFi network
  delay(3000);
  GSM_Data("AT+CIPSHUT", 1000, DEBUG); // Connect to WiFi network
  delay(3000);
  GSM_Data("AT+CIPSTATUS", 1000, DEBUG); // Connect to WiFi network
  delay(3000);
  
}

String GSM_Data(String command, const int timeout, boolean debug) {
  if (debug) {
  Serial.print("AT Command ==> ");
  Serial.println(command);
  }
  GSM_Serial.println(command);

  long int time = millis();
  while ((time + timeout) > millis()) {
    while (GSM_Serial.available()) {
    char c = GSM_Serial.read();
    if (debug) {
      Serial.write(c); 
    }
    if (c == '{' && RECV==1) {
      // Start capturing data
      dataStarted = true;
      response = "";
    }

    if (dataStarted == true && c != '{' && c != '}' ) {
      // Start capturing data
      response += c;
    }
    if(c == '}'&& dataStarted == true){
        dataStarted = false;
        Serial.println("Received LED Status Data: " + response);
        Downlinkaction();      
        response = "";
      }
    }
   }
  if (debug) {
    Serial.print(response);
  }
  return response;
}

void Sensor_Data(){
  DHT.read(DHT11_PIN);
  Serial.print("temp:");
  Serial.print(DHT.temperature);
  Serial.print("  humi:");
  Serial.println(DHT.humidity);
  jsonData = "{\"Temperature\":" + String(DHT.temperature) + ",\"Humidity\":" + String(DHT.humidity) + "}";
}



