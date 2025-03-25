import RPi.GPIO as GPIO
import time

PIN0 = 17
PIN1 = 18
PIN2 = 27
PIN3 = 22

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

# output
GPIO.setup(PIN0, GPIO.OUT, initial = GPIO.LOW)
GPIO.setup(PIN1, GPIO.OUT, initial = GPIO.LOW)
GPIO.setup(PIN2, GPIO.OUT, initial = GPIO.LOW)

# input
GPIO.setup(PIN3, GPIO.IN)

while True:
    if GPIO.input(PIN3) == 1:
        GPIO.output(PIN0, True)
    else:
        GPIO.output(PIN0, False)

GPIO.cleanup()
