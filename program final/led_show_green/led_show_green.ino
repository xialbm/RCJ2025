#include<Wire.h>
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel pixels1(36, 6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2(36, 7, NEO_GRB + NEO_KHZ800);

int zhiling;
int stepx=0;

void setup() {
  Serial.begin(38400);
  pixels1.begin();
  pixels2.begin();
  for(int i=0;i<36;i++){
    pixels1.setPixelColor(i, pixels1.Color(0, 255, 0));
    pixels2.setPixelColor(i, pixels1.Color(0, 255, 0));
  }
  pixels1.show();
  pixels2.show();
  delay(500);
  for(int i=0;i<36;i++){
    pixels1.setPixelColor(i, pixels1.Color(0, 0, 0));
    pixels2.setPixelColor(i, pixels1.Color(0, 0, 0));
  }
  pixels1.show();
  pixels2.show();

  Serial.begin(38400);
  while(1)
  {
    receivenow();
    if(stepx>=5){btsend(3);break;}
  }
  while(1)
  {receivenow();
    if(stepx>=40){break;}
    }
  delay(3000);
  highlight_g();

  while(1)
  {receivenow();
    if(stepx>=40){break;}
    }
  highlight_r();

  while(1)
  {receivenow();
    if(stepx>=90){break;}
    }
lowlight();
}



void loop() {
  /*if (Serial.available()) {
    while (Serial.available()) {
      delay(20);
      if (Serial.read() == 251) {
        zhiling=Serial.read();
      }
    }
    if(zhiling==1){for(int i=0;i<24;i++){pixels1.setPixelColor(i, pixels1.Color(255, 0, 0));pixels2.setPixelColor(i, pixels1.Color(255, 0, 0));}}
    else if(zhiling==2){for(int i=0;i<24;i++){pixels1.setPixelColor(i, pixels1.Color(0, 255, 0));pixels2.setPixelColor(i, pixels1.Color(0, 255, 0));}}
    else if(zhiling==3){for(int i=0;i<24;i++){pixels1.setPixelColor(i, pixels1.Color(0, 0, 255));pixels2.setPixelColor(i, pixels1.Color(0, 0, 255));}}
    else if(zhiling==0){for(int i=0;i<24;i++){pixels1.setPixelColor(i, pixels1.Color(0, 0, 0));pixels2.setPixelColor(i, pixels1.Color(0, 0, 0));}}
    pixels1.show();
    pixels2.show();
    delay(50);
  }
  for(int i=0;i<36;i++){
    pixels1.setPixelColor(i, pixels1.Color(0, 0, 0));
    pixels2.setPixelColor(i, pixels1.Color(0, 0, 0));
  }
  pixels1.show();
  pixels2.show();
  delay(8000);
  for(int i=0;i<36;i++){
    pixels1.setPixelColor(i, pixels1.Color(0, 255, 0));
    pixels2.setPixelColor(i, pixels1.Color(0, 255, 0));
  }
  pixels1.show();
  pixels2.show();
  delay(30000);
  for(int i=0;i<36;i++){
    pixels1.setPixelColor(i, pixels1.Color(0, 0, 0));
    pixels2.setPixelColor(i, pixels1.Color(0, 0, 0));
  }
  pixels1.show();
  pixels2.show();
  while(1){}*/
  
}

void highlight_g(){
  for(int i=0;i<36;i++){
    pixels1.setPixelColor(i, pixels1.Color(0, 255, 0));
    pixels2.setPixelColor(i, pixels1.Color(0, 255, 0));
  }
  pixels1.show();
  pixels2.show();
}

void highlight_r(){
  for(int i=0;i<36;i++){
    pixels1.setPixelColor(i, pixels1.Color(255, 0, 0));
    pixels2.setPixelColor(i, pixels1.Color(255, 0, 0));
  }
  pixels1.show();
  pixels2.show();
}

void lowlight(){
  for(int i=0;i<36;i++){
    pixels1.setPixelColor(i, pixels1.Color(0, 0, 0));
    pixels2.setPixelColor(i, pixels1.Color(0, 0, 0));
  }
  pixels1.show();
  pixels2.show();
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
      if(getnrnow>stepx){stepx=getnrnow;}
    }
  }

}
void btsend(int btnr)
{
  Serial.write(254);
  Serial.write(btnr);
}
