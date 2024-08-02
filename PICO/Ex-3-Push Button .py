import machine as gpio
import utime as TM

# Define the pin for the push button
Button_IN = gpio.Pin(16, gpio.Pin.IN, gpio.Pin.PULL_DOWN)

while True:
    # Read the state of the push button
    Button_Status = Button_IN.value()

    # Check if the button is pressed (active high)
    if Button_Status == 1:
        print("Button is pressed")
    else:
        print("Button is not pressed")

    # Add a small delay to avoid rapid state changes
    TM.sleep_ms(100)
