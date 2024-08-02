import machine as gpio
import time


# Create a UART object (baud rate 9600, UART1 by default)
uart = gpio.UART(1, baudrate=9600, tx=gpio.Pin(4), rx=gpio.Pin(5)) # Use the appropriate UART pins


# Define the GPIO pins for the ultrasonic sensor & relay

trigger_pin = gpio.Pin(14, gpio.Pin.OUT)
echo_pin = gpio.Pin(15, gpio.Pin.IN)
relay_pin= gpio.Pin(9, gpio.Pin.OUT)

# Initialize variables
inputString = ""
stringComplete = False

old_time = time.ticks_ms()
uplink_interval = 30000
get_LA66_data_status = False
network_joined_status = False
#ULT


# Define a unique variable name to store the distance
distance_cm = 0


# Function to read the LM35 temperature sensor
def sensor_read():
    # Send a 10us trigger pulse to start the measurement
    trigger_pin.value(1)
    time.sleep_us(10)
    trigger_pin.value(0)
    
    # Wait for the echo pin to go high
    while echo_pin.value() == 0:
        pass
    
    start_time = time.ticks_us()
    
    # Wait for the echo pin to go low
    while echo_pin.value() == 1:
        pass
    
    end_time = time.ticks_us()
    
    # Calculate the duration of the pulse and convert it to distance (cm)
    pulse_duration = time.ticks_diff(end_time, start_time)
    distance_cm = (pulse_duration / 2) / 29.1  # Speed of sound in air at 20°C is approximately 343 m/s

    String_convo = "{:.2f}".format(distance_cm)
    Dist = float(String_convo)
    Temp = int(Dist * 100)
    print("DIstance in CM:", Dist)
    return Temp
print("Starts")
uart.write("ATZ \r\n")
# Main loop
while True:
    new_time = time.ticks_ms()

    if new_time - old_time >= uplink_interval: 
        old_time = new_time
        get_LA66_data_status = False
        Temp = sensor_read()
        uart.write("AT+SENDB=0,2,2,{:04X}\r\n".format(Temp))  # Send payload in HEX format

    if uart.any():
        rx_data = uart.readline().decode().strip()
        print(rx_data)
        if rx_data.startswith("1:"):
            if rx_data[3]=='1':
                print("LED_ON")
                relay_pin.value(1)
            if rx_data[3]=='2':
                print("LED_OFF")   
                relay_pin.value(1)                
        if rx_data.startswith("JOINED"):
            network_joined_status = True

        if rx_data.startswith("Dragino LA66 Device"):
            network_joined_status = False

        if rx_data.startswith("Run AT+RECVB=? to see detail"):
            get_LA66_data_status = True
            uart.write("AT+RECVB=?\r\n")  # Request configuration

    time.sleep_ms(100)  # Add a small delay to prevent busy-waiting


