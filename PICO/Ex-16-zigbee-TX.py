import machine
import time

# UART setup (adjust pins and baud rate as needed)
uart = machine.UART(0, baudrate=9600, tx=machine.Pin(0), rx=machine.Pin(1))

while True:
    data_to_send = "Hello, ZigBee!"
    uart.write(data_to_send.encode('utf-8'))
    time.sleep(1)
