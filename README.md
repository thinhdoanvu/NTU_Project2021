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
