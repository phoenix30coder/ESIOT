import dht
import machine as gpio
import utime as TM

# Define the DHT11 sensor pin (change to your GPIO pin)
dht11_pin = gpio.Pin(15)

# Create a unique variable name to store DHT11 data
dht11_data = dht.DHT11(dht11_pin)

# Function to read and print DHT11 sensor data
def read_dht11_data():
    for _ in range(3):  # Retry 3 times
        try:
            dht11_data.measure()  # Measure temperature and humidity
            temperature = dht11_data.temperature()
            humidity = dht11_data.humidity()
            print("Temperature: {:.2f}°C".format(temperature))
            print("Humidity: {:.2f}%".format(humidity))
            return  # If successful, exit the loop
        except OSError as e:
            print("Error reading DHT11:", e)
            TM.sleep(2)  # Add a delay before retrying

# Main loop
while True:
    read_dht11_data()
    TM.sleep(2)  # Add a delay between readings

