#include <LiquidCrystal.h>
//khai bao man hinh lcd
//pin RW == GND ***Always**
const int pin_RS =2;//PD2
const int pin_EN = 3;//PD3
const int pin_d4 = 4;//PD4
const int pin_d5 = 5;//PD5
const int pin_d6 = 6;//PD6
const int pin_d7 = 7;//PD7
LiquidCrystal lcd(pin_RS,pin_EN,pin_d4,pin_d5,pin_d6,pin_d7);
//khai bao bien
int i;
int analogPin = A0; //Doc du lieu cho ADC
int val = 0;  
float temp;
// ---------------------------------------------------------------
void setup() {
 // khoi tao lcd
 lcd.begin(16,2);  /* Initialize 16x2 LCD */
 lcd.clear();  /* Clear the LCD */
}
// ---------------------------------------------------------------
// ham hien thi ngay gio phu vi khong the tinh toan tren DateTime duoc
void Display()
{
  String S_character="N.do: ";
  String value =  String(temp, 1); //lam tron 3 chu so thap phan 
  S_character = S_character + value + char(223) + "C";
  lcd.print(S_character);
  delay(500);
  lcd.clear();
}


// ---------------------------------------------------------------
void loop() 
{
  val = analogRead(analogPin);  // read the input pin
  float voltage = (float)val * 5.0 / 1024.0;
  temp = voltage * 100.0;
  Display();
}
