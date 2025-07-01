#include <Wire.h>
#include "paj7620.h"
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixels1(8, 11, NEO_GRB + NEO_KHZ800);

#define GES_REACTION_TIME		500				
#define GES_ENTRY_TIME			800				
#define GES_QUIT_TIME			500
int  zhiling;
int stepx=0;
void setup()
{
  //Serial2.begin(38400);
  Serial.begin(9600);
  pixels1.begin();



// while(1)
  //{
 //   receivenow();
 //   if(stepx>=5){btsend(5);break;}
 // }

  for(int i=0;i<8;i++){
  pixels1.setPixelColor(i, pixels1.Color(200, 200, 200)); }
  pixels1.show();
  delay(2000);
  pixels1.clear();
  pixels1.show();
	uint8_t error = 0;
	error = paj7620Init();	
	if (error) 
	{

	}
	else
	{
	
	}
 while(1){
 Serial.println(gethandonce());
	delay(100);
  zhiling=gethandonce();

    if(zhiling!=0){/*btsend(111);*/pixels1.clear(); pixels1.show();for(int i=0;i<8;i++){pixels1.setPixelColor(i, pixels1.Color(255, 0, 0));} pixels1.show();delay(3000);pixels1.clear(); while(1){Serial.println(gethandonce());delay(100);zhiling=gethandonce();if(zhiling!=0)/*btsend(222);*/break;}for(int i=0;i<8;i++){pixels1.setPixelColor(i, pixels1.Color(0, 255, 0));} pixels1.show();delay(3000);pixels1.clear();  pixels1.show();}
    
    else {}

 }


}

void loop()
{

}


int gethandonce()
{
  uint8_t data = 0, data1 = 0, error;
	int endhand=0;
	error = paj7620ReadReg(0x43, 1, &data);			
	if (!error) 
	{
		switch (data) 								
		{
			case GES_RIGHT_FLAG:
       
				break;
			case GES_LEFT_FLAG: 
      
				break;
			case GES_UP_FLAG:
				delay(GES_ENTRY_TIME);
				paj7620ReadReg(0x43, 1, &data);
				if(data == GES_FORWARD_FLAG) 
				{
					
				}
				else if(data == GES_BACKWARD_FLAG) 
				{
					
				}
				else
				{
					endhand=1;
					//Serial.println("Up");
				}          
				break;
			case GES_DOWN_FLAG:
				delay(GES_ENTRY_TIME);
				paj7620ReadReg(0x43, 1, &data);
				if(data == GES_FORWARD_FLAG) 
				{

				}
				else if(data == GES_BACKWARD_FLAG) 
				{

				}
				else
				{
					endhand=2;
					//Serial.println("Down");
				}          
				break;
			case GES_FORWARD_FLAG:

				break;
			case GES_BACKWARD_FLAG:		  

				break;
			case GES_CLOCKWISE_FLAG:
				//Serial.println("Clockwise");
				endhand=3;
				break;
			case GES_COUNT_CLOCKWISE_FLAG:
				//Serial.println("anti-clockwise");
				endhand=4;
				break;  
			default:
				paj7620ReadReg(0x44, 1, &data1);
				break;
		}
	}
	return endhand;
}

/*void receivenow()
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
}*/