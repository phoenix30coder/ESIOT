import machine as gpio
import utime as TM

# Define the GPIO pins for the ultrasonic sensor
trigger_pin = gpio.Pin(14, gpio.Pin.OUT)
echo_pin = gpio.Pin(15, gpio.Pin.IN)

# Define a unique variable name to store the distance
distance_cm = 0

# Function to measure the distance using the ultrasonic sensor
def measure_distance():
    # Send a 10us trigger pulse to start the measurement
    trigger_pin.value(1)
    TM.sleep_us(10)
    trigger_pin.value(0)
    
    # Wait for the echo pin to go high
    while echo_pin.value() == 0:
        pass
    
    start_time = TM.ticks_us()
    
    # Wait for the echo pin to go low
    while echo_pin.value() == 1:
        pass
    
    end_time = TM.ticks_us()
    
    # Calculate the duration of the pulse and convert it to distance (cm)
    pulse_duration = TM.ticks_diff(end_time, start_time)
    distance_cm = (pulse_duration / 2) / 29.1  # Speed of sound in air at 20°C is approximately 343 m/s

    return distance_cm

# Main loop
while True:
    distance_cm = measure_distance()
    print("Distance: {:.2f} cm".format(distance_cm))
    TM.sleep(1)  # Add a delay between measurements

