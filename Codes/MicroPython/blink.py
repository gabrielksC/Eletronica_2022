from machine import Pin
import time

led = Pin(25, Pin.OUT)
led(1)

while True:
    print("Hello World!")
    time.sleep(1)


