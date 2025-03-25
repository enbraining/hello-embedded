import RPi.GPIO as GPIO
import time

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(16, GPIO.OUT, initial = GPIO.LOW)
GPIO.setup(20, GPIO.OUT, initial = GPIO.LOW)
GPIO.setup(21, GPIO.OUT, initial = GPIO.LOW)

while True:
    GPIO.output(21, GPIO.LOW)
    GPIO.output(16, GPIO.HIGH)
    GPIO.output(20, GPIO.HIGH)
    time.sleep(1)
    GPIO.output(18, GPIO.LOW)
    GPIO.output(20, GPIO.LOW)
    time.sleep(1)
    GPIO.output(21, GPIO.HIGH)
    time.sleep(1)

GPIO.cleanup()
