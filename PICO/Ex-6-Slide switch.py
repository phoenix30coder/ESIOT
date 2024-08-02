import machine as gpio
import utime as TM

# Define the GPIO pin for the slide switch
slide_switch_pin = gpio.Pin(14, gpio.Pin.IN)

# Function to read and print the slide switch status
def read_slide_switch_status():
    status = slide_switch_pin.value()
    if status == 0:
        return "Slide switch is in OFF position"
    else:
        return "Slide switch is in ON position"

# Main loop
while True:
    switch_status = read_slide_switch_status()
    print(switch_status)
    TM.sleep(1)  # Add a delay to avoid rapid status changes
