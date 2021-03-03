#include<SPI.h>
#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal.h>

//A4=SDA <-> SCL=RTC
//A5=SCL <-> SDA=RTC


//khai bao bien
String buf="";
volatile int pos;
volatile bool active;

//Khai bao bien cho Thoi gian
String ngaythang="";
String giophut="";

// doi tuong dong ho
RTC_DS1307 rtc;


void setup()
{
  // Truyen du lieu den Master
  pinMode(MISO, OUTPUT);

  // Bat che do Slave
  SPCR |= bit(SPE);

  // Cho phep ngat
  SPCR |= bit(SPIE);

//  Serial.begin (9600);
//  Serial.println ("Starting");

// khoi tao dong ho
 if (! rtc.begin()) {
   //lcd.print("Khong tim thay RTC");
   
  while (1);
 }
 if (! rtc.isrunning()) {
    //lcd.clear();
    //lcd.print("RTC chua dat thoi gian");
    
   //Chi lam 1 lan khi khoi tao;
   // Dat ngay gio dong ho theo hien tai cua may tinh
   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
   
   // ta cung co the dat theo y muon theo vd ben duoi
   // vi du thang 1 ngay 21, nam 2020 gio 3am
   // rtc.adjust(DateTime(2020, 1, 21, 3, 0, 0));
 } 

 //Serial.begin (9600);
 
}


// SPI interrupt routine
ISR (SPI_STC_vect)
{
  byte c = SPDR;

  if (c == 5)  //nhan duoc tin hieu tu Master de yeu cau truyen data (byte =5)
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

//Serial.println(ngaythang);
//Serial.println(giophut);
//delay(1000);
}

void loop ()
{
  DateTime now = rtc.now();
  showtime(now);
  buf=ngaythang+"/"+giophut;
  //Serial.print ("Thoi gian: ");
  //Serial.println (buf);
  //delay(1000);
}
