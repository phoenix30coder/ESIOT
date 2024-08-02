import machine as gpio
import utime as TM 

# Define the GPIO pin for the relay control (change to your GPIO pin)
relay_pin = gpio.Pin(16, gpio.Pin.OUT)

# Function to turn on the appliance
def turn_on_appliance():
    relay_pin.value(1)  # Turn on the relay
    print("Appliance is ON")

# Function to turn off the appliance
def turn_off_appliance():
    relay_pin.value(0)  # Turn off the relay
    print("Appliance is OFF")

# Main loop
while True:
    # Simulate turning the appliance on for 5 seconds
    turn_on_appliance()
    TM.sleep(5)
    
    # Simulate turning the appliance off for 5 seconds
    turn_off_appliance()
    TM.sleep(5)

