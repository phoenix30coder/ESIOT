import machine as gpio
import utime as TM 

# Define the ADC (Analog-to-Digital Converter) pin for the LM35 temperature sensor
lm35_pin = gpio.ADC(26)

# Define a unique variable name to store the temperature reading
temperature_celsius = 0.0

# Function to read and calculate the temperature from the LM35 sensor
def read_temperature():
    global temperature_celsius
    raw_value = lm35_pin.read_u16()  # Read the raw ADC value
    voltage = (raw_value / 65535) * 3.3  # Convert raw value to voltage (assuming 3.3V reference)
    temperature_celsius = (voltage ) * 100  # Calculate temperature in Celsius

# Main loop
while True:
    read_temperature()
    print("Temperature: {:.2f} °C".format(temperature_celsius))
    TM.sleep(1)  # Add a delay between readings
