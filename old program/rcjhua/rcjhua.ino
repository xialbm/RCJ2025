#include <Adafruit_NeoPixel.h>
void setup() { 
 Adafruit_NeoPixel pixels1(64, 38, NEO_GRB + NEO_KHZ800);
  while(1)
  {
   receivenow();
   if(stepx>=5){btsend(5);break;}
 }
 delay(4000);
for (int a=0;a<86;a++){pixels6.setPixelColor(a, pixels6.Color(250, 0, 0));}pixels6.show();//delay(1000);pixels6.clear(); pixels6.show();delay(1000);
 while(1)
  {
   receivenow();
   if(stepx>=5){btsend(5);break;}
for (int a=0;a<86;a++){pixels6.setPixelColor(a, pixels6.Color(250, 0, 0));}pixels6.clear();pixels6.show();

 }
}

void loop() {


}
