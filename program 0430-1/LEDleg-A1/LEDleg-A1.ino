#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <Servo.h>
Servo myservo1; 
Servo myservo2; 
 
const int MPU_addr = 0x68;
long AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
long AcXMBBL=0;
long AcXMB=-3500;


int showx=0;
int showy=0;
int stepx=0;

Adafruit_NeoPixel pixels1(64, 38, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2(64, 39, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels3(64, 40, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels4(64, 41, NEO_GRB + NEO_KHZ800);


int zhuangtai=0;
int button=0;
int sum=0;

void setup() {
  Serial.begin(38400);
     
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B); 
  Wire.write(0); //启动mpu6050
  Wire.endTransmission(true);                         //初始化MPU6050
  delay(100);


  pixels1.begin();
  pixels2.begin();
  pixels3.begin();
  pixels4.begin();

  myservo1.attach(25); 
  myservo2.attach(26); 
  myservo1.write(10);      
  myservo2.write(10);   

 /*for (int i=0;i<64;i++)
  {
    pixels1.clear(); 
    pixels2.clear(); 
    pixels3.clear(); 
    pixels4.clear(); 
    pixels1.setPixelColor(i, pixels1.Color(0, 50, 0));
    pixels2.setPixelColor(i, pixels2.Color(0, 50, 0));
    pixels3.setPixelColor(i, pixels3.Color(0, 50, 0));
    pixels4.setPixelColor(i, pixels4.Color(0, 50, 0));
    pixels1.show();
    pixels2.show();
    pixels3.show();
    pixels4.show();
    delay(20);
  }*/

  pixels1.clear(); 
  pixels2.clear(); 
  pixels3.clear(); 
  pixels4.clear();
  pixels1.show();
  pixels2.show();
  pixels3.show();
  pixels4.show();
 

 
 
 
 
 //while(1)
 // {
 //   receivenow();
 //   if(stepx>=5){btsend(4);break;}
 // }

 /*while(1){button=digitalRead(6);if(button==0)break;else{}}
 delay(2000);
 for (int pos = 0; pos <= 95; pos += 1) { 
    myservo1.write(pos);            
    delay(15);                       
  }
  delay(1000);
   for(int pos = 0; pos <= 95; pos += 1) { 
    myservo2.write(pos);            
    delay(15);                       
  }
  while(1)
  {
 //if(sum==200){sum=0;btsend(444);}   
 //else{};  
 esp32MPU();
 showx=znzget();
 if(showx>180)showx=showx-360;
 showx=showx/5+7;
 showy=8-AcXMBBL/1000;
 Serial.println(showy);
 supershow(showx,showy);
  }*/
  while(1)
  {
    receivenow();
    if(stepx>=5){btsend(5);break;}
    
  }
//以上为初始化


while(1)
  {
    receivenow();
    if(stepx>=70){break;}    
  }
  //准备响应对接动作


//对接瞄准后
btsend(75);
}

void loop() {
 
}



void esp32MPU()
{
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true); // request a total of 14 registers
  AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
   
   AcXMBBL=(AcXMBBL*9+AcX-AcXMB)/10;
   //Serial.print("AcX = "); Serial.println(AcXMBBL);
   // Serial.print(" | AcY = "); Serial.print(AcY);
  //  Serial.print(" | AcZ = "); Serial.print(AcZ);
  //  Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53); //equation for temperature in degrees C from datasheet
  //  Serial.print(" | GyX = "); Serial.print(GyX);
   // Serial.print(" | GyY = "); Serial.print(GyY);
  //  Serial.print(" | GyZ = "); Serial.println(GyZ);
}

void supershow(int sshowx,int sshowy)
{
  pixels1.clear(); 
  pixels2.clear(); 
  pixels3.clear(); 
  pixels4.clear();
 // if(sshowx>15) sshowx=15;
  //if(sshowy>15) sshowy=15;
  //if(sshowx<0) sshowx=0;
  //if(sshowy<0) sshowy=0;
  DZled(sshowx,sshowy,1);
  if((sshowx==7||showx==8)&&(sshowy==7||showy==8))
  {
    sum=sum+1;
    DZled(sshowx-1,sshowy,4);
    DZled(sshowx-1,sshowy+1,4);
    DZled(sshowx-1,sshowy-1,4);
    DZled(sshowx,sshowy+1,4);
    DZled(sshowx,sshowy-1,4);
    DZled(sshowx+1,sshowy,4);
    DZled(sshowx+1,sshowy+1,4);
    DZled(sshowx+1,sshowy-1,4);
  }
  else
  {
    DZled(sshowx-1,sshowy,2);
    DZled(sshowx-1,sshowy+1,2);
    DZled(sshowx-1,sshowy-1,2);
    DZled(sshowx,sshowy+1,2);
    DZled(sshowx,sshowy-1,2);
    DZled(sshowx+1,sshowy,2);
    DZled(sshowx+1,sshowy+1,2);
    DZled(sshowx+1,sshowy-1,2);
  }
    DZled(sshowx-2,sshowy,3);
    DZled(sshowx-3,sshowy,3);
    DZled(sshowx+2,sshowy,3);
    DZled(sshowx+3,sshowy,3);
    DZled(sshowx,sshowy-2,3);
    DZled(sshowx,sshowy-3,3);
    DZled(sshowx,sshowy+2,3);
    DZled(sshowx,sshowy+3,3);
  pixels1.show();
  pixels2.show();
  pixels3.show();
  pixels4.show();
  delay(10);
}

void DZled(int ledx,int ledy,int ledzt)
{
  if(ledx>=0&&ledx<8&&ledy>=0&&ledy<8) 
  {
    if(ledzt==1)pixels1.setPixelColor(ledx+ledy*8, pixels1.Color(250, 50, 0));
    if(ledzt==2)pixels1.setPixelColor(ledx+ledy*8, pixels1.Color(0, 0, 200));
    if(ledzt==3)pixels1.setPixelColor(ledx+ledy*8, pixels1.Color(0, 200, 0));
    if(ledzt==4)pixels1.setPixelColor(ledx+ledy*8, pixels1.Color(200, 0, 0));
  //  Serial.println("1");
  }
  if(ledx>=8&&ledx<16&&ledy>=0&&ledy<8) 
  {
    if(ledzt==1)pixels2.setPixelColor(ledx-8+ledy*8, pixels2.Color(250, 50, 0));
    if(ledzt==2)pixels2.setPixelColor(ledx-8+ledy*8, pixels2.Color(0, 0, 200));
    if(ledzt==3)pixels2.setPixelColor(ledx-8+ledy*8, pixels2.Color(0, 200, 0));
    if(ledzt==4)pixels2.setPixelColor(ledx-8+ledy*8, pixels2.Color(200, 0, 0));
   // Serial.println("2");
  }
    if(ledx>=0&&ledx<8&&ledy>=8&&ledy<16) 
  {
    if(ledzt==1)pixels3.setPixelColor(ledx+(ledy-8)*8, pixels3.Color(250, 50, 0));
    if(ledzt==2)pixels3.setPixelColor(ledx+(ledy-8)*8, pixels3.Color(0, 0, 200));
    if(ledzt==3)pixels3.setPixelColor(ledx+(ledy-8)*8, pixels3.Color(0, 200, 0));
    if(ledzt==4)pixels3.setPixelColor(ledx+(ledy-8)*8, pixels3.Color(200, 0, 0));
   // Serial.println("3");
  }
  if(ledx>=8&&ledx<16&&ledy>=8&&ledy<16) 
  {
    if(ledzt==1)pixels4.setPixelColor(ledx-8+(ledy-8)*8, pixels4.Color(250, 50, 0));
    if(ledzt==2)pixels4.setPixelColor(ledx-8+(ledy-8)*8, pixels4.Color(0, 0, 200));
    if(ledzt==3)pixels4.setPixelColor(ledx-8+(ledy-8)*8, pixels4.Color(0, 200, 0));
    if(ledzt==4)pixels4.setPixelColor(ledx-8+(ledy-8)*8, pixels4.Color(200, 0, 0));
   // Serial.println("4");
  }
}


int znzget()
{
  int highpr = 0;
  int lowpr = 0;
  Wire.requestFrom(59, 2);
  while (Wire.available())
  {
    highpr = Wire.read();
    lowpr = Wire.read();
  }
  //if (highpr == 11 && lowpr == 02) return 360; else 
  if (highpr < 2)return highpr * 255 + lowpr;
  else return highpr;
}


void receivenow()
{
  int getnrnow=0;
  if(Serial.available())
  {
    
    delay(25);
    while(Serial.available())
    {
      if(Serial.read()==254)
      getnrnow=Serial.read();
      Serial.println(getnrnow);
      if(getnrnow>stepx){stepx=getnrnow;}
    }
  }

}
void btsend(int btnr)
{
  Serial.write(254);
  Serial.write(btnr);
}