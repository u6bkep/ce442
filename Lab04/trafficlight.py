import time
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)

GPIO.setup(11, GPIO.OUT)#Green
GPIO.setup(13, GPIO.OUT)#Yellow
GPIO.setup(15, GPIO.OUT)#Red

GPIO.setup(16, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)#button

while(1):
    GPIO.output(11,False)
    GPIO.output(13,False)
    GPIO.output(15,False)
    if GPIO.input(16) == GPIO.HIGH:
        GPIO.output(11,False)
        GPIO.output(13,False)
        GPIO.output(15,True)
        time.sleep(1)
        GPIO.output(15,False)
        time.sleep(1)
    else:
        GPIO.output(13,False)
        GPIO.output(15,False)

        GPIO.output(11,True)
        time.sleep(4)

        GPIO.output(13,True)
        GPIO.output(11,False)
        time.sleep(1)

        GPIO.output(15,True)
        GPIO.output(13,False)
        time.sleep(4)
