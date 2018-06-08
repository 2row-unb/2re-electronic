"""
Kernel module is responsible to handle IMUs and Strain Gage
"""

import gabby
import logging
import RPi.GPIO as GPIO
import time

GPIO.setwarnings(False) 
GPIO.setmode(GPIO.BOARD)


class Kernel(gabby.Gabby):
    def transform(self, message):
        logging.debug(
            f"Received message, data: {message.payload.decode('utf-8')}")
        imu_data = [float(x) for x in
                    message.payload.decode('utf-8').split(';')]

        buttons_info = self.get_buttons()
        weight_info = self.get_weight()
        time_info = self.get_time()

        data = [*imu_data, time_info, *buttons_info, weight_info]
        return [gabby.Message(data, self.output_topics)]

    def get_time(self):
        return 12938712983712.12

    def get_buttons(self):
        
        #Verifica quantas vezes o botao foi acionado
        contador = 0
        contador1 = 0
        
        #Define os pinos dos reles como saida - Modulo 1
        GPIO.setup(37, GPIO.OUT)
        GPIO.setup(35, GPIO.OUT)
        GPIO.setup(33, GPIO.OUT)
        GPIO.setup(31, GPIO.OUT)
        #Define os pinos dos reles como saida - Modulo 2
        GPIO.setup(40, GPIO.OUT)
        GPIO.setup(38, GPIO.OUT)
        GPIO.setup(36, GPIO.OUT)
        GPIO.setup(32, GPIO.OUT) 
        #Define o pino do botao como entrada
        GPIO.setup(18, GPIO.IN)
        GPIO.setup(11, GPIO.IN)
        GPIO.setup(, GPIO.IN)
        
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

    
    	if GPIO.input(18) == True:
        #Incrementa a variavel contador
        contador = contador +1
        time.sleep(0.5)
        	if contador == 1:
           		GPIO.output(37, 0)
	       		GPIO.output(32, 0)
        	 if contador == 2:
	       		GPIO.output(37, 1)
	       		GPIO.output(32, 1)
           		GPIO.output(35, 0)
           		GPIO.output(36, 0)
        	 if contador == 3:
	       		GPIO.output(35, 1)
           		GPIO.output(36, 1)  
           		GPIO.output(33, 0)
           		GPIO.output(38, 0)
        	  if contador == 4:
	       		GPIO.output( 33, 1)
           		GPIO.output( 38, 1)
           		GPIO.output( 31, 0)
           		GPIO.output( 40, 0)
       		  if contador > 4:
           		GPIO.output(31, 1)
	   		GPIO.output(40, 1)
	   		print('Por favor, escolha uma carga de 1 a 4')   
           		contador = 0

        if GPIO.input(11) == True:
        #Incrementa a variavel contador
        time.sleep(0.5)
		if contador == 0:
	        	print('Nao tem carga no equipamento')
              	if contador == 1:
                	GPIO.output(37, 1)
                	GPIO.output(32, 1)
	        	contador = 0  
            	if contador == 2:
                	GPIO.output(35, 1)
	        	GPIO.output(36, 1)
	        	GPIO.output(37, 0)
                	GPIO.output(32, 0)
	        	contador = 1
            	if contador == 3:
                	GPIO.output(33, 1)
                	GPIO.output(38, 1)
	        	GPIO.output(35, 0)
                	GPIO.output(36, 0)
	        	contador = 2
             	if contador == 4:
                	GPIO.output(31, 1)
	        	GPIO.output(40, 1)
	        	GPIO.output(33, 0)
                	GPIO.output(38, 0)
	        	contador = 3

        
        return [1.0, 0.0, 1.0]

    def get_weight(self):
        return 13255.0

   
