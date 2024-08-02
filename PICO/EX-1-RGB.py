import machine as Gpio
import utime as TM

# Define the RGB LED pins (common cathode)
Red_Pin = Gpio.Pin(15, Gpio.Pin.OUT)
Green_Pin = Gpio.Pin(14, Gpio.Pin.OUT)
Blue_Pin = Gpio.Pin(13, Gpio.Pin.OUT)

# Helper function to set RGB color
def set_rgb_color(red, green, blue):
    Red_Pin.value(red)
    Green_Pin.value(green)
    Blue_Pin.value(blue)

# Main loop
while True:
    # Red
    set_rgb_color(1, 0, 0)
    TM.sleep(1)
    
    # Green
    set_rgb_color(0, 1, 0)
    TM.sleep(1)
    
    # Blue
    set_rgb_color(0, 0, 1)
    TM.sleep(1)

