import RPi.GPIO as GPIO
import sys
import termios
import tty
import select
import time

GPIO.setmode(GPIO.BOARD)

Motor1A = 16
Motor1B = 18
Motor1E = 22

Motor2A = 19
Motor2B = 21
Motor2E = 23
	
GPIO.setup(Motor1A,GPIO.OUT)
GPIO.setup(Motor1B,GPIO.OUT)
GPIO.setup(Motor1E,GPIO.OUT)
GPIO.setup(Motor2A,GPIO.OUT)
GPIO.setup(Motor2B,GPIO.OUT)
GPIO.setup(Motor2E,GPIO.OUT)

filename = str(sys.argv[1])
imglog = open(filename, 'r')

def drive(i):
	# first determine motor direction
	if i<=3:
		GPIO.output(Motor1A,GPIO.LOW)
		GPIO.output(Motor1B,GPIO.HIGH)
		GPIO.output(Motor2A,GPIO.HIGH)
		GPIO.output(Motor2B,GPIO.LOW)
	if i>=7:
		GPIO.output(Motor1A,GPIO.HIGH)
		GPIO.output(Motor1B,GPIO.LOW)
		GPIO.output(Motor2A,GPIO.LOW)
		GPIO.output(Motor2B,GPIO.HIGH)
	if i==4:
		GPIO.output(Motor1A,GPIO.LOW)
		GPIO.output(Motor1B,GPIO.HIGH)
		GPIO.output(Motor2A,GPIO.LOW)
		GPIO.output(Motor2B,GPIO.HIGH)
	if i==6:			
		GPIO.output(Motor1A,GPIO.HIGH)
		GPIO.output(Motor1B,GPIO.LOW)
		GPIO.output(Motor2A,GPIO.HIGH)
		GPIO.output(Motor2B,GPIO.LOW)
	# then determine motor enable
	if i in [1,2,4,6,7,8]:
		GPIO.output(Motor1E,GPIO.HIGH)
	else:
		GPIO.output(Motor1E,GPIO.LOW)
	if i in [3,2,4,6,9,8]:
		GPIO.output(Motor2E,GPIO.HIGH)
	else:
		GPIO.output(Motor2E,GPIO.LOW)
	return
			
def do_mission(status, missiontime):
	
	print "mission: status " + str(status) + "for " + str(missiontime) + "/100 seconds"
	
	#start timer
	timer_start = time.clock() * 100
	drive(status)
	#wait for timer to run out
	while (time.clock() * 100) - timer_start < missiontime:
		print str((time.clock() * 100) - timer_start)
	return

print "Rerunning script from file: "+filename

while True:
	mission=imglog.readline()
	if not mission: break

	# status definition:
	#   L   R
	#   1 2 3 Forward
	#   4 5 6 
	#   7 8 9 Backward
	# (5 = full stop)
	
	missionarray = mission.split(':')
	do_mission(int(missionarray[0]),float(missionarray[1].rstrip('\n')))

GPIO.cleanup()
imglog.close()

