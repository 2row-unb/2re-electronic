import RPi.GPIO as GPIO
import time
import math

GPIO.setwarnings(False) 
GPIO.setmode(GPIO.BOARD)

#def get_buttons(self):
button_incr = 0
button_decr = 0
button_reset = 0
indice = 0
	
#Define o pino do botao como entrada
GPIO.setup(18, GPIO.IN)
GPIO.setup(11, GPIO.IN)
GPIO.setup(12, GPIO.IN)
        

while(1):

    	if GPIO.input(18) == True:
        	time.sleep(0.3)
		indice += 1
		    
	if GPIO.input(11) == True:
		time.sleep(0.3)
        	indice -= 1
		    
	if GPIO.input(12) == True:
		button_reset = 1
        	
        
#	return [indice, button_reset]"
	print "inidice:" +str(indice)
	print "reset:" +str(button_reset)
time.sleep(1)
