import machine as gpio
import utime as TM

# Define the LED pin
led_pin = gpio.Pin("LED", gpio.Pin.OUT)

# Define the UART (serial) port
uart = gpio.UART(0, baudrate=9600, tx=gpio.Pin(0), rx=gpio.Pin(1))  # Use GPIO 0 (TX) and GPIO 1 (RX)

while True:
    # Read data from the serial port
    Slave_Data = uart.readline()
    
    if Slave_Data:
        Slave_Data = Slave_Data.decode().strip()  # Decode the received Slave_Data as a string
        
        # Check the received command
        if Slave_Data == 'ON':
            led_pin.value(1)  # Turn on the LED
            print("LED is ON")
        elif Slave_Data == 'OFF':
            led_pin.value(0)  # Turn off the LED
            print("LED is OFF")
        else:
            print("Invalid command")

    TM.sleep(0.1)  # Add a small delay to avoid busy-waiting

