# NTU_Project2021
## Install pyserial:
###### sudo apt install python-pip
###### pip install pyserial

## Check USB Port
ls -l /dev/ttyUSB0

## Permit ttyUSB0
sudo chown dthinh /dev/ttyUSB0

## Disable all programs are running on USB0
### ps ax
find and kill PID process

## Run script to get data
python savedata.py

## Install Apache:
##### sudo apt-get install lamp-server^
##### sudo apt-get install apache2
##### sudo /etc/init.d/apache2 restart

##### http://localhost/

## Permit user add files or folders in www folder
chmod 755 -R ../../var/www/

A simple and efficient Json library for embedded C++ namely ArduinoJson version 5.11.2 was developed by Benoit Blanchon need to be installed on Arduino IDE Platform, it used to write program for Arduino master which communicated with Raspberry pi. This is library for json format transmission between Arduino device and computer via comport.
