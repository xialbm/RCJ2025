#include <Wire.h>
int reada = 0;
int readjg = 0;
int anniu1 = 0;
int anniujiasu = 0;
unsigned long time1 = 0;
int showx = 1;
int jtwz1 = 1;
bool readyes = 0;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial3.begin(38400);
}

void loop() {
//anniu();
panduan();
}

void zigbeesend(int zbsj)
{
  Serial3.write(201);
  Serial3.write(zbsj);
}
/*void anniu()
{
  int s1, s2, s3;
  s1 = analogRead(A2);
  s2 = analogRead(A1);
  s3 = analogRead(A0);
    Serial.print(s1); Serial.print("  ");
    Serial.print(s2); Serial.print("  ");
    Serial.println(s3);
  if (s1 < 10 || s2 < 200 || s2 > 800 || s3 < 200 || s3 > 800)
  {
    time1 = millis();
    while (1)
    {
      s1 = analogRead(A2);
      s2 = analogRead(A1);
      s3 = analogRead(A0);

      if (s2 < 300 && anniu1 != 1) anniu1 = 2;//shang
      if (s2 > 700 && anniu1 != 1) anniu1 = 3;//xia
      if (s3 < 300 && anniu1 != 1) anniu1 = 4;//zuo
      if (s3 > 700 && anniu1 != 1) anniu1 = 5;//you
      if (s1 < 50) anniu1 = 1;//anjian

      if (millis() > time1 + 300 - anniujiasu * 10) {
        anniujiasu = anniujiasu + 5;
        if (anniujiasu > 20)anniujiasu = 20;
        break;
      }
      if (s1 > 30 && s2 > 200 && s2 < 800 && s3 > 200 && s3 < 800) {
        anniujiasu = 0;
        break;
      }
    }
  }
  else anniujiasu = 0;
  delay(10);
}*/

void panduan(){
   int s1, s2, s3;
  s1 = analogRead(A2);
  s2 = analogRead(A1);
  s3 = analogRead(A0);
    Serial.print(s1); Serial.print("  ");
    Serial.print(s2); Serial.print("  ");
    Serial.println(s3);
if(s2 < 100 ){
zigbeesend(2);
delay(100);
}
else if(s2 > 800){
zigbeesend(3);
delay(100);
}
else if(s3 < 20 ){
zigbeesend(4);
delay(100);
}
else if(s3 > 800 ){
zigbeesend(5);
delay(100);
}
else if(s1 == 0){
zigbeesend(1);
delay(100);
}
else{
zigbeesend(0);
delay(100);
}
delay(50);
}