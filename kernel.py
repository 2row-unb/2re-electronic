"""
Kernel module is responsible to handle IMUs and Strain Gage
"""

import gabby
import logging
import RPi.GPIO as GPIO
import time
import math


GPIO.setwarnings(False) 
GPIO.setmode(GPIO.BOARD)


indice = 0

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
    	#time.sleep()

	tx= time.time()

	get_time()

	ty  = time.time() - tx

	#print ty
	
        return ty


    def get_buttons(self):
        button_reset = 0
	
        #Define o pino do botao como entrada
        GPIO.setup(18, GPIO.IN)
        GPIO.setup(11, GPIO.IN)
        GPIO.setup(12, GPIO.IN)
        
    	if GPIO.input(18) == True:
        	time.sleep(0.3)
		indice += 1
		    
	if GPIO.input(11) == True:
		time.sleep(0.3)
        	indice -= 1
		    
	if GPIO.input(12) == True:
		button_reset = 1
        	
        
	#return [indice, button_reset]"
	#print "inidice:" +str(indice)
	#print "reset:" +str(button_reset)
	#time.sleep(1)
			
        return [indice, button_reset]


    def get_weight(self):
	#Definindo os pinos da celula de carga 1:
	DAT =15
	CLK=16
	#Definindo os pinos da celula de carga 2:
	DAT2 = 13
	CLK2 = 8
	#Contadores das celulas 1 e 2, respectivamente:
	num=0
	num2=0
	#Definindo pinos como saida:
	gpio.setup(CLK, gpio.OUT)
	gpio.setup(CLK2,gpio.OUT)
	#Funcao da leitura da celula de carga 2:
	def weight2():
  		i=0
  		num2=0
  		gpio.setup(DAT2, gpio.OUT)
  		gpio.output(DAT2,1)
  		gpio.output(CLK2,0)
  		gpio.setup(DAT2, gpio.IN)

  		while gpio.input(DAT2) == 1:
      			i=0
  		for i in range(24):
        		gpio.output(CLK2,1)
        		num2 = num2<<1
			
        		gpio.output(CLK2,0)
        		if gpio.input(DAT2) == 0:
            			num2 = num2 + 1
  		gpio.output(CLK2,1)
 		
  		num2 = num2^0x800000
  		gpio.output(CLK2,0)
  		wei2 = 0
  		wei2 = ((num2)/1406)
 
  		PESO2=(((wei2-5943)/15))
  		print PESO2,"kg"
  		time.sleep(0.5)

        #Funcao da leitura da celula de carga 1:
	def weight():
  		i=0
  		num=0
  		gpio.setup(DAT, gpio.OUT)
  		gpio.output(DAT,1)
  		gpio.output(CLK,0)
  		gpio.setup(DAT, gpio.IN)

  		while gpio.input(DAT) == 1:
      			i=0
  		for i in range(24):
        		gpio.output(CLK,1)
        		num = num<<1

        		gpio.output(CLK,0)

        	if gpio.input(DAT) == 0:
            		num=num+1
			gpio.output(CLK,1)
 
  			num=num^0x800000
 
  		gpio.output(CLK,0)
  		wei = 0
  		wei = ((num)/1406)
  			
  
  		PESO=(((wei-5943)/15))
  		print PESO,"kg"
  		time.sleep(0.5)
 	
	#Verificar local certo de colocar essa conta
	P_medio = 0
	P_medio = PESO2 + PESO
	F = 0
	angle = 45
	F = P_medio*9.81*0.7071
	#calculo da energia
	#verificar t como variável global
	Pot_final = 0
	Pot_final = E/t 
	
        return F

      
    def get_carga()

	#Verifica quantas vezes o botao foi acionado
       
	
   	return xxx
