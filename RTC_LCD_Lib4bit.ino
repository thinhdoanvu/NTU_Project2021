#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal.h>

//A4=SDA <-> SCL=RTC
//A5=SCL <-> SDA=RTC

//khai bao man hinh lcd
//pin RW == GND ***Always**
const int pin_RS =2;//PD2
const int pin_EN = 3;//PD3
const int pin_d4 = 4;//PD4
const int pin_d5 = 5;//PD5
const int pin_d6 = 6;//PD6
const int pin_d7 = 7;//PD7
LiquidCrystal lcd(pin_RS,pin_EN,pin_d4,pin_d5,pin_d6,pin_d7);

//Khai bao bien cho Thoi gian
String ngaythang="";
String giophut="";

// doi tuong dong ho
RTC_DS1307 rtc;

// ---------------------------------------------------------------
void setup() {

 // khoi tao lcd
 lcd.begin(16, 2);
 // khoi tao dong ho
 if (! rtc.begin()) {
   lcd.print("Khong tim thay RTC");
   
  while (1);
 }
 if (! rtc.isrunning()) {
    lcd.clear();
    lcd.print("RTC chua dat thoi gian");
    
   //Chi lam 1 lan khi khoi tao;
   // Dat ngay gio dong ho theo hien tai cua may tinh
   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
   
   // ta cung co the dat theo y muon theo vd ben duoi
   // vi du thang 1 ngay 21, nam 2020 gio 3am
   // rtc.adjust(DateTime(2020, 1, 21, 3, 0, 0));
 } 

 Serial.begin (9600);
 
}
// ---------------------------------------------------------------
void showtime(DateTime now){
  
  String ngay="";
   if(now.day()<=9)
   {
     ngay="0"+String(now.day())+"-";
   }
   else {
    ngay=String(now.day())+"-";
   }
   String thang="";
   if(now.month()<=9)
   {
     thang="0"+String(now.month())+"-";
   }
   else {
    thang=String(now.month())+"-";
   }
   String nam="";
   if(now.year()<=9)
   {
     nam="0"+String(now.year());
   }
   else {
    nam=String(now.year());
   }

//Tinh toan GIO:PHUT:GIAY 
  String gio="";
 if(now.hour()<=9)
   {
    gio="0"+String(now.hour())+":";
   }
   else {
    gio=String(now.hour())+":";
   }
   
   String phut="";
   if(now.minute()<=9)
   {
     phut="0"+String(now.minute())+":";
   }
   else {
     phut=String(now.minute())+":";
   }
   
   String giay="";
   if(now.second()<=9)
   {
     giay="0"+String(now.second());
   }
   else {
    giay=String(now.second());
   }

  ngaythang=ngay+thang+nam;
  giophut=gio+phut+giay;
  
    // hien thi ngay 
//    lcd.setCursor(0, 0);    
//    lcd.print(ngaythang);
//
//    // hien thi gio
//    lcd.setCursor(0, 1);
//    lcd.print(giophut);

Serial.println(ngaythang);
Serial.println(giophut);
delay(1000);
}

// ---------------------------------------------------------------
void loop() {
 DateTime now = rtc.now();
 showtime(now);
}
