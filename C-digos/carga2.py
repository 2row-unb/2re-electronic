import RPi.GPIO as gpio
import threading
import time
DAT =15
CLK=16
DAT2 = 13
CLK2 = 8
num=0
num2=0
gpio.setwarnings(False)
gpio.setmode(gpio.BOARD)
gpio.setup(CLK, gpio.OUT)
gpio.setup(CLK2,gpio.OUT)
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
        num2=num2<<1

        gpio.output(CLK2,0)
        if gpio.input(DAT2) == 0:
            num2=num2+1

  gpio.output(CLK2,1)
 # print num
  num2=num2^0x800000
 # print num
  gpio.output(CLK2,0)
  wei2=0
  wei2=((num2)/1406)


  PESO2=(((wei2-5943)/15))
  print PESO2,"kg"
  time.sleep(0.5)


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
        num=num<<1

        gpio.output(CLK,0)

        if gpio.input(DAT) == 0:
            num=num+1

  gpio.output(CLK,1)
 # print num
  num=num^0x800000
 # print num
  gpio.output(CLK,0)
  wei=0
  wei=((num)/1406)
  p=((num)/14.06)
  p1=p-59423
 # print p1
 # print p
  PN=(p-594261)
  N=PN/1.503
  quilo=N/1000
  PESO=(((wei-5943)/15))
  print PESO,"kg"
  time.sleep(0.5)
while True:
 weight()
 weight2()


