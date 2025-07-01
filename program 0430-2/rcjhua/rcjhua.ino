#include <Adafruit_NeoPixel.h>
int stepx=0;
 Adafruit_NeoPixel pixels6(64, 38, NEO_GRB + NEO_KHZ800);

void setup() { 
  Serial.begin(38400);
  pixels6.begin();
  while(1)
  {
   receivenow();
   if(stepx>=5){btsend(8);break;}
 }


 while(1)
  {
   receivenow();
   if(stepx>=30){break;}
}
delay(4000);
highlight();

 while(1)
  {
   receivenow();
   if(stepx>=90){break;}
}
lowlight();
}

void loop() {


}

void highlight(){
for(int a=0;a<86;a++){pixels6.setPixelColor(a, pixels6.Color(250, 0, 0));}pixels6.clear();pixels6.show(); 
}

void lowlight(){
  for(int a=0;a<86;a++){pixels6.setPixelColor(a, pixels6.Color(0, 0, 0));}pixels6.clear();pixels6.show(); 
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