#include <SCServo.h>
#include <Wire.h>


SMS_STS scmain;


#define AH1 1
#define AH2 2
#define AH3 3
#define AL1 4
#define AL2 5
#define AL3 6
#define BH1 7
#define BH2 8
#define BH3 9
#define BL1 10
#define BL2 11
#define BL3 12
#define CH1 13
#define CH2 14
#define CH3 15
#define CL1 16
#define CL2 17
#define CL3 18
#define DH1 19
#define DH2 20
#define DH3 21
#define DL1 22
#define DL2 23
#define DL3 24


#define AH1BAS 500
#define AH2BAS 500
#define AH3BAS 500
#define AL1BAS 500
#define AL2BAS 500
#define AL3BAS 500
#define BH1BAS 500
#define BH2BAS 500
#define BH3BAS 500
#define BL1BAS 500
#define BL2BAS 500
#define BL3BAS 500
#define CH1BAS 500
#define CH2BAS 500
#define CH3BAS 500
#define CL1BAS 500
#define CL2BAS 500
#define CL3BAS 500
#define DH1BAS 500
#define DH2BAS 500
#define DH3BAS 500
#define DL1BAS 500
#define DL2BAS 500
#define DL3BAS 500

#define PWMB 35
#define PWMA 36
#define PWMC 37//////
#define PWMD 38//////
#define duoji1 1//////
#define duoji2 2//////




