#!/usr/bin/env python
#-*- coding: utf-8 -*-

import RPi.GPIO as GPIO 
import SimpleMFRC522
import time
import datetime
import pymysql

global id

def nfc_db():
	db = pymysql.connect("117.16.19.184", "user", "test", "school")
	cur = db.cursor()
	cur.execute("select * from Drive")
	nfc_cardNum = id
	i=0

	while True:
		cardNum = cur.fetchone()
		print(cardNum)
		print(i)
		i+=1
		if not cardNum: #nfc 키값이 DB에 없을때(탈때)
			cur.execute("select * from Car") # 차량넘버(d_number) 가져옴
			car = cur.fetchone()
			cur.execute("select * from Student") #반복문까지는 탑승하는 원생정보 Get
			while True:
                            child = cur.fetchone()
                            if not child:
                                cur.close()
                                db.close()
                                break
                            elif child[0] == str(nfc_cardNum):
                                #cur.execute("select s_name from Student where s_key=%s", (nfc_cardNum))
                                #child_name = cur.fetchall()
                                #print(car[0])
                                
                                cur.execute("insert into Drive(d_number, d_key, d_name, d_state, d_time) values(%s, %s, %s, %s, now())", (car[0], nfc_cardNum, child[1], 1))
                                cur.execute("select * from Car")
                                car_num = cur.fetchone()
                                cur.execute("select * from Student where s_key = (%s)", nfc_cardNum)
                                stu_temp = cur.fetchone()
                                cur.execute("insert into Log values(%s, %s, %s, %s, %s, %s, %s, now())",(car_num[0],car_num[1],car_num[2],stu_temp[0],stu_temp[1],stu_temp[2],1))
                                db.commit()
                                cur.close()
                                db.close()
                                break
                            
                                #print(car[0])
                        
                        break
		if str(cardNum[1]) == str(id): #같은 nfc 키값이 DB에 있을때(내릴때)
                        print('sadsad')
			cur.execute("delete from Drive where d_key = (%s)", nfc_cardNum)
			cur.execute("select * from Car")
			car_num = cur.fetchone()
			cur.execute("select * from Student where s_key = (%s)", nfc_cardNum)
			stu_temp = cur.fetchone()
			cur.execute("insert into Log values(%s, %s, %s, %s, %s, %s, %s, now())",(car_num[0],car_num[1],car_num[2],stu_temp[0],stu_temp[1],stu_temp[2],0))
			db.commit()
			cur.close()
			db.close()
			break
		

GPIO.setmode(GPIO.BCM)

led = 2
GPIO.setup(led, GPIO.OUT)

reader = SimpleMFRC522.SimpleMFRC522()
GPIO.output(led, False)

try:
	a = 0
	b = 0
	c = 0
	d = 0
	while True:
		id, text = reader.read()
		nfc_db()
                print(text)
		if id == 349359255111:
                    
			if a == 0:
				print(id)
				print(text)
				print("in")
				GPIO.output(led, True)
				s = datetime.datetime.now()
				print s
				a = 1
			else:
				print(id)
                                print(text)
				print("out")
				GPIO.output(led, True)
				a = 0
                                s = datetime.datetime.now()
                                print s
			time.sleep(3)
			GPIO.output(led, False)
		elif id == 486542421543:
			if b == 0:
				print(id)
				print(text)
				print("in")
				GPIO.output(led, True)
                                s = datetime.datetime.now()
                                print s
				b = 1
			else:
				print(id)
                                print(text)
				print("out")
				GPIO.output(led, True)
                                s = datetime.datetime.now()
                                print s
				b = 0
			time.sleep(3)
			GPIO.output(led, False)
		elif id == 358109425377:
			if c == 0:
				print(id)
				print(text)
				print("in")
				GPIO.output(led, True)
                                s = datetime.datetime.now()
                                print s
				c = 1
			else:
				print(id)
                                print(text)
				print("out")
				GPIO.output(led, True)
                                s = datetime.datetime.now()
                                print s
				c = 0
			time.sleep(3)
			GPIO.output(led, False)
		elif id == 350149357182:
			if d == 0:
				print(id)
				print(text)
				print("in")
				GPIO.output(led, True)
                                s = datetime.datetime.now()
                                print s
				d = 1
			else:
                                print(id)
                                print(text)
				print("out")
				GPIO.output(led, True)
                                s = datetime.datetime.now()
                                print s
				d = 0
			time.sleep(3)
			GPIO.output(led, False)	

finally:
	GPIO.cleanup()

