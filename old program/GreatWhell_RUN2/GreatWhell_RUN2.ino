#include <SCServo.h>
#include <Wire.h>


SMS_STS scmain;


#define AH1 1
#define AH2 2
#define AL1 4
#define AL2 5
#define BH1 7
#define BH2 8
#define BL1 10
#define BL2 11
#define CH1 13
#define CH2 14
#define CL1 16
#define CL2 17
#define DH1 19
#define DH2 20
#define DL1 22
#define DL2 23


#define AH1BAS 500
#define AH2BAS 500
#define AL1BAS 500
#define AL2BAS 500
#define AL3BAS 500
#define BH1BAS 500
#define BH2BAS 500
#define BL1BAS 500
#define BL2BAS 500
#define CH1BAS 500
#define CH2BAS 500
#define CL1BAS 500
#define CL2BAS 500
#define DH1BAS 500
#define DH2BAS 500
#define DL1BAS 500
#define DL2BAS 500

#define PWMB 35
#define PWMA 36
#define PWMC 37//////
#define PWMD 38//////
#define duoji1 1//////
#define duoji2 2//////




int LRold[]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int deltaLR[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int AH1GO= 500+deltaLR[0];
int AH2GO= 500+deltaLR[1];
int AL1GO= 500+deltaLR[3];
int AL2GO= 500+deltaLR[4];
int BH1GO= 500+deltaLR[6];
int BH2GO= 500+deltaLR[7];
int BL1GO= 500+deltaLR[9];
int BL2GO= 500+deltaLR[10];
int CH1GO= 500+deltaLR[12];
int CH2GO= 500+deltaLR[13];
int CL1GO= 500+deltaLR[15];
int CL2GO= 500+deltaLR[16];
int DH1GO= 500+deltaLR[18];
int DH2GO= 500+deltaLR[19];
int DL1GO= 500+deltaLR[21];
int DL2GO= 500+deltaLR[22];
int LRnow[]={AH1GO,AH2GO,AL1GO,AL2GO,BH1GO,BH2GO,BL1GO,BL2GO,CH1GO,CH2GO,CL1GO,CL2GO,DH1GO,DH2GO,DL1GO,DL2GO};

int compassyes = 0;
//本机编号
int beginname = 8; //3左4右
//复眼变量
int td = 0;
int zhi = 0;
unsigned char c = 0;
int zuoyoucha = 0;
//指南针变量
int zhinz = 0;
//程序用变量
int outx = 0;
float speedsc=1;
//计算出的运动时间
int rtime=0;
long timer=0;




void setup() {
  pinMode(35,OUTPUT);
  pinMode(36,OUTPUT);
  pinMode(37,OUTPUT);
  pinMode(38,OUTPUT);
  pinMode(38,OUTPUT);
  pinMode(40,OUTPUT);
  Wire.begin();
  Serial.begin(9600);
  delay(200);
  Serial2.begin(38400);
  delay(200);
  scmain.pSerial = &Serial2;
  delay(200);



  speedsc=0.5;
  SCPUT(1003,1137,1201,2338,907,1817,1092,1152,791,2192,1197,1301,812,2008,1163,974);
  scall();
    delay(500);scmain.RegWriteAction();
  delay(1500);
  speedsc=1;
  SCPUT(1344,622,625,2843,489,973,1660,1991,270,951,632,1727,1272,1237,1691,1926);
  scall();
    Serial.println("xx2");

  delay(1500);

  sportUPDN(255);
  timer=millis();
  while(1)
  {
    if(millis()-timer>30000||digitalRead(1)==0) break;
    delay(20);
  }
 

}


void loop() {
 
  sportUPDN(-255);
  delay(22000);
  speedsc=1;
  SCPUT(1003,1137,1201,2338,907,1817,1092,1152,791,2192,1197,1301,812,2008,1163,974);
  scall();
  delay(2200);
 sportUPDN(0);
SCPUT(343,2235,1659,1202,448,2595,1686,161,365,2785,1647,144,377,2737,1632,172);
 scall();
  delay(1200);
  sportUPDN(255);
  delay(7000);
  sportUPDN(0);
sport(100,100);

  delay(4800);
   sport(0,0);
   while(1){}
}




void SCPUT(int PAH1,int PAH2,int PAL1,int PAL2,int PBH1,int PBH2,int PBL1,int PBL2,int PCH1,int PCH2,int PCL1,int PCL2,int PDH1,int PDH2,int PDL1,int PDL2)
{
  LRnow[0]=PAH1; LRnow[1]=PAH2;  LRnow[2]=PAL1; LRnow[3]=PAL2;
  LRnow[4]=PBH1; LRnow[5]=PBH2;  LRnow[6]=PBL1; LRnow[7]=PBL2;
  LRnow[8]=PCH1;LRnow[9]=PCH2; LRnow[10]=PCL1;LRnow[11]=PCL2;
  LRnow[12]=PDH1;LRnow[13]=PDH2; LRnow[14]=PDL1;LRnow[15]=PDL2;
}

void scall()
{
  
  int rmax=0;
  int rqd=99;
  float gospeed=0;

  for (int scalli=0;scalli<16;scalli++)
  {
    if(abs(LRold[scalli]-LRnow[scalli])>rmax){rmax=abs(LRold[scalli]-LRnow[scalli]);}
     
  }
  
  rtime=(rmax*10/speedsc)/8+15;
  for (int scalli=0;scalli<16;scalli++)
  {
    if(scalli==0) rqd=AH1;    if(scalli==1) rqd=AH2;  if(scalli==2) rqd=AL1;    if(scalli==3) rqd=AL2;      
    if(scalli==4) rqd=BH1;    if(scalli==5) rqd=BH2;  if(scalli==6) rqd=BL1;    if(scalli==7) rqd=BL2;  
    if(scalli==8) rqd=CH1;   if(scalli==9) rqd=CH2;   if(scalli==10) rqd=CL1;   if(scalli==11) rqd=CL2;   
    if(scalli==12) rqd=DH1;   if(scalli==13) rqd=DH2; if(scalli==14) rqd=DL1;   if(scalli==15) rqd=DL2;  
    if(abs(LRold[scalli]-LRnow[scalli])>0){gospeed=1000*float(abs(LRold[scalli]-LRnow[scalli]))/(rtime);if(gospeed>1500)gospeed=1500;scmain.RegWritePosEx(rqd, LRnow[scalli]+deltaLR[scalli], gospeed,950);Serial.println(gospeed);}
    LRold[scalli]=LRnow[scalli];
  }  
   scmain.RegWriteAction();

  
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


void sport(int speeda,int speedb)
{
  int outa,outpwma,outb,outpwmb;
  if(speeda>0) 
  {outa=0;   outpwma=speeda;}
  else if(speeda<0)
  {outa=1;   outpwma=-speeda;}
  else 
  {outa=0;   outpwma=0;}

    if(speedb>0) 
  {outb=1;   outpwmb=speedb;}
  else if(speedb<0)
  {outb=0;   outpwmb=-speedb;}
  else 
  {outb=0;   outpwmb=0;}
  digitalWrite(36,outa);
  analogWrite(35,outpwma);
  digitalWrite(38,outb);
  analogWrite(37,outpwmb);
}

void sportUPDN(int speedc)
{
  int outc,outpwmc;
  if(speedc>0) 
  {outc=0;   outpwmc=speedc;}
  else if(speedc<0)
  {outc=1;   outpwmc=-speedc;}
  else 
  {outc=0;   outpwmc=0;}


  digitalWrite(40,outc);
  analogWrite(39,outpwmc);

}