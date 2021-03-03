#include <SPI.h>
#include <LiquidCrystal.h>
#include <ArduinoJson.h>

#define SS0 A4 //NH3
#define SS1 A1 //ND
#define SS2 A2 //OD
#define SS3 A3 //pH
#define SS4 A5 //RTC

//khai bao bien
String nhietdo;
String oxyhoatan;
String ph;
String nh3;
String S_character;
String thoigian;
char buf[50];

//khai bao man hinh lcd
//pin RW == GND ***Always**
const int pin_RS =2;//PD2
const int pin_EN = 3;//PD3
const int pin_d4 = 4;//PD4
const int pin_d5 = 5;//PD5
const int pin_d6 = 6;//PD6
const int pin_d7 = 7;//PD7
LiquidCrystal lcd(pin_RS,pin_EN,pin_d4,pin_d5,pin_d6,pin_d7);

void setup()
{
  Serial.begin (9600);
  //Serial.println ("Starting");
  pinMode(SS0, OUTPUT);
  pinMode(SS1, OUTPUT);
  pinMode(SS2, OUTPUT);
  pinMode(SS3, OUTPUT);
  pinMode(SS4, OUTPUT);
  
  digitalWrite(SS0, HIGH);  // Ngat ket noi den cac Slave
  digitalWrite(SS1, HIGH);  // Ngat ket noi den cac Slave
  digitalWrite(SS2, HIGH);  // Ngat ket noi den cac Slave
  digitalWrite(SS3, HIGH);  // Ngat ket noi den cac Slave
  digitalWrite(SS4, HIGH);  // Ngat ket noi den cac Slave
  
  SPI.begin ();

  // Chia tan so truyen
  SPI.setClockDivider(SPI_CLOCK_DIV8);

  // Khoi tao lcd
  lcd.begin(16,2);  /* Initialize 16x2 LCD */
  lcd.clear();  /* Clear the LCD */
  
}

void NH3()
{
  delay (100);  // Cho trong giay lat de ben Slave hoan tat xu ly roi moi yeu cau gui 
  
  //Gui du lieu den Slave, doc gia tri do nhiet do
  digitalWrite(SS0, LOW); 
  delay(100);
  digitalWrite(SS1, HIGH); 
  digitalWrite(SS2, HIGH); 
  digitalWrite(SS3, HIGH); 
  digitalWrite(SS4, HIGH);
  
  SPI.transfer (4); //Truyen byte co gia tri la 0 de Slave NH3 biet va bat dau truyen
  
  for (int pos = 0; pos < sizeof (buf) - 1; pos++)
    {
      delayMicroseconds (15);
      buf [pos] = SPI.transfer (0);
      if (buf [pos] == 0)
      {
        break;
      }
    }

  buf [sizeof (buf) - 1] = 0;  // ensure terminating null

  // Ngat ket noi
  digitalWrite(SS0, HIGH);//dung truyen va doi xu ly de hien thi da
  digitalWrite(SS1, HIGH);  
  digitalWrite(SS2, HIGH);
  digitalWrite(SS3, HIGH); 
  digitalWrite(SS4, HIGH); 
  
  nh3=buf; //ghi du lieu ra LCD
}

void NhietDo()
{
  delay (100);  // Cho trong giay lat de ben Slave hoan tat xu ly roi moi yeu cau gui 

  //Gui du lieu den Slave, doc gia tri do nhiet do
  digitalWrite(SS1, LOW);  
  digitalWrite(SS0, HIGH);
  digitalWrite(SS2, HIGH); 
  digitalWrite(SS3, HIGH); 
  digitalWrite(SS4, HIGH); 
   
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

  buf [sizeof (buf) - 1] = 0;  // ensure terminating null

  // Ngat ket noi
  digitalWrite(SS0, HIGH); //dung truyen va doi xu ly de hien thi da 
  digitalWrite(SS1, HIGH);
  digitalWrite(SS2, HIGH);
  digitalWrite(SS3, HIGH);
  digitalWrite(SS4, HIGH); 
   
  nhietdo=buf; //ghi du lieu ra LCD
}

void OxyHoatan()
{
  delay (100);  // Cho trong giay lat de ben Slave hoan tat xu ly roi moi yeu cau gui 

  //Gui du lieu den Slave, doc gia tri do nhiet do
  digitalWrite(SS2, LOW);  
  digitalWrite(SS0, HIGH);
  digitalWrite(SS1, HIGH);
  digitalWrite(SS3, HIGH); 
  digitalWrite(SS4, HIGH);   
   
  SPI.transfer (2); //Truyen byte co gia tri la 2 de Slave biet va bat dau truyen
  
  for (int pos = 0; pos < sizeof (buf) - 1; pos++)
    {
      delayMicroseconds (15);
      buf [pos] = SPI.transfer (0);
      if (buf [pos] == 0)
      {
        break;
      }
    }

  buf [sizeof (buf) - 1] = 0;  // ensure terminating null

  // Ngat ket noi
  digitalWrite(SS0, HIGH); //dung truyen va doi xu ly de hien thi da 
  digitalWrite(SS1, HIGH); 
  digitalWrite(SS2, HIGH);
  digitalWrite(SS3, HIGH);  
  digitalWrite(SS4, HIGH); 
  
  oxyhoatan=buf; //ghi du lieu ra LCD
}

