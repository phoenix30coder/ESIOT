import machine as gpio
import utime as TM

# Configure UART for communication with the HC-05 Bluetooth module
uart = gpio.UART(0, baudrate=9600, tx=gpio.Pin(0), rx=gpio.Pin(1))  # UART0, GPIO 0 (TX) and GPIO 1 (RX)

#Controlling pin configuration
Cntrl_Led=gpio.Pin(17, gpio.Pin.OUT)

def send_data(data):
    uart.write(data)
    TM.sleep_ms(100)  # Wait for data to be transmitted

def receive_data():
    if uart.any():
        return uart.read()
    return b''  # Return an empty byte string if no data is available



# Main loop to send and receive data
while True:
    # Send data to the HC-05 module
    data_to_send = "TEMPDATA\n"
    send_data(data_to_send.encode())
    print("Sent:", data_to_send.strip())

    # Receive data from the HC-05 module
    received_data = receive_data()
    if received_data:
        print("Received_Raw:", received_data)
        print("Received:", received_data.decode().strip())
    #Controlling Via Bluetooth    
    if("ON"==received_data.decode().strip()):
        Cntrl_Led.value(1)
        print("LED_ON")
    elif("OFF"==received_data.decode().strip()):
        Cntrl_Led.value(0)
        print("LED_OFF")
    
    TM.sleep(1)



