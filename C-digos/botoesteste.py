def get_buttons(self):
        
        #Verifica quantas vezes o botao foi acionado
        #contador = 0
	button _incr = 0
	button_decr = 0
	button_reset = 0
  	indice = 0
	
        #Define o pino do botao como entrada
        GPIO.setup(18, GPIO.IN)
        GPIO.setup(11, GPIO.IN)
        GPIO.setup(17, GPIO.IN)
        

    	if GPIO.input(18) == True:
        time.sleep(0.3)
		    indice += 1
		    
      if GPIO.input(11) == True:
		    time.sleep(0.3)
        indice -= 1
		    
       if GPIO.input(17) == True:
		    button_reset = 1
        	
        
        return [indice, button_reset]
