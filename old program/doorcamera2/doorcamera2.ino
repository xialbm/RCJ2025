#include <U8g2lib.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>


Adafruit_NeoPixel pixels1(4, 35, NEO_GRB + NEO_KHZ800);//
Adafruit_NeoPixel pixels2(4, 36, NEO_GRB + NEO_KHZ800);//
Adafruit_NeoPixel pixels3(4, 37, NEO_GRB + NEO_KHZ800);//
Adafruit_NeoPixel pixels4(4, 38, NEO_GRB + NEO_KHZ800);//四角灯
Adafruit_NeoPixel pixels5(8, 39, NEO_GRB + NEO_KHZ800);//横条舵机灯
Adafruit_NeoPixel pixels6(86, 40, NEO_GRB + NEO_KHZ800);//爆炸灯

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);




long cameratime=0;
int fingerx=0;
int fingery=0;
int handegree=0;
long begintime=0;
int ncameramode=0;
bool lhy=0;
bool rhy=0;
bool lly=0;
bool rly=0;
int handegreego=180;
int handegreex=180;

void setup() {
  Wire.begin();
  pinMode(47,OUTPUT);
  pinMode(48,OUTPUT);
  pinMode(7,OUTPUT);
  ledcAttachChannel(47, 50, 12, 1);
  ledcAttachChannel(48, 50, 12, 2);
  ledcAttachChannel(7, 50, 12, 3);
  ledcWrite(47, 60);
  ledcWrite(7, 60);
  ledcWrite(48, 440);
  Serial.begin(9600);
  Serial2.begin(38400, SERIAL_8N1, 19, 20); 
  Serial1.begin(38400, SERIAL_8N1, 15, 16); 
  u8g2.begin();
  u8g2.setFont(u8g2_font_boutique_bitmap_7x7_tf);
  delay(200);
  u8g2.clearBuffer();u8g2.setCursor(0, 20); u8g2.print("loading");u8g2.sendBuffer(); 
  ledcWrite(47, 360);
  pixels1.begin();
  pixels2.begin();
  pixels3.begin();
  pixels4.begin();
  pixels5.begin();
  pixels6.begin();
  
    for (int i=0;i<4;i++){pixels1.setPixelColor(i, pixels1.Color(0, 0, 0));} 
    for (int i=0;i<4;i++){pixels2.setPixelColor(i, pixels2.Color(0, 0, 0));} 
    for (int i=0;i<4;i++){pixels3.setPixelColor(i, pixels3.Color(0, 0, 0));} 
    for (int i=0;i<4;i++){pixels4.setPixelColor(i, pixels4.Color(0, 0, 0));} 
    for (int i=0;i<8;i++){pixels5.setPixelColor(i, pixels5.Color(0, 0, 0));}
    for (int i=0;i<80;i++){pixels6.setPixelColor(i, pixels6.Color(0, 0, 0));}
    pixels1.show();
    pixels2.show();
    pixels3.show();
    pixels4.show();
    pixels5.show();
  delay(500);
  ledcWrite(7, 70);
  delay(1000);
  ledcWrite(7, 470);
  delay(1000);
  begintime=millis();
 while(1)
  {
    if(millis()>begintime+20000){ncameramode=1;u8g2.clearBuffer();u8g2.setCursor(0, 20); u8g2.print("Camera error");u8g2.sendBuffer(); delay(1000);break;}
    cameraget(1);
    if(handegree+fingerx+fingery>0)break;
  }
  doorclose(); 
  delay(2000);
  dooropen();
}



void loop() {
  
//doorclose();
}


void cameraget(bool xsms)
{
  while(Serial1.available())
  {
      Serial1.read();
  }
  cameratime=millis();
  Serial1.write(120+xsms);
  while(!Serial1.available())
  {
    if(millis()>cameratime+500) {cameratime=0;break;}
  }
  delay(10);
  if(cameratime>0)
  {
    if(Serial1.read()==125)
    fingerx=Serial1.read();
    fingery=Serial1.read();
    handegree=Serial1.read()*3;
    Serial.print(fingerx);Serial.print("  ");Serial.println(fingery);
    u8g2.clearBuffer();
    u8g2.drawCircle(120-fingerx, 2+fingery*1.15, 2);
    u8g2.drawLine(64, 32, 64-(10*(sin((handegree-90+360)%360*3.14/180))), 32-(10*(cos((handegree-90+360)%360*3.14/180))));
    u8g2.sendBuffer(); 
  }

}




void doorclose()
{
  Serial.print("ncameramode ");Serial.print(ncameramode);
    while(1)
    {
      if(ncameramode==1)
      {
        delay(3000);
         {for (int i=0;i<4;i++){pixels1.setPixelColor(i, pixels1.Color(90, 0, 0));} }
         pixels1.show();
        delay(1500);
         {for (int i=0;i<4;i++){pixels2.setPixelColor(i, pixels2.Color(90, 0, 0));} }
         pixels2.show();
        delay(1200);
         {for (int i=0;i<4;i++){pixels4.setPixelColor(i, pixels4.Color(90, 0, 0));} }
         pixels3.show();
        delay(1500);
         {for (int i=0;i<4;i++){pixels3.setPixelColor(i, pixels3.Color(90, 0, 0));} }
         pixels4.show();
         Serial.print("err ");
         break;
      }
      else {
        cameraget(0);
        if(fingerx<40&&fingery<20&&fingerx>3&&fingerx>3)rhy=1;
        if(fingerx>70&&fingery<20)lhy=1;
        if(fingerx<40&&fingery>40)rly=1;
        if(fingerx>70&&fingery>40)lly=1;
        if(lhy==1) {for (int i=0;i<4;i++){pixels1.setPixelColor(i, pixels1.Color(90, 0, 0));} pixels1.show();}
        if(rhy==1) {for (int i=0;i<4;i++){pixels2.setPixelColor(i, pixels2.Color(90, 0, 0));} pixels2.show();}
        if(lly==1) {for (int i=0;i<4;i++){pixels3.setPixelColor(i, pixels3.Color(90, 0, 0));} pixels3.show();}
        if(rly==1) {for (int i=0;i<4;i++){pixels4.setPixelColor(i, pixels4.Color(90, 0, 0));} pixels4.show();}
        Serial.print(lhy);Serial.print("  ");Serial.print(rhy);Serial.print("  ");Serial.print(lly);Serial.print("  ");Serial.println(rly);
        if(lhy&rhy*lly*rly==1) break;
    

      }
    }
    
    for (int i=0;i<8;i++){pixels5.setPixelColor(i, pixels5.Color(200, 0, 0));}
    pixels5.show();
    delay(250);
    begintime=millis();
    if(ncameramode==0)   while(1){ cameraget(0);if(handegree>150&&handegree<270)break;  if(millis()-begintime>3000)break;}
       
    while(1)
    {
      if(ncameramode==1)
      {
        delay(1500);
         for (int i=70;i<130;i++){ledcWrite(7, i); }
        delay(500);
         for (int i=130;i<300;i++){ledcWrite(7, i); }
        delay(200);
         for (int i=300;i<430;i++){ledcWrite(7, i); }
        delay(500);
         for (int i=430;i<470;i++){ledcWrite(7, i); }
         Serial.print("err");
         break;
      }
      else {
        cameraget(0);
        if (handegree>270)handegreex=0;
        else if (handegree>180)handegreex=180;
        else handegreex=handegree;
        if(handegreego-handegreex>6)handegreego=handegreego-5;
        if(handegreego-handegreex<-6)handegreego=handegreego+5;
        if(handegreego<0)handegreego=0;
        if(handegreego>180)handegreego=180;
        Serial.println(handegreego);
        ledcWrite(7, (handegreego)*20/9+70);
        if(handegreego<20) 
        {
          for (int i=20;i>0;i--){ledcWrite(7, i*20/9+70);delay(50);}
          break;
        }

      }      
    }
    for (int i=0;i<4;i++){pixels1.setPixelColor(i, pixels1.Color(0, 200, 0));} 
    for (int i=0;i<4;i++){pixels2.setPixelColor(i, pixels2.Color(0, 200, 0));} 
    for (int i=0;i<4;i++){pixels3.setPixelColor(i, pixels3.Color(0, 200, 0));} 
    for (int i=0;i<4;i++){pixels4.setPixelColor(i, pixels4.Color(0, 200, 0));} 
    for (int i=0;i<8;i++){pixels5.setPixelColor(i, pixels5.Color(0, 200, 0));}


    pixels1.show();
    pixels2.show();
    pixels3.show();
    pixels4.show();
    pixels5.show();

    for (int i=360;i>80;i--){ledcWrite(47, i);delay(4);}//不确定
    delay(250);
    
}


void dooropen()//炸门
{
 
 /*for(int i=0;i<15;i++){
 if(i<=5){
 for (int a=0;a<86;a++){pixels6.setPixelColor(a, pixels6.Color(250, 0, 0));}
 pixels6.show();
 delay(2000-i*200);
 pixels6.clear();
 pixels6.show();
 delay(2000-i*200);
 }
 else if(i>5){
 for (int a=0;a<86;a++){pixels6.setPixelColor(a, pixels6.Color(250, 0, 0));}
 pixels6.show();
 delay(900-(i-5)*90);
 pixels6.clear();
 pixels6.show();
 delay(900-(i-5)*90);
 }
 }*/
 
for(int i=0;i<3;i++){for (int a=0;a<86;a++){pixels6.setPixelColor(a, pixels6.Color(250, 0, 0));}pixels6.show();delay(1000);pixels6.clear(); pixels6.show();delay(1000);}
for(int i=0;i<5;i++){for (int a=0;a<86;a++){pixels6.setPixelColor(a, pixels6.Color(250, 0, 0));}pixels6.show();delay(180);pixels6.clear(); pixels6.show();delay(180);}

 pixels6.clear();
 pixels6.show();

 for (int i=440;i>180;i--){ledcWrite(48, i);delay(2);}


}