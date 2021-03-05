import time
from datetime import datetime
import serial
import csv

ser=serial.Serial(

	port='/dev/ttyUSB0',
	baudrate=9600,
	parity=serial.PARITY_NONE,
	stopbits=serial.STOPBITS_ONE,
	bytesize=serial.EIGHTBITS,
	timeout=1
)
#file name:
f = open("dataFile.txt","a")

counter="@"
ser.flushInput()
ser.flushOutput()

dt_string=""
ti_string=""

#Loop:

while True:
	try:
		ser.write(counter)
		data_raw = ser.readline()
	#Save to csv file
		#with open("test_data.csv","a") as f:
            	#writer = csv.writer(f,delimiter=',')
            	#writer.writerow([time.time(),data_raw])
	#Adding time stamp to file
		if (data_raw=="},\r\n"):
			now = datetime.now()
			dt_string = now.strftime("%x")
			ti_string = now.strftime("%X")
			print("  "+'"Date"'+":"+'"'+dt_string+'"'+"\n")
			print("  "+'"Time"'+":"+'"'+ti_string+'"'+"\n")
			#f.write('"Time:"'+","+ti_string)
			f.write("  "+'"Date"'+":"+'"'+dt_string+'"'+",\n"+"  "+'"Time"'+":"+'"'+ti_string+'"'+"\n")
                	f.close()
			f = open("dataFile.txt","a")
			time.sleep(1)#1 second for reading data again

	#Save to json file
		f.write(data_raw)
    		f.close()
    		f = open("dataFile.txt","a")

	#Hien thi ra terminal
		print(data_raw)
		#time.sleep(1)
		ser.close

	except:
		print("Keyboard Interrupt")
        	break
