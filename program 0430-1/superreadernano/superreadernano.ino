#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 4);


int stepx=0;


void setup() {
  mySerial.begin(38400);
  while(1)
  {
    receivenow();
    if(stepx>=5){btsend(5);break;}
  }

}

void loop() {
  delay(1000);

}


void receivenow()
{
  int getnrnow=0;
  if(mySerial.available())
  {
    delay(25);
    while(mySerial.available())
    {
      if(mySerial.read()==254)
      getnrnow=mySerial.read();
      if(getnrnow>stepx){stepx=getnrnow;}
    }
  }

}
void btsend(int btnr)
{
  mySerial.write(254);
  mySerial.write(btnr);
}