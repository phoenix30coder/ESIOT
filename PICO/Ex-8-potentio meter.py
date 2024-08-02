import machine as gpio
import utime as TM

# Define the ADC (Analog-to-Digital Converter) pin for the potentiometer
potentiometer_pin = gpio.ADC(26)

# Define a unique variable name to store the voltage reading
voltage = 0.0

# Function to read the voltage from the potentiometer
def read_potentiometer_voltage():
    global voltage
    raw_value = potentiometer_pin.read_u16()  # Read the raw ADC value
    voltage = (raw_value / 65535) * 3.3  # Convert to voltage (assuming 3.3V reference)

# Main loop
while True:
    read_potentiometer_voltage()
    print("Potentiometer Voltage: {:.2f} V".format(voltage))
    TM.sleep(1)
