import RPi.GPIO as GPIO
import curses
import sys
import termios
import tty
import select
import time
from time import sleep
from curses import wrapper

def main(stdscr):
	stdscr = curses.initscr()
	curses.cbreak()
	#stdscr.keypad(1)

	GPIO.setmode(GPIO.BOARD)

	Motor1A = 16
	Motor1B = 18
	Motor1E = 22

	Motor2A = 19
	Motor2B = 21
	Motor2E = 23
	
	sw_backL = 11
	sw_backR = 13
	sw_frontL = 40
	sw_frontR = 38

	eye_L = 37
	eye_R = 35 

	GPIO.setup(Motor1A,GPIO.OUT)
	GPIO.setup(Motor1B,GPIO.OUT)
	GPIO.setup(Motor1E,GPIO.OUT)
	GPIO.setup(Motor2A,GPIO.OUT)
	GPIO.setup(Motor2B,GPIO.OUT)
	GPIO.setup(Motor2E,GPIO.OUT)

	GPIO.setup(sw_backL,GPIO.IN)
	GPIO.setup(sw_backR,GPIO.IN)	
	GPIO.setup(sw_frontL,GPIO.IN)
	GPIO.setup(sw_frontR,GPIO.IN)

	GPIO.setup(eye_L,GPIO.IN)
	GPIO.setup(eye_R,GPIO.IN)

	imglog = open('imglog', 'w')

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
			
	class NonBlockingConsole(object):

    		def __enter__(self):
       			self.old_settings = termios.tcgetattr(sys.stdin)
        		tty.setcbreak(sys.stdin.fileno())
        		return self

    		def __exit__(self, type, value, traceback):
        		termios.tcsetattr(sys.stdin, termios.TCSADRAIN, self.old_settings)

    		def get_data(self):
        		if select.select([sys.stdin], [], [], 0) == ([sys.stdin], [], []):
            			return sys.stdin.read(1)
        		return False

	with NonBlockingConsole() as nbc:
		stdscr.addstr(0,0,"Hit 'ESC' to quit -- yui hjk bnm as numpad -- space = stop")
		stdscr.addstr(3,5, "  ___   ___  ")
		stdscr.addstr(4,5, " /.00...00.\ ")
		stdscr.addstr(5,5, "  .       .  ")
		stdscr.addstr(6,5, "  .       .  ")
		stdscr.addstr(7,5, "  .   x   .  ")
		stdscr.addstr(8,5, "  .       .  ")
		stdscr.addstr(9,5, "  .       .  ")
		stdscr.addstr(10,5,"  .........  ")
		stdscr.addstr(11,5," \__     __/ ")
		stdscr.refresh()

		status = 5
		timestamp = 0

    		while 1: # main loop

			newstatus = 0

			# status definition:
			#   L   R
			#   1 2 3 Forward
			#   4 5 6 
			#   7 8 9 Backward
			# (5 = full stop)

			key = nbc.get_data() # get key

        		if key == '\x1b':  # x1b is ESC
            			break
			if key == 'y':
				newstatus = 1
			if key == 'u':
				newstatus = 2
			if key == 'i':
				newstatus = 3
			if key == 'h':
				newstatus = 4
			if key == 'j':
				newstatus = 5
			if key == 'k':
				newstatus = 6
			if key == 'b':
				newstatus = 7
			if key == 'n':
				newstatus = 8
			if key == 'm':
				newstatus = 9
			if key == ' ':
				newstatus = 5

			if GPIO.input(sw_frontR):
				stdscr.addstr(3, 13, "XXX")
				if status in [1,2,3]:
					newstatus = 5
			else:
				stdscr.addstr(3, 13, "___")

			if GPIO.input(sw_frontL):
				stdscr.addstr(3, 7, "XXX")
				if status in [1,2,3]:
					newstatus = 5
			else:
				stdscr.addstr(3, 7, "___")

			if GPIO.input(sw_backL):
				stdscr.addstr(11, 7, "XXX")
				if status in [7,8,9]:
					newstatus = 5
			else:
				stdscr.addstr(11, 7, "___")

			if GPIO.input(sw_backR):
				stdscr.addstr(11, 13, "XXX")
				if status in [7,8,9]:
					newstatus = 5
			else:
				stdscr.addstr(11, 13, "___")

			if not GPIO.input(eye_R):
				stdscr.addstr(4, 13, "XX")
			else:
				stdscr.addstr(4, 13, "00")
				
			if not GPIO.input(eye_L):
				stdscr.addstr(4, 8, "XX")
			else:
				stdscr.addstr(4, 8, "00")

			if (newstatus > 0):
				if (newstatus <> status):
					# status update!
					drive(newstatus)
					newtime = time.clock()*100
					timelapse = newtime - timestamp
					imglog.write(str(status) + ':' + str(timelapse) + '\n')
					status = newstatus
					timestamp = newtime
			stdscr.refresh()

		curses.endwin()

		GPIO.cleanup()
		imglog.close()

wrapper(main)
