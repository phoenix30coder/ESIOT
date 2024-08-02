/*
thingZkit_Basic 
*/
#include <SoftwareSerial.h>

String inputString = "";         // a String to hold incoming data

bool stringComplete = false;     // whether the string is complete

long old_time=millis();
long new_time;
char Downlink_Data;

long uplink_interval=30000;

// Define pin constants
const int TEMPERATURE_SENSOR_PIN = A0;

bool time_to_at_recvb=false;
bool get_LA66_data_status=false;

bool network_joined_status=false;

SoftwareSerial ss(2, 3); // Arduino RX, TX ,

char rxbuff[128];
uint8_t rxbuff_index=0;

uint16_t sensorValue=0;
uint8_t LoRa_Uplink_Buffer[2];
String temperatureString;
uint16_t Temp=0;

void sensorread ();

void setup() {
  // initialize serial
  Serial.begin(9600);

  ss.begin(9600);
  ss.listen();
  pinMode(13, OUTPUT);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);

  ss.println("ATZ");//reset LA66
}

void loop() {
  new_time = millis();

  if((new_time-old_time>=uplink_interval)&&(network_joined_status==1)){
    old_time = new_time;
    get_LA66_data_status=false;
    sensorread();
    ss.println("AT+SENDB=0,2,2,"+String(Temp,HEX));//confirm status,Fport,payload length,payload(HEX)
  }

  if(time_to_at_recvb==true){
    time_to_at_recvb=false;
    get_LA66_data_status=true;
    delay(1000);
    ss.println("AT+CFG");
  }

    while ( ss.available()) {
    // get the new byte:
    char inChar = (char) ss.read();
    // add it to the inputString:
    inputString += inChar;

    rxbuff[rxbuff_index++]=inChar;

    if(rxbuff_index>128)
    break;
    
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n' || inChar == '\r') {
      stringComplete = true;
      rxbuff[rxbuff_index]='\0';
      
      if(strncmp(rxbuff,"JOINED",6)==0){
        network_joined_status=1;
      }

      if(strncmp(rxbuff,"Dragino LA66 Device",19)==0){
        network_joined_status=0;
      }

      if(strncmp(rxbuff,"Run AT+RECVB=? to see detail",28)==0){
        time_to_at_recvb=true;
        stringComplete=false;
        inputString = "\0";
      }

      if(strncmp(rxbuff,"AT+RECVB=",9)==0){       
        stringComplete=false;
        inputString = "\0";
        Serial.print("\r\nGet downlink data(FPort & Payload):");
        Serial.println(&rxbuff[12]);
        Downlink_Data=((rxbuff[12]));
        if(Downlink_Data == '1'){digitalWrite(13, HIGH);Serial.println("LED_ON");digitalWrite(13,HIGH);}
        else if (Downlink_Data=='2'){digitalWrite(13, LOW);Serial.println("LED_OFF");digitalWrite(13,LOW);}

      }
      
      rxbuff_index=0;
      if(get_LA66_data_status==true){
        stringComplete=false;
        inputString = "\0";
      }
    }
  }

   while ( Serial.available()) {
    // get the new byte:
    char inChar = (char) Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n' || inChar == '\r') {
      ss.print(inputString);
      inputString = "\0";
    }
  }
  // print the string when a newline arrives:
  if (stringComplete) {
    Serial.print(inputString);
    // clear the string:
    inputString = "\0";
    stringComplete = false;
  }
}

void sensorread(){
  // Read the analog voltage from the LM35 sensor
  sensorValue = analogRead(TEMPERATURE_SENSOR_PIN);

  // Convert the sensor value to temperature in degrees Celsius
  float voltage = (sensorValue / 1023.0) * 5.0;  // Use 5V reference
  float temperatureCelsius = (voltage) * 100.0;  // LM35 output is 10 mV per degree Celsius


  // Format the float with 2 decimal places
  temperatureString = String(temperatureCelsius, 2);

  // Convert the formatted string to a float
  float temperatureFloat = temperatureString.toFloat();

  Temp= uint16_t (temperatureFloat *100);
  
  Serial.print("Temperature (Celsius): ");
  Serial.println(temperatureFloat);

}
//jassimm0401@gamil.com