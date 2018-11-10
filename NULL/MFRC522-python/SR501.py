import RPi.GPIO as GPIO
import time
import datetime
from gpiozero import Buzzer
from subprocess import call
import pymysql
import threading

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
sensor = 23
led = 22
buzzer = Buzzer(17)

GPIO.setup(sensor, GPIO.IN)
GPIO.setup(led, GPIO.OUT)

print ("Waiting for sensor to settle")
time.sleep(0.5)
print ("Detecting motion")

db = pymysql.connect("117.16.19.184", "user", "test", "school")
cur = db.cursor()
chk=0

def loop():
    global chk
    while True:
       if GPIO.input(sensor):
           print ("Motion Detected")
           GPIO.output(led, True)
           # buzzer.on()
           chk=1
           time.sleep(0.5)
       else:
            print ("Detecting motion")
            GPIO.output(led, False)
            # buzzer.off()
            chk=0
            time.sleep(0.5)

t=threading.Thread(target=loop)
t.start()
while True:
    cur.execute("select * from Car")
    car_start = cur.fetchone()
    
    if car_start[3] == 0:
        cur.execute("select * from Drive")
        car_person = cur.fetchone()
        print(car_person[0])
        if car_person:
                time.sleep(5)
                if chk==1:
                    buzzer.on()
                elif chk==0:
                    buzzer.off()
        else :
            buzzer.off()
    else :
        buzzer.off()
t.join()
