import machine as gpio
import utime as TM

# Define the buzzer pin (change to your GPIO pin)
buzzer_pin = gpio.Pin(15, gpio.Pin.OUT)

# Define the duration (in milliseconds) for the buzzer to sound
duration_ms = 500

# Function to make the buzzer sound
def buzz():
    buzzer_pin.value(1)  # Turn on the buzzer
    TM.sleep_ms(duration_ms)  # Sound duration
    buzzer_pin.value(0)  # Turn off the buzzer

# Main loop
while True:
    buzz()
    TM.sleep(2)  # Pause for 2 seconds before sounding the buzzer again