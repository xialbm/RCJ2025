#include <SCServo.h>


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



SMS_STS sc;

int AH1p,AH2p,AL1p,AL2p,BH1p,BH2p,BL1p,BL2p,CH1p,CH2p,CL1p,CL2p,DH1p,DH2p,DL1p,DL2p;
int Voltage;
int Temper;

void setup()
{

  Serial2.begin(38400);
  delay(100);
  Serial.begin(9600);
  delay(100);
  sc.pSerial = &Serial2;
  delay(300);
}

void loop()
{

getpos();
posshow();
delay(3500);

  
 

}

void getpos()
{
    Voltage = sc.ReadVoltage(1);
    Temper = sc.ReadTemper(1);

  AH1p = sc.ReadPos(AH1);delay(10);
  AH2p = sc.ReadPos(AH2);delay(10);
  AL1p = sc.ReadPos(AL1);delay(10);
  AL2p = sc.ReadPos(AL2);delay(10);
  BH1p = sc.ReadPos(BH1);delay(10);
  BH2p = sc.ReadPos(BH2);delay(10);
  BL1p = sc.ReadPos(BL1);delay(10);
  BL2p = sc.ReadPos(BL2);delay(10);
  CH1p = sc.ReadPos(CH1);delay(10);
  CH2p = sc.ReadPos(CH2);delay(10);
  CL1p = sc.ReadPos(CL1);delay(10);
  CL2p = sc.ReadPos(CL2);delay(10);
  DH1p = sc.ReadPos(DH1);delay(10);
  DH2p = sc.ReadPos(DH2);delay(10);
  DL1p = sc.ReadPos(DL1);delay(10);
  DL2p = sc.ReadPos(DL2);delay(10);
}

void posshow()
{
Serial.println("");

  Serial.print("         A                      C                ");
    Serial.print("   Temperature:");
  Serial.print(Temper, DEC);
  Serial.print("    ");
  Serial.print("Voltage:");
  Serial.println(Voltage, DEC);
  
Serial.print("H    ");
Serial.print(AH1p);
Serial.print(" ");
Serial.print(AH2p);
Serial.print("            ");
Serial.print(CH1p);
Serial.print(" ");
Serial.print(CH2p);
Serial.println("");
Serial.print("L    ");
Serial.print(AL1p);
Serial.print(" ");
Serial.print(AL2p);
Serial.print("            ");
Serial.print(CL1p);
Serial.print(" ");
Serial.print(CL2p);
Serial.println("");
Serial.println("         B                      D    ");
Serial.print("H    ");
Serial.print(BH1p);
Serial.print(" ");
Serial.print(BH2p);
Serial.print("            ");
Serial.print(DH1p);
Serial.print(" ");
Serial.print(DH2p);
Serial.println("");
Serial.print("L    ");
Serial.print(BL1p);
Serial.print(" ");
Serial.print(BL2p);
Serial.print("            ");
Serial.print(DL1p);
Serial.print(" ");
Serial.print(DL2p);
Serial.println("");
Serial.print("SCPUT(");
Serial.print(AH1p);Serial.print(",");Serial.print(AH2p);Serial.print(",");
Serial.print(AL1p);Serial.print(",");Serial.print(AL2p);Serial.print(",");
Serial.print(BH1p);Serial.print(",");Serial.print(BH2p);Serial.print(",");
Serial.print(BL1p);Serial.print(",");Serial.print(BL2p);Serial.print(",");
Serial.print(CH1p);Serial.print(",");Serial.print(CH2p);Serial.print(",");
Serial.print(CL1p);Serial.print(",");Serial.print(CL2p);Serial.print(",");
Serial.print(DH1p);Serial.print(",");Serial.print(DH2p);Serial.print(",");
Serial.print(DL1p);Serial.print(",");Serial.print(DL2p);
Serial.println(");");
}