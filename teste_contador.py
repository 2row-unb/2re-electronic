contador = 0
contador1 = 0
 
import RPi.GPIO as GPIO
import time

GPIO.setwarnings(False) 
GPIO.setmode(GPIO.BOARD)
 
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

#Apaga todos os reles - Modulo 1
GPIO.output(37,1)
GPIO.output(35,1)
GPIO.output(33,1)
GPIO.output(31,1)
#Apaga todos os reles - Modulo 2
GPIO.output(40,1)
GPIO.output(38,1)
GPIO.output(36,1)
GPIO.output(32,1)

 
while(1):
    #Verifica se o botao foi pressionado
    if GPIO.input(18) == True:
        #Incrementa a variavel contador
        contador = contador +1
        time.sleep(0.5)
        #Caso contador = 1, acende o rele 1
        if contador == 1:
           GPIO.output(37, 0)
	   GPIO.output(32, 0)
        #Caso contador = 2, acende o rele 2
        if contador == 2:
	   GPIO.output(37, 1)
	   GPIO.output(32, 1)
           GPIO.output(35, 0)
           GPIO.output(36, 0)
        #Caso contador = 3, acende o rele 3
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
        #Caso contador = 1, acende o led vermelho
        if contador == 1:
           GPIO.output(37, 1)
           GPIO.output(32, 1)
	   contador = 0
        #Caso contador = 2, acende o led verde
        if contador == 2:
           GPIO.output(35, 1)
	   GPIO.output(36, 1)
	   GPIO.output(37, 0)
           GPIO.output(32, 0)
	   contador = 1
        #Caso contador = 3, acende o led amarelo
        if contador == 3:
           GPIO.output(33, 1)
           GPIO.output(38, 1)
	   GPIO.output(35, 0)
           GPIO.output(36, 0)
	   contador = 2
        #Caso contador = 2, acende o led verde
        if contador == 4:
           GPIO.output(31, 1)
	   GPIO.output(40, 1)
	   GPIO.output(33, 0)
           GPIO.output(38, 0)
	   contador = 3


    


