# main.py -- put your code here!

#runs vith qt application
#if the received serial string is correct turn on the led on pin x3

import array as arr
from pyb import *

l1 = pyb.Pin('X3', pyb.Pin.OUT)
usb = pyb.USB_VCP()

l1.low()
l2.low()

def serial_exe(buffer):
	buffer = str(buffer)
	if buffer.find('set l1 on') != -1:
		l1.value(1)
		usb.write("led1 on\r\n")
	else:
		if buffer.find('set l1 off') != -1:
			l1.value(0)
			usb.write("led1 off\r\n")

while True:
	if usb.any():
		rx_buffer = usb.readline()
		serial_exe(rx_buffer)
