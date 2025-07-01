#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4); 

String errort="";
long timer=0;
long begintimer=0;
int stepx=0;
long steptime=0;
long ledtimer;
long zerotimer;


void setup() {
  lcd.init();   
  lcd.backlight();
  lcd.clear();

  Serial.begin(9600);
  Serial1.begin(38400);
  Serial2.begin(38400);
  Serial3.begin(38400);
  timer=millis();
  begintimer=millis();
  while(1)
  {
    receivebegin();
    if(analogRead(A0)<0)break;
    if(millis()-timer>1000){ errort=errort+"0"; lcd.setCursor(0, 3);lcd.print(errort);lcd.print(" T OUT");break;}
    if(millis()-begintimer>2000){begintimer=millis();btsendbegin(5);}
  }
  zerotimer=millis();
  //lcd.clear();





  btsend(20);
  timer=millis();
  ledtimer=millis();
  begintimer=millis();
  
  steptime=6000;
  while(1)
  {
    receivenow();
    if(millis()-timer>steptime){errort=errort+"1"; lcd.setCursor(0, 3);lcd.print(errort);lcd.print(" T OUT");break; }
    if(stepx>=25){break;}
    if(millis()-ledtimer>1000)
    {ledtimer=millis();lcd.setCursor(0, 0);lcd.print("T:");lcd.print(int(millis()-zerotimer)/1000);
    lcd.setCursor(6, 0);lcd.print("TS:");lcd.print(int(millis()-begintimer)/1000);}
  } 





  btsend(30);
  timer=millis();
  ledtimer=millis();
  begintimer=millis();
  
  steptime=6000;
  while(1)
  {
    receivenow();
    if(millis()-timer>steptime){errort=errort+"2"; lcd.setCursor(0, 3);lcd.print(errort);lcd.print(" T OUT");break; }
    if(stepx>=35){break;}
    if(millis()-ledtimer>1000)
    {ledtimer=millis();lcd.setCursor(0, 0);lcd.print("T:");lcd.print(int(millis()-zerotimer)/1000);
    lcd.setCursor(6, 0);lcd.print("TS:");lcd.print(int(millis()-begintimer)/1000);}
  } 





}

void loop() {
  delay(1000);

}