int LRold[]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int deltaLR[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int AH1GO= 500+deltaLR[0];
int AH2GO= 500+deltaLR[1];
int AH3GO= 500+deltaLR[2];
int AL1GO= 500+deltaLR[3];
int AL2GO= 500+deltaLR[4];
int AL3GO= 500+deltaLR[5];
int BH1GO= 500+deltaLR[6];
int BH2GO= 500+deltaLR[7];
int BH3GO= 500+deltaLR[8];
int BL1GO= 500+deltaLR[9];
int BL2GO= 500+deltaLR[10];
int BL3GO= 500+deltaLR[11];
int CH1GO= 500+deltaLR[12];
int CH2GO= 500+deltaLR[13];
int CH3GO= 500+deltaLR[14];
int CL1GO= 500+deltaLR[15];
int CL2GO= 500+deltaLR[16];
int CL3GO= 500+deltaLR[17];
int DH1GO= 500+deltaLR[18];
int DH2GO= 500+deltaLR[19];
int DH3GO= 500+deltaLR[20];
int DL1GO= 500+deltaLR[21];
int DL2GO= 500+deltaLR[22];
int DL3GO= 500+deltaLR[23];
int LRnow[]={AH1GO,AH2GO,AH3GO,AL1GO,AL2GO,AL3GO,BH1GO,BH2GO,BH3GO,BL1GO,BL2GO,BL3GO,CH1GO,CH2GO,CH3GO,CL1GO,CL2GO,CL3GO,DH1GO,DH2GO,DH3GO,DL1GO,DL2GO,DL3GO};

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





void setup() {
  ledcAttachChannel(PWMA, 500, 8, 1);
  ledcAttachChannel(PWMB, 500, 8, 2);
  ledcAttachChannel(PWMC, 500, 8, 3);
  ledcAttachChannel(PWMD, 500, 8, 4);
  ledcAttachChannel(duoji1, 50, 12, 5);
  ledcAttachChannel(duoji2, 50, 12, 6);

  Wire.begin();
  Serial.begin(9600);
  delay(100);
  Serial2.begin(115200);
  delay(100);
  //Serial2.begin(38400);
  //delay(100);
  scmain.pSerial = &Serial2;
  delay(100);
  speedsc=0.5;
  SCPUT(AH1GO,AH2GO,AH3GO,AL1GO,AL2GO,AL3GO,BH1GO,BH2GO,BH3GO,BL1GO,BL2GO,BL3GO,CH1GO,CH2GO,CH3GO,CL1GO,CL2GO,CL3GO,DH1GO,DH2GO,DH3GO,DL1GO,DL2GO,DL3GO);
  scall();
  delay(rtime+500);

  duoji();
}


void loop() {
  speedsc=1;
  SCPUT(371,1881,-1,1678,1569,-1,467,2288,-1,1623,498,-1,313,2386,-1,1694,525,-1,361,2437,-1,1656,487,-1);
  scall();
/*SCPUT(377,657,-1,1683,2739,-1,1424,390,-1,602,2411,-1,329,1207,-1,1705,1689,-1,1452,506,-1,593,2415,-1);
  scall();
  delay(4200);
SCPUT(803,729,-1,664,2839,-1,1478,2614,-1,631,108,-1,1379,1201,-1,1302,1794,-1,1359,2800,-1,570,132,-1);
  scall();
  delay(4200);
SCPUT(834,1656,-1,643,2998,-1,1474,2611,-1,631,108,-1,1386,1007,-1,1269,848,-1,1367,2800,-1,820,281,-1);
  scall();
  delay(4800);
SCPUT(887,2274,-1,604,2963,-1,1474,2612,-1,631,108,-1,1368,1000,-1,1271,69,-1,1367,2799,-1,933,304,-1);
  scall();
  delay(4800);
SCPUT(380,2293,-1,1236,2893,-1,1474,2614,-1,631,108,-1,872,1168,-1,1728,55,-1,1361,2800,-1,929,303,-1);
  scall();
  delay(4800);
SCPUT(356,2342,-1,1188,1919,-1,1482,2614,-1,669,123,-1,817,2041,-1,1871,91,-1,1339,2800,-1,589,138,-1);
  scall();
  delay(4800);
SCPUT(308,2358,-1,1326,1143,-1,1526,2614,-1,740,123,-1,765,2862,-1,1814,7,-1,1339,2800,-1,592,138,-1);
  scall();
  delay(4800);
SCPUT(371,1881,-1,1678,1569,-1,467,2288,-1,1623,498,-1,313,2386,-1,1694,525,-1,361,2437,-1,1656,487,-1);
  scall();
  delay(4800);
/*SCPUT(0,650,-1,1704,2728,-1,1726,373,-1,631,2413,-1,653,1279,-1,1829,1779,-1,1172,578,-1,639,2430,-1);
  scall();
  delay(4800);
SCPUT(0,618,-1,1606,2870,-1,1766,432,-1,602,2149,-1,681,1197,-1,1705,1766,-1,1118,417,-1,662,2242,-1);
  scall();
  delay(4800);
SCPUT(466,531,-1,1598,2790,-1,1481,432,-1,672,2102,-1,387,1195,-1,1755,1765,-1,1354,432,-1,662,2245,-1);
  scall();
  delay(4800);
SCPUT(413,540,-1,1641,2664,-1,1481,432,-1,639,2310,-1,387,1193,-1,1736,1623,-1,1356,432,-1,662,2446,-1);  
scall();
  delay(4800);
SCPUT(413,1698,-1,1570,3372,-1,1439,476,-1,262,2372,-1,494,612,-1,1641,692,-1,1743,602,-1,787,2099,-1);
  scall();
  delay(4800);
SCPUT(355,2228,-1,1683,1753,-1,1621,368,-1,738,2296,-1,399,2307,-1,1661,64,-1,1210,756,-1,269,2359,-1);
  scall();
  delay(4800);
SCPUT(389,2366,-1,1701,1177,-1,1621,368,-1,645,2277,-1,405,2793,-1,1755,44,-1,1210,564,-1,268,2403,-1);
  scall();
  delay(4800);
SCPUT(371,1881,-1,1678,1569,-1,467,2288,-1,1623,498,-1,313,2386,-1,1694,525,-1,361,2437,-1,1656,487,-1);
  scall();*/
  delay(4800);
}




void SCPUT(int PAH1,int PAH2,int PAH3,int PAL1,int PAL2,int PAL3,int PBH1,int PBH2,int PBH3,int PBL1,int PBL2,int PBL3,int PCH1,int PCH2,int PCH3,int PCL1,int PCL2,int PCL3,int PDH1,int PDH2,int PDH3,int PDL1,int PDL2,int PDL3)
{
  LRnow[0]=PAH1; LRnow[1]=PAH2; LRnow[2]=PAH3; LRnow[3]=PAL1; LRnow[4]=PAL2; LRnow[5]=PAL3;
  LRnow[6]=PBH1; LRnow[7]=PBH2; LRnow[8]=PBH3; LRnow[9]=PBL1; LRnow[10]=PBL2;LRnow[11]=PBL3;
  LRnow[12]=PCH1;LRnow[13]=PCH2;LRnow[14]=PCH3;LRnow[15]=PCL1;LRnow[16]=PCL2;LRnow[17]=PCL3;
  LRnow[18]=PDH1;LRnow[19]=PDH2;LRnow[20]=PDH3;LRnow[21]=PDL1;LRnow[22]=PDL2;LRnow[23]=PDL3;
}

void scall()
{
  
  int rmax=0;
  int rqd=99;
  float gospeed=0;

  for (int scalli=0;scalli<24;scalli++)
  {
    if(abs(LRold[scalli]-LRnow[scalli])>rmax){rmax=abs(LRold[scalli]-LRnow[scalli]);}
  }
  rtime=(rmax*10/speedsc)/8+15;
  for (int scalli=0;scalli<24;scalli++)
  {
    if(scalli==0) rqd=AH1;    if(scalli==1) rqd=AH2;    if(scalli==2) rqd=AH3;    if(scalli==3) rqd=AL1;    if(scalli==4) rqd=AL2;    if(scalli==5) rqd=AL3;    
    if(scalli==6) rqd=BH1;    if(scalli==7) rqd=BH2;    if(scalli==8) rqd=BH3;    if(scalli==9) rqd=BL1;    if(scalli==10) rqd=BL2;   if(scalli==11) rqd=BL3;
    if(scalli==12) rqd=CH1;   if(scalli==13) rqd=CH2;   if(scalli==14) rqd=CH3;   if(scalli==15) rqd=CL1;   if(scalli==16) rqd=CL2;   if(scalli==17) rqd=CL3;
    if(scalli==18) rqd=DH1;   if(scalli==19) rqd=DH2;   if(scalli==20) rqd=DH3;   if(scalli==21) rqd=DL1;   if(scalli==22) rqd=DL2;   if(scalli==23) rqd=DL3;
    if(abs(LRold[scalli]-LRnow[scalli])>0){gospeed=1000*float(abs(LRold[scalli]-LRnow[scalli]))/(rtime);if(gospeed>1500)gospeed=1500;scmain.RegWritePosEx(rqd, LRnow[scalli]+deltaLR[scalli], gospeed,950);Serial.println(gospeed);}
    LRold[scalli]=LRnow[scalli];
  }  
   scmain.RegWriteAction();

  
}

void duoji(){
  ledcWriteChannel(5,100);//duoji1
  ledcWriteChannel(6,500);//duoji2
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