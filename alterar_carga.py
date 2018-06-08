"""
2re-electronic: Codigo para alterar cargas.

"""

import logging
import gabby

import GPIO


class Controller(gabby.Gabby):
    """
    Class to controll the system of weigth and receiver messages to
    the transmitter module
    """
    def transform(self, message):       
    	if message.belongs_to('transmitter_kernel'):
       		logging.info(f'Received message from transmitter: {message.data}')

	    	button_data = message.data
	   
  		self.Controller_weigth(button_data)          


    def Controller_weigth(self,button_data):

	indice = button_data[0]
        #button_decr = button_data[1]
        reset = button_data[1]
        
	#Define os pinos dos reles como saida- Modulo 1
        GPIO.setup(37, GPIO.OUT)
        GPIO.setup(35, GPIO.OUT)
        GPIO.setup(33, GPIO.OUT)
        GPIO.setup(31, GPIO.OUT)
        #Define os pinos dos reles como saida - Modulo 2
        GPIO.setup(40, GPIO.OUT)
        GPIO.setup(38, GPIO.OUT)
        GPIO.setup(36, GPIO.OUT)
        GPIO.setup(32, GPIO.OUT) 
	
	#Inicio-todos os reles desligados - Modulo 1
        GPIO.output(37,1)
        GPIO.output(35,1)
        GPIO.output(33,1)
        GPIO.output(31,1)
        #Inicio- todos os reles desligados - Modulo 2
        GPIO.output(40,1)
        GPIO.output(38,1)
        GPIO.output(36,1)
        GPIO.output(32,1)
	
	#Colocar aqui parte do código que indica botão Plus_click
	if indice  == 1:

		GPIO.output(35,1)
                GPIO.output(33,1)
                GPIO.output(31,1)

        	GPIO.output(37,0)
	       	#GPIO.output(32,0)

       	if indice == 2:

	       	GPIO.output(37,1)
        	GPIO.output(33,1)
        	GPIO.output(31,1)

	       	#GPIO.output(32, 1)
           	GPIO.output(35, 0)
           	#GPIO.output(36, 0)

       	if indice == 3:

		GPIO.output(37,1)
        	GPIO.output(35,1)
        	GPIO.output(31,1)

           	#GPIO.output(36, 1)  
           	GPIO.output(33, 0)
           	#GPIO.output(38, 0)
		
       	if indice == 4:

		GPIO.output(37,1)
        	GPIO.output(35,1)
        	GPIO.output(33,1)

           	#GPIO.output( 38, 1)
           	GPIO.output(31,0)
           	#GPIO.output(40,0)

       	if indice > 4:
		indice = 1
			

return []
