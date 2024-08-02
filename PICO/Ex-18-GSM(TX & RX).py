import machine
import time
lm35_pin = machine.ADC(26)

temperature_celsius = 0.0

GSM_SERIAL = machine.UART(0, baudrate=9600, tx=machine.Pin(0), rx=machine.Pin(1))

# User Credentials
Host_URL = "console.thingzmate.com"
Sub_URL_POST = "/api/v1/device-types/thingzmate-basic-kit/devices/demo-1/http-uplink"
Sub_URL_GET = "/api/v1/device-types/thingzmate-basic-kit/devices/demo-1/http-downlink"
PORT = "80"
Bearer_Key = "Bearer 4e3dac123dbf812530fe0af613ff4aab"

# Variables
jsonData = ""
dataStarted = False
RECV = False
response = ""
Downlindata=""

def GSM_Data(command, timeout, debug):
    if debug:
        print("AT Command ==> " + command)

    GSM_SERIAL.write(command + "\r\n")
    response = ""
    dataStarted = False
    start_time = time.ticks_ms()

    while (time.ticks_ms() - start_time) < timeout:
        if GSM_SERIAL.any():
            c = GSM_SERIAL.read(1).decode('utf-8')
            
            if debug:
                print(c, end='')            
            global RECV
            if c == '{':
                print("data_coming")
            if c == '{' and RECV:
                dataStarted = True
                response = ""

            if dataStarted and c != '{' and c != '}':
                response += c
            if c == '}' and dataStarted:
                dataStarted = False
                print("Received LED Status Data: " + response)
                Downlinkaction(response)
                response = ""
    if debug:
        print(response)

    return response

def GSM_Module_init():
    GSM_Data("AT", 1000, DEBUG)
    time.sleep(3)
    GSM_Data("AT+CPIN?", 1000, DEBUG)
    time.sleep(3)
    GSM_Data("AT+CREG?", 1000, DEBUG)
    time.sleep(3)
    GSM_Data("AT+CGATT?", 1000, DEBUG)
    time.sleep(3)
    GSM_Data("AT+CIPSHUT", 1000, DEBUG)
    time.sleep(3)
    GSM_Data("AT+CIPSTATUS", 1000, DEBUG)
    time.sleep(3)

def Sensor_Data():
    global temperature_celsius
    raw_value = lm35_pin.read_u16()  # Read the raw ADC value
    voltage = (raw_value / 65535) * 3.3  # Convert raw value to voltage (assuming 3.3V reference)
    temperature_celsius = (voltage ) * 100  # Calculate temperature in Celsius
    print("temp: " + str(temperature_celsius))
    return '{"Temperature": ' + str(temperature_celsius) +'}'

def Sending_data_to_the_cloud():
    global jsonData
    global RECV
    RECV = False
    GSM_Data("AT+CIPMUX=1", 1000, DEBUG)
    time.sleep(2)
    GSM_Data('AT+CSTT="airtelgprs.com"', 1000, DEBUG)
    time.sleep(3)
    GSM_Data("AT+CIICR", 1000, DEBUG)
    time.sleep(3)
    GSM_Data("AT+CIFSR", 1000, DEBUG)
    time.sleep(3)
    GSM_Data("AT+CIPSPRT=0", 1000, DEBUG)
    time.sleep(3)
    jsonData = Sensor_Data()
    time.sleep(0.2)
    sendData = ('POST '+ Sub_URL_POST+ ' HTTP/1.1\r\nHost: '+ Host_URL+ '\r\nAuthorization: '+ Bearer_Key+ '\r\nContent-Type: application/json\r\nContent-Length: '+ str(len(jsonData))+ '\r\n\r\n'+ jsonData)
    GSM_Data('AT+CIPSTART=0,"TCP","' + Host_URL + '",' + PORT, 1000, DEBUG)
    time.sleep(2)
    GSM_Data('AT+CIPSEND=0,' + str(len(sendData)), 1000, DEBUG)
    time.sleep(2)
    GSM_SERIAL.write(sendData)
    GSM_SERIAL.write('\x1A')
    delay_duration = 10
    for x in range(delay_duration * 1000):
        pass
    GSM_Data('AT+CIPCLOSE=0', 4000, DEBUG)

def Downlinkaction(response):
    if response == "01":
        print("LED_ON")
    elif response == "02":
        print("LED_OFF")

    
def receiveDataFromCloud():
    global RECV
    RECV = True
    send_Data = ('GET '+ Sub_URL_GET+ ' HTTP/1.1\r\nHost:'+ Host_URL+ '\r\nAuthorization: '+ Bearer_Key+ '\r\n\r\n')
    GSM_Data('AT+CIPSTART=0,"TCP","' + Host_URL + '",' + PORT, 1000, DEBUG)
    time.sleep(3)
    GSM_Data('AT+CIPSEND=0,' + str(len(send_Data)), 1000, DEBUG)
    time.sleep(2)
    GSM_SERIAL.write(send_Data)
    GSM_SERIAL.write('\x1A')
    delay_duration = 10
    for x in range(delay_duration * 1000):
        pass
    GSM_Data('AT+CIPCLOSE=0', 8000, DEBUG)
    time.sleep(2)

DEBUG = True

def setup():
    print("Thinzkit_Basic_GSM")
    GSM_Module_init()

def loop():
    Sending_data_to_the_cloud()
    time.sleep(20)
    receiveDataFromCloud()
    time.sleep(20)

setup()

while True:
    loop()

