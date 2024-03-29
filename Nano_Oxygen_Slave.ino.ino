#include<SPI.h>

//khai bao bien
String buf="";
volatile int pos;
volatile bool active;

int analogPin = A0; //Doc du lieu cho ADC
int val = 0;  
float temp;

byte nguyen;
byte le;
String x;

void setup()
{
  // Truyen du lieu den Master
  pinMode(MISO, OUTPUT);

  // Bat che do Slave
  SPCR |= bit(SPE);

  // Cho phep ngat
  SPCR |= bit(SPIE);
}


// SPI interrupt routine
ISR (SPI_STC_vect)
{
  byte c = SPDR;

  if (c == 2)  //nhan duoc tin hieu tu Master de yeu cau truyen data
    {
      active = true;
      pos = 0;
      SPDR = buf [pos++];   // send first byte
      return;
    }
  if (!active)
    {
      SPDR = 0;
      return;
    }

  //Thanh ghi de truyen
  SPDR = buf [pos];
  if (buf [pos] == 0 || ++pos >= sizeof (buf)) //khong co du lieu hoac het bo dem
    active = false;
}


void loop ()
{
  val = analogRead(analogPin);  // read the input pin
  float voltage = (float)val * 5.0 / 1024.0;
  temp = voltage * 100.0;
  //nguyen
  nguyen = temp/1.0;
  //thap phan
  le = (temp - nguyen)*100;
  x = String (nguyen) + "." + String (le);
  buf=x;

}