void PH()
{
  delay (100);  // Cho trong giay lat de ben Slave hoan tat xu ly roi moi yeu cau gui 

  //Gui du lieu den Slave, doc gia tri do nhiet do
  digitalWrite(SS3, LOW);
  digitalWrite(SS0, HIGH);  
  digitalWrite(SS1, HIGH);
  digitalWrite(SS2, HIGH); 
  digitalWrite(SS4, HIGH);   
   
  SPI.transfer (3); //Truyen byte co gia tri la 2 de Slave biet va bat dau truyen
  
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
  digitalWrite(SS0, HIGH); //dung truyen va doi xu ly de hien thi da  
  digitalWrite(SS1, HIGH);
  digitalWrite(SS2, HIGH);
  digitalWrite(SS3, HIGH);  
  digitalWrite(SS4, HIGH); 
  ph=buf; //ghi du lieu ra LCD
}

void RTC()
{
  delay (100);  // Cho trong giay lat de ben Slave hoan tat xu ly roi moi yeu cau gui 

  //Gui du lieu den Slave, doc gia tri do nhiet do
  digitalWrite(SS4, LOW);
  digitalWrite(SS0, HIGH);  
  digitalWrite(SS1, HIGH);
  digitalWrite(SS2, HIGH); 
  digitalWrite(SS3, HIGH);   
   
  SPI.transfer (5); //Truyen byte co gia tri la 5 de Slave biet va bat dau truyen
  
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
  digitalWrite(SS0, HIGH); //dung truyen va doi xu ly de hien thi da  
  digitalWrite(SS1, HIGH);
  digitalWrite(SS2, HIGH);
  digitalWrite(SS3, HIGH);  
  digitalWrite(SS4, HIGH); 
  thoigian=buf; //ghi du lieu ra LCD
}


void Display()
{ 
  // set the cursor to column 0, line 0
  lcd.setCursor(0, 0);
  String S_characternh3 = nh3 + "mg";
  lcd.print(S_characternh3);
  
  // set the cursor to column 8, line 0
  lcd.setCursor(9, 0);
  String S_characternd = nhietdo + char(223) + "C";
  lcd.print(S_characternd);
  
  // set the cursor to column 0, line 1
  lcd.setCursor(0, 1);
  String S_characterod = oxyhoatan + "mg";
  lcd.print(S_characterod);
  delay(100);
  //lcd.clear();

  // set the cursor to column 8, line 1
  lcd.setCursor(9, 1);
  String S_characterph = ph + "mg";
  lcd.print(S_characterph);
  delay(100);
  //lcd.clear();
}


void Reading()
{
  NH3();
  NhietDo();
  OxyHoatan();
  PH();
/*
    Serial.print ("Amoniac: ");
    Serial.println (nh3);
    Serial.print ("Temperature: ");
    Serial.println (nhietdo);
    Serial.print ("pH: ");
    Serial.println (ph);
    Serial.print ("Oxygen: ");
    Serial.println (oxyhoatan);
    Serial.print ("DateTime: ");
    Serial.println (thoigian);
  */
  
  while(nh3.length()<5||nhietdo.length()<5||ph.length()<5||oxyhoatan.length()<5)
  {
    NH3();
    NhietDo();
    OxyHoatan();
    PH();
  }

  String temp_nhietdo = nhietdo;
  String temp_nh3 = nh3;
  String temp_ph = ph;
  String temp_oxyhoatan = oxyhoatan;
  String temp_thoigian = thoigian;

  //checking serial communication request
  char r;
  r = Serial.read();
  //Truyen ca so va ten cua cac cam bien
  if(r=='@')
  {
    //Dinh dang du lieu Json
    DynamicJsonBuffer jBuffer;
    JsonObject& root  = jBuffer.createObject();
    root["Amoniac"]=temp_nh3;
    root["pH"]=temp_ph;
    root["Temperature"]=temp_nhietdo;
    root["Oxygen"]=temp_oxyhoatan;
    //root["date_time"]=temp_thoigian;
    root.prettyPrintTo(Serial);
    Serial.println(",");
    //Serial.println();
     
  }
  //Chi truyen chuoi so
  if(r=='!')
  {
    Serial.print (temp_thoigian);
    Serial.print (temp_nh3);
    Serial.print (temp_nhietdo);
    Serial.print (temp_ph);
    Serial.print (temp_oxyhoatan);
  }
}

void loop ()
{
  Reading();
  Display();
  delay(100);
}
