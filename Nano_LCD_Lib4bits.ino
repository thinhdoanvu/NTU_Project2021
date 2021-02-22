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
// ---------------------------------------------------------------
void setup() {
 // khoi tao lcd
 lcd.begin(16,2);  /* Initialize 16x2 LCD */
 lcd.clear();  /* Clear the LCD */
}
// ---------------------------------------------------------------
// ham hien thi ngay gio phu vi khong the tinh toan tren DateTime duoc
void display(int a){
  lcd.setCursor(0,0);
  lcd.print("0");
  lcd.print(a);
}
// ---------------------------------------------------------------
void loop() {
 lcd.setCursor(0, 0);                            // set the cursor to column 0, line1
lcd.print("Welcome to   ");               //print name
lcd.setCursor(0, 1);                            // set the cursor to column 0, line 2
lcd.print("github.com/thinhdoanvu/Arduino ");  //print name
delay(750);                                         //delay of 0.75sec
lcd.scrollDisplayLeft();                     //shifting data on LCD

}
