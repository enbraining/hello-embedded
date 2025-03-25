import RPi.GPIO as GPIO
import time

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(17, GPIO.OUT, initial = GPIO.LOW)
GPIO.setup(18, GPIO.OUT, initial = GPIO.LOW)
GPIO.setup(27, GPIO.OUT, initial = GPIO.LOW)

x = [17, 18, 27]

while True:
    for i in x:
        for k in range(0, 2):
            GPIO.output(i, k^1)
            time.sleep(0.5)

GPIO.cleanup()