void receivebegin()
{
  int getnrbegin=0;
    if(Serial1.available())
  {
    delay(25);
    while(Serial1.available())
    {
      if(Serial1.read()==254)
      getnrbegin=Serial1.read();
      if(getnrbegin==1){lcd.setCursor(0, 0);lcd.print("*1*");}
      if(getnrbegin==2){lcd.setCursor(4, 0);lcd.print("*2*");}
      if(getnrbegin==3){lcd.setCursor(8, 0);lcd.print("*3*");}
      if(getnrbegin==4){lcd.setCursor(12, 0);lcd.print("*4*");}
      if(getnrbegin==5){lcd.setCursor(16, 0);lcd.print("*5*");}
      if(getnrbegin==6){lcd.setCursor(0, 1);lcd.print("*6*");}
      if(getnrbegin==7){lcd.setCursor(4, 1);lcd.print("*7*");}
      if(getnrbegin==8){lcd.setCursor(8, 1);lcd.print("*8*");}
      if(getnrbegin==9){lcd.setCursor(12, 1);lcd.print("*9*");}
      if(getnrbegin==10){lcd.setCursor(16, 1);lcd.print("*10");}
      if(getnrbegin==11){lcd.setCursor(0, 2);lcd.print("*11");}
      if(getnrbegin==12){lcd.setCursor(4, 2);lcd.print("*12");}
      if(getnrbegin==13){lcd.setCursor(8, 2);lcd.print("*13");}
      if(getnrbegin==14){lcd.setCursor(12, 2);lcd.print("*14");}
      if(getnrbegin==15){lcd.setCursor(16, 2);lcd.print("*15");}

    }
  }
  if(Serial2.available())
  {
    delay(25);
    while(Serial2.available())
    {
      if(Serial2.read()==254)
      getnrbegin=Serial2.read();
      if(getnrbegin==1){lcd.setCursor(0, 0);lcd.print("*1*");}
      if(getnrbegin==2){lcd.setCursor(4, 0);lcd.print("*2*");}
      if(getnrbegin==3){lcd.setCursor(8, 0);lcd.print("*3*");}
      if(getnrbegin==4){lcd.setCursor(12, 0);lcd.print("*4*");}
      if(getnrbegin==5){lcd.setCursor(16, 0);lcd.print("*5*");}
      if(getnrbegin==6){lcd.setCursor(0, 1);lcd.print("*6*");}
      if(getnrbegin==7){lcd.setCursor(4, 1);lcd.print("*7*");}
      if(getnrbegin==8){lcd.setCursor(8, 1);lcd.print("*8*");}
      if(getnrbegin==9){lcd.setCursor(12, 1);lcd.print("*9*");}
      if(getnrbegin==10){lcd.setCursor(16, 1);lcd.print("*10");}
      if(getnrbegin==11){lcd.setCursor(0, 2);lcd.print("*11");}
      if(getnrbegin==12){lcd.setCursor(4, 2);lcd.print("*12");}
      if(getnrbegin==13){lcd.setCursor(8, 2);lcd.print("*13");}
      if(getnrbegin==14){lcd.setCursor(12, 2);lcd.print("*14");}
      if(getnrbegin==15){lcd.setCursor(16, 2);lcd.print("*15");}

    }
  }
  if(Serial3.available())
  {
    delay(25);
    while(Serial3.available())
    {
      if(Serial3.read()==254)
      getnrbegin=Serial3.read();
      if(getnrbegin==1){lcd.setCursor(0, 0);lcd.print("*1*");}
      if(getnrbegin==2){lcd.setCursor(4, 0);lcd.print("*2*");}
      if(getnrbegin==3){lcd.setCursor(8, 0);lcd.print("*3*");}
      if(getnrbegin==4){lcd.setCursor(12, 0);lcd.print("*4*");}
      if(getnrbegin==5){lcd.setCursor(16, 0);lcd.print("*5*");}
      if(getnrbegin==6){lcd.setCursor(0, 1);lcd.print("*6*");}
      if(getnrbegin==7){lcd.setCursor(4, 1);lcd.print("*7*");}
      if(getnrbegin==8){lcd.setCursor(8, 1);lcd.print("*8*");}
      if(getnrbegin==9){lcd.setCursor(12, 1);lcd.print("*9*");}
      if(getnrbegin==10){lcd.setCursor(16, 1);lcd.print("*10");}
      if(getnrbegin==11){lcd.setCursor(0, 2);lcd.print("*11");}
      if(getnrbegin==12){lcd.setCursor(4, 2);lcd.print("*12");}
      if(getnrbegin==13){lcd.setCursor(8, 2);lcd.print("*13");}
      if(getnrbegin==14){lcd.setCursor(12, 2);lcd.print("*14");}
      if(getnrbegin==15){lcd.setCursor(16, 2);lcd.print("*15");}

    }
  }
}
void receivenow()
{
  int getnrnow=0;
  if(Serial1.available())
  {
    delay(25);
    while(Serial1.available())
    {
      if(Serial1.read()==254)
      getnrnow=Serial1.read();
      lcd.setCursor(0, 1);lcd.print("READ:          ");
      lcd.setCursor(5, 1);lcd.print(getnrnow);
      lcd.setCursor(10, 1);lcd.print("AT:        ");
      lcd.setCursor(13, 1);lcd.print(int(millis()-zerotimer)/1000);
      if(getnrnow>stepx){stepx=getnrnow;}
    }
  }
  if(Serial2.available())
  {
    delay(25);
    while(Serial2.available())
    {
      if(Serial2.read()==254)
      getnrnow=Serial2.read();
      lcd.setCursor(0, 1);lcd.print("READ:          ");
      lcd.setCursor(5, 1);lcd.print(getnrnow);
      lcd.setCursor(10, 1);lcd.print("AT:        ");
      lcd.setCursor(13, 1);lcd.print(int(millis()-zerotimer)/1000);
      if(getnrnow>stepx){stepx=getnrnow;}
    }
  }
    if(Serial3.available())
  {
    delay(25);
    while(Serial3.available())
    {
      if(Serial3.read()==254)
      getnrnow=Serial3.read();
      lcd.setCursor(0, 1);lcd.print("READ:          ");
      lcd.setCursor(5, 1);lcd.print(getnrnow);
      lcd.setCursor(10, 1);lcd.print("AT:        ");
      lcd.setCursor(13, 1);lcd.print(int(millis()-zerotimer)/1000);
      if(getnrnow>stepx){stepx=getnrnow;}
    }
  }
}

void btsendbegin(int btnr)
{
  Serial1.write(254);
  Serial1.write(btnr);
  delay(3);
  Serial2.write(254);
  Serial2.write(btnr);
  delay(3);
  Serial2.write(254);
  Serial2.write(btnr);
}

void btsend(int btnr)
{
  Serial1.write(254);
  Serial1.write(btnr);
  delay(3);
  Serial2.write(254);
  Serial2.write(btnr);
  delay(3);
  Serial3.write(254);
  Serial3.write(btnr);
      lcd.setCursor(0, 1);lcd.print("SEND:          ");
      lcd.setCursor(5, 1);lcd.print(btnr);
      lcd.setCursor(10, 1);lcd.print("AT:        ");
      lcd.setCursor(13, 1);lcd.print(int(millis()-zerotimer)/1000);
}
