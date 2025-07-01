int stepx=0;


void setup() {

  Serial2.begin(38400);
  while(1)
  {
    receivenow();
    if(stepx>=5){btsend(5);break;}
  }

 while(1)
  {
    receivenow();
    if(stepx>=20){break;}/////////自己定值
  }



}

void loop() {
  

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