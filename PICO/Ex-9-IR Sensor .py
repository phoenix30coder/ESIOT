import machine as gpio
import utime as TM 

# Define the GPIO pin for the IR sensor
Sensor_In = gpio.Pin(14, gpio.Pin.IN)

# Function to read and print the IR sensor's digital output
def read_ir_sensor():
    sensor_output = Sensor_In.value()
    if sensor_output == 0:
        print("IR sensor detected an object.")
    else:
        print("IR sensor did not detect an object.")

# Main loop
while True:
    read_ir_sensor()
    TM.sleep(1)  # Add a delay between readings