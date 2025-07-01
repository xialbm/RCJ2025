int stepx=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(33,OUTPUT);
  pinMode(32,OUTPUT);
  pinMode(27,OUTPUT);
  ledcAttachChannel(33, 50, 12, 1);//100桌子内，320桌子外
  ledcAttachChannel(32, 50, 12, 2);//放80，240抬
  ledcAttachChannel(27, 50, 12, 3);//120开，230夹

  Serial2.begin(38400,SERIAL_8N1,16,17);
while(1)
  { receivenow();
    if(stepx>=5){btsend(7);break;}
  }
  ledcWrite(33, 100);
  ledcWrite(32, 80);
  ledcWrite(27, 270);
  delay(3000);
  
  
  while(1)
  { receivenow();
    if(stepx>=30){break;}
  }
  renghua();
}

int zhua_x,zhua_y,jia;

void loop() {}

void renghua()
{ ledcWrite(32, 240);
  delay(1000);
  ledcWrite(33, 320);
  delay(700);
  ledcWrite(32, 70);
  ledcWrite(27, 120);
  delay(2000);
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