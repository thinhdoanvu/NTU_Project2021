//MASTER
#include <LiquidCrystal.h>
#include <SPI.h>

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
String x;
char buf[20];

// ---------------------------------------------------------------
void setup() {
 // Khoi tao lcd
 lcd.begin(16,2);  /* Initialize 16x2 LCD */
 lcd.clear();  /* Clear the LCD */
 
// Serial.begin (9600);
// Serial.println ("Starting");

 digitalWrite(SS, HIGH);  // Ngat ket noi den cac Slave
 SPI.begin ();

 // Chia tan so truyen
 SPI.setClockDivider(SPI_CLOCK_DIV8);
}

// ---------------------------------------------------------------
void Display()
{ 
  // set the cursor to column 0, line 0
  lcd.setCursor(0, 0);
  lcd.print("Arduino No.1: ");
  // set the cursor to column 0, line 1
  lcd.setCursor(0, 1);
  String S_character = x + char(223) + "C";
  lcd.print(S_character);
  delay(100);
  //lcd.clear();
}

// ---------------------------------------------------------------
void loop() 
{
  delay (300);  // Cho trong giay lat de ben Slave hoan tat xu ly roi moi yeu cau gui 

  //Gui du lieu den Slave
  digitalWrite(SS, LOW);    
  SPI.transfer (1); //Truyen byte co gia tri la 1 de Slave biet va bat dau truyen
  
  for (int pos = 0; pos < sizeof (buf) - 1; pos++)
    {
      delayMicroseconds (15);
      buf [pos] = SPI.transfer (0);
      if (buf [pos] == 0)
      {
        break;
      }
    }

  //buf [sizeof (buf) - 1] = 0;  // ensure terminating null

  // Ngat ket noi
  digitalWrite(SS, HIGH); //dung truyen va doi xu ly de hien thi da

//  Serial.print ("We received: ");
//  Serial.println (buf);
  
  x=buf; //ghi du lieu ra LCD
  Display();
  delay (100);  // 1 second delay 
}
