import time
import serial

ser=serial.Serial(

	port='/dev/ttyUSB0',
	baudrate=9600,
	parity=serial.PARITY_NONE,
	stopbits=serial.STOPBITS_ONE,
	bytesize=serial.EIGHTBITS,
	timeout=1
)
counter="@"
ser.flushInput()
ser.flushOutput()

while True:
	ser.write(counter)
	data_raw = ser.readline()
  	print(data_raw)
	time.sleep(1)
	ser.close
