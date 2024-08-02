
import machine
import utime
from umqtt.simple import MQTTClient
import network
import json

# Your Wi-Fi credentials
ssid = 'Praveen'
password = 'Praveenpk'

# Define MQTT parameters
MQTT_BROKER = "console.thingzmate.com"  # Replace with your MQTT broker address
CLIENT_ID = "NNEF.42VNKZI7JXCNLPA"      # Replace with your CLIENT_ID
USERNAME = "e2515df66b7bac352d1fcfeb28edde3b"      # Replace with your USSERNAME
PASSWORD = "12345678"      # Replace with your PASSWORD
MQTT_PORT = 1883 
TOPIC_SUBSCRIBE =b"thinks-kit-basic-1/thingzkit-basic-mqtt/downlink"     # Replace with your TOPIC_SUBSCRIBE
TOPIC_PUBLISH =b"thinks-kit-basic-1/thingzkit-basic-mqtt/uplink"     # Replace with your TOPIC_PUBLISH
# Create a Wi-Fi station interface
wlan = network.WLAN(network.STA_IF)

# Activate the interface
wlan.active(True)

# Connect to the Wi-Fi network
wlan.connect(ssid, password)

# Wait for the connection to be established
while not wlan.isconnected():
    pass

# Print the network configuration
print('Connected to', ssid)
print('IP address:', wlan.ifconfig()[0])

# Define the LED pin and set it off
led = machine.Pin("LED", machine.Pin.OUT)
led.value(0)

#PUBLISH
def publish_data():
    data_to_publish = {
        "temperature": 25.5,
        "humidity": 86.9
    }
    json_data = json.dumps(data_to_publish)
    client.publish(TOPIC_PUBLISH, json_data.encode())
    
# Callback function for incoming MQTT messages
def mqtt_callback(topic, msg):
    try:
        # Attempt to decode the message as JSON
        received_data = json.loads(msg)  
        if received_data == "on":
            led.value(1)
            print("LED_ON")
        elif received_data == "off":
            led.value(0)
            print("LED_OFF")
             # Handle any exceptions that occur during message processing
    except Exception as e:
        print("Error processing MQTT message:", e)
        
# Connect to the MQTT broker with user credentials
client = MQTTClient(CLIENT_ID, MQTT_BROKER, user=USERNAME,password=PASSWORD,port=MQTT_PORT)
#check if client is connected or not

if client.connect() is not None:
    print("Connected to MQTT broker")
else:
    print("Failed to connect to MQTT broker")
    
#Set the callbac to client    
client.set_callback(mqtt_callback)
# Subscribe to the topic
client.subscribe(TOPIC_SUBSCRIBE)
# Main loop
try:
    while True:
        publish_data()
        utime.sleep(10)
        client.check_msg()
except:
    led.value(0)
    print("Stoped")
     