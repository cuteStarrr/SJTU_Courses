#include<MsTimer2.h>
int LED=8;
void flash();
void setup() {
  // put your setup code here, to run once:
  pinMode(LED,OUTPUT);
  MsTimer2::set(1000,flash);
  MsTimer2::start();

}

void loop() {
  // put your main code here, to run repeatedly:

}

void flash()
{
  static bool now=HIGH;
  digitalWrite(LED,now);
  now=!now;
  }
