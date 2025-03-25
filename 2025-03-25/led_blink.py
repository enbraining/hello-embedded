import RPi.GPIO as GPIO
import time

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(17, GPIO.OUT, initial = GPIO.LOW)
GPIO.setup(18, GPIO.OUT, initial = GPIO.LOW)
GPIO.setup(27, GPIO.OUT, initial = GPIO.LOW)

while True:
    GPIO.output(27, GPIO.LOW)
    GPIO.output(17, GPIO.HIGH)
    GPIO.output(18, GPIO.HIGH)
    time.sleep(1)
    GPIO.output(17, GPIO.LOW)
    GPIO.output(18, GPIO.LOW)
    time.sleep(1)
    GPIO.output(27, GPIO.HIGH)
    time.sleep(1)

GPIO.cleanup()
