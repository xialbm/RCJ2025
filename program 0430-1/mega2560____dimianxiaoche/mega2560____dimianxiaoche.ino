int zhuandong1=0;
int zhuandong=0;
int pos=0;
int fang=0;
#include <Wire.h>
#include <Servo.h>
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel pixels1(23, 38, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2(23, 40, NEO_GRB + NEO_KHZ800);

Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;

int fazhi=100;

int stepx=0;

void setup() {
 Wire.begin();
 pixels1.begin();
 pixels2.begin();


  for(int i=0;i<23;i++){
  pixels1.setPixelColor(i, pixels1.Color(200, 200, 200)); pixels1.show(); delay(150);}
  pixels1.clear();
  delay(1000);
  for(int i=0;i<23;i++){
  pixels2.setPixelColor(i, pixels2.Color(200, 200, 200)); pixels2.show(); delay(150);}
  pixels2.clear();
  delay(1000);

 Serial.begin(9600);
 Serial2.begin(38400);
 Serial3.begin(38400);
 myservo1.attach(22);
 myservo2.attach(23);//升降
 myservo3.attach(46);
 myservo4.attach(49);//圆

 myservo3.write(175);
 myservo4.write(145);//下

while(1)
  {
    receivenow();
    if(stepx>=5){btsend(6);break;}
  }


//myservo3.write(110);
//myservo4.write(90);//圆
 myservo1.write(170);//底     
 myservo2.write(10);   
 //myservo1.write(70);//顶
 //myservo2.write(110);   
 delay(3000);
 for(pos=175;pos>=110;pos-=1){
 myservo3.write(pos);
 delay(5);}
 for(pos=145;pos>=90;pos-=1){
 myservo4.write(pos);
 delay(5);}//圆
delay(1000);

while(1){

  for(int i=0;i<23;i++){
  pixels1.setPixelColor(i, pixels1.Color(100, 50, 200)); pixels2.setPixelColor(i, pixels1.Color(100, 50, 200)); pixels1.show();  pixels2.show();delay(300);}
  pixels1.clear();
  pixels2.clear();
  delay(1000);


}
//以上为初始化

while(1)
  {
    receivenow();
    if(stepx>=80){break;}
    
  }
  //变形动作，变形亮灯之后
  btsend(85);




}
void loop() {
 //Serial.println(znzget());delay(100);
//jieshou();
// fang1();

}
void sportkk(int speedkz1, int speedkz2, int speedkz3, int speedkz4)
{
  int sdjk2, sdjk3, sdjk4, sdjk5, sdjk6, sdjk7, sdjk8, sdjk9;
  if (speedkz1 < 0) {
    sdjk2 = -speedkz1 ;
    sdjk3 = 0;
  }  else if (speedkz1 > 0) {
    sdjk3 = 255;
    sdjk2 = speedkz1;
  }  else {
    sdjk2 = 0;
    sdjk3 = 0;
  }
  if (speedkz2 < 0) {
    sdjk4 = -speedkz2 ;
    sdjk5 = 0;
  }  else if (speedkz2 > 0) {
    sdjk5 = 255;
    sdjk4 = speedkz2;
  }  else {
    sdjk4 = 0;
    sdjk5 = 0;
  }
  if (speedkz3 < 0) {
    sdjk6 = -speedkz3;
    sdjk7 = 255;
  }  else if (speedkz3 > 0) {
    sdjk7 = 0;
    sdjk6 = speedkz3;
  }  else {
    sdjk6 = 0;
    sdjk7 = 0;
  }
  if (speedkz4 < 0) {
    sdjk8 = -speedkz4;
    sdjk9 = 255;
  }  else if (speedkz4 > 0) {
    sdjk9 = 0;
    sdjk8 = speedkz4;
  }  else {
    sdjk8 = 0;
    sdjk9 = 0;
  }
  analogWrite(26, sdjk2); analogWrite(27, sdjk3); analogWrite(28, sdjk4); analogWrite(29, sdjk5); analogWrite(30, sdjk6); analogWrite(31, sdjk7); analogWrite(32, sdjk8); analogWrite(33, sdjk9);
}
void jieshou()
{ 
  if(Serial3.available()> 0)
  {
    if(Serial3.read()!=201) 
    {
    }
    else
    {
      delay(20); 
       fang=Serial3.read();
       
      //Serial.println(fang);
    }
  }
}
void fang1(){
zhuandong=znzget();
//zhuandong=(znzget()+zhuandong*9)/10; 
if( fang == 2){
zhuandong1=zhuandong-pos;
  if(zhuandong1>180)zhuandong1=zhuandong1-360;///
if(zhuandong1<5&&zhuandong1>-5)zhuandong1=0;
zhuandong1=zhuandong1*3;
sportkk(150-zhuandong1,150-zhuandong1,150+zhuandong1,150+zhuandong1);
}
else if( fang == 3){
zhuandong1=zhuandong-pos;
  if(zhuandong1>180)zhuandong1=zhuandong1-360;///
if(zhuandong1<5&&zhuandong1>-5)zhuandong1=0;
zhuandong1=zhuandong1*3;
sportkk(-150-zhuandong1,-150-zhuandong1,-150+zhuandong1,-150+zhuandong1);
}
else if( fang == 4){
if(zhuandong>180)zhuandong=zhuandong-360;///
if(zhuandong<5&&zhuandong>-5)zhuandong=0;
pos=zhuandong;
sportkk(-255,-255,255,255);
}
else if( fang == 5){
if(zhuandong>180)zhuandong=zhuandong-360;///
if(zhuandong<5&&zhuandong>-5)zhuandong=0;
pos=zhuandong;
sportkk(255,255,-255,-255);
}
else if( fang == 1){
 //sportkk(200-zhuandong,200-zhuandong,200+zhuandong,200+zhuandong);
}
else{
sportkk(0,0,0,0);
}
Serial.println(zhuandong);
delay(10);
}

void stopdj()
{
  sportkk(0, 0, 0, 0);
}
int znzget()
{
  int highpr = 99;
  int lowpr = 99;
  Wire.requestFrom(59, 2);
  while (Wire.available())
  {
    highpr = Wire.read();
    lowpr = Wire.read();
  }
  if (highpr == 11 && lowpr == 02) return 999;
  else if (highpr < 2)return highpr * 255 + lowpr;
  else return highpr;
}


void receivenow()
{
  int getnrnow=0;
  if(Serial2.available())
  {
    delay(25);
    while(Serial2.available())
    {
      if(Serial2.read()==254)
      getnrnow=Serial2.read();
      if(getnrnow>stepx){stepx=getnrnow;}
    }
  }

}
void btsend(int btnr)
{
  Serial2.write(254);
  Serial2.write(btnr);
}
  // a=analogRead(33)/16; 
 // a=(a*19+analogRead(33)/16)/20;
 /* analogWrite(26,255);
 // analogWrite(27,255);//3
  analogWrite(28,255);
  //analogWrite(29,0);//5
  analogWrite(30,255);
 // analogWrite(31,0);//7
  analogWrite(32,255);
 // analogWrite(33,0);//9*/
//else{sportkk(100,100,100,100);}
//sportkk(255,255,255,255);