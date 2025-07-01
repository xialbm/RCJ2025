#include <U8g2lib.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>


Adafruit_NeoPixel pixels1(4, 35, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2(4, 36, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels3(4, 37, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels4(4, 38, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels5(8, 39, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels6(4, 40, NEO_GRB + NEO_KHZ800);

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
int handegreego=90;
int handegreex=90;

void setup() {
  Wire.begin();
  pinMode(47,OUTPUT);
  pinMode(48,OUTPUT);
  ledcAttachChannel(47, 50, 12, 5);
  ledcAttachChannel(48, 50, 12, 5);
  ledcWrite(47, 60);
  ledcWrite(48, 60);
  Serial.begin(9600);
  Serial2.begin(38400, SERIAL_8N1, 19, 20); 
  Serial1.begin(38400, SERIAL_8N1, 15, 16); 
  u8g2.begin();
  u8g2.setFont(u8g2_font_boutique_bitmap_7x7_tf);
  delay(200);
  u8g2.clearBuffer();u8g2.setCursor(0, 20); u8g2.print("loading");u8g2.sendBuffer(); 
  pixels1.begin();
  pixels2.begin();
  pixels3.begin();
  pixels4.begin();
  pixels5.begin();
  pixels6.begin();
  begintime=millis();
  while(1)
  {
    if(millis()>begintime+20000){ncameramode=1;u8g2.clearBuffer();u8g2.setCursor(0, 20); u8g2.print("Camera error");u8g2.sendBuffer(); delay(1000);break;}
    cameraget(1);
    if(handegree+fingerx+fingery>0)break;
  }
}



void loop() {
  
doorclose();
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
        delay(1500);
         {for (int i=0;i<4;i++){pixels2.setPixelColor(i, pixels2.Color(90, 0, 0));} }
        delay(1200);
         {for (int i=0;i<4;i++){pixels4.setPixelColor(i, pixels4.Color(90, 0, 0));} }
        delay(1500);
         {for (int i=0;i<4;i++){pixels3.setPixelColor(i, pixels3.Color(90, 0, 0));} }
         Serial.print("err ");
         break;
      }
      else {
        cameraget(0);
        if(fingerx<40&&fingery<20&&fingerx>3&&fingerx>3)rhy=1;
        if(fingerx>70&&fingery<20)lhy=1;
        if(fingerx<40&&fingery>40)rly=1;
        if(fingerx>70&&fingery>40)lly=1;
        if(lhy==1) {for (int i=0;i<4;i++){pixels1.setPixelColor(i, pixels1.Color(90, 0, 0));} }
        if(rhy==1) {for (int i=0;i<4;i++){pixels2.setPixelColor(i, pixels2.Color(90, 0, 0));} }
        if(lly==1) {for (int i=0;i<4;i++){pixels3.setPixelColor(i, pixels3.Color(90, 0, 0));} }
        if(rly==1) {for (int i=0;i<4;i++){pixels4.setPixelColor(i, pixels4.Color(90, 0, 0));} }
        Serial.print(lhy);Serial.print("  ");Serial.print(rhy);Serial.print("  ");Serial.print(lly);Serial.print("  ");Serial.println(rly);
        if(lhy&rhy*lly*rly==1) break;

      }
    }
    for (int i=60;i<500;i++){ledcWrite(47, i);delay(4);}
    delay(250);
    for (int i=0;i<8;i++){pixels5.setPixelColor(i, pixels5.Color(90, 0, 0));}
    delay(250);
    while(1)
    {
      if(ncameramode==1)
      {
        delay(1500);
         for (int i=60;i<130;i++){ledcWrite(48, i); }
        delay(500);
         for (int i=130;i<300;i++){ledcWrite(48, i); }
        delay(200);
         for (int i=300;i<430;i++){ledcWrite(48, i); }
        delay(500);
         for (int i=430;i<500;i++){ledcWrite(48, i); }
         Serial.print("err");
         break;
      }
      else {
        cameraget(0);
        if(handegree>270)handegreex=0;
        else if (handegree>180)handegreex=180;
        else handegreex=handegree;
        if(handegreego-handegreex>6)handegreego=handegreego-3;
        if(handegreego-handegreex<-6)handegreego=handegreego+3;
        if(handegreego<0)handegreego=0;
        if(handegreego>180)handegreego=180;
        Serial.println(handegreego);
        ledcWrite(48, (handegreego)*41/100);
        if(handegreego<20) 
        {
          for (int i=20;i>0;i--){ledcWrite(48, i*41/100);delay(20);}
          break;
        }

      }      
    }
    for (int i=0;i<4;i++){pixels1.setPixelColor(i, pixels1.Color(0, 90, 0));} 
    for (int i=0;i<4;i++){pixels2.setPixelColor(i, pixels2.Color(0, 90, 0));} 
    for (int i=0;i<4;i++){pixels3.setPixelColor(i, pixels3.Color(0, 90, 0));} 
    for (int i=0;i<4;i++){pixels4.setPixelColor(i, pixels4.Color(0, 90, 0));} 
    for (int i=0;i<8;i++){pixels5.setPixelColor(i, pixels5.Color(0, 90, 0));}
    
}


void dooropen()
{



}