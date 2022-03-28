#include <EEPROM.h>
#include <TimerOne.h>
#include <avr/pgmspace.h>
#include "TM1637.h"
#define ON 1
#define OFF 0

#include<Servo.h>
Servo myservo;
float distance;
const int echo=12;
const int trig=7;
float limit=15;
int pos;
int secure=0;
bool ifopen=0;
int pin1=8;//LED
int pin2=6;
volatile bool flagon=true; 

int8_t TimeDisp[] = {0x00,0x00,0x00,0x00};
unsigned char ClockPoint = 1;
unsigned char Update;
unsigned char microsecond_10 = 0;
unsigned char second;
unsigned char _microsecond_10 = 0;
unsigned char _second;
unsigned int eepromaddr;
boolean Flag_ReadTime;

#define CLK A5//pins definitions for TM1637 and can be changed to other ports        
#define DIO A4
TM1637 tm1637(CLK,DIO);

volatile bool flagpause=true;
unsigned char minutes=0;
unsigned char hours=0;
unsigned long oldtime=0;
unsigned long newtime=0;
long interval=1000;
bool flagupdate;

void setup() {
  // put your setup code here, to run once:
  tm1637.set(BRIGHT_TYPICAL);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
  tm1637.init();
  attachInterrupt(0,doPause,RISING);
  pinMode(echo,INPUT);
  pinMode(trig,OUTPUT);
  myservo.attach(11);
  myservo.write(90);
  attachInterrupt(1,steal,RISING);
  pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:
  flagupdate=false;
  if(!flagpause)
  {
    TimeUpdate();
    tm1637.display(TimeDisp);
  }
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);

  distance=pulseIn(echo,HIGH)/58.00;
  if(flagon){
   if(distance<=limit&&ifopen==0){
    for(pos=90;pos>20;--pos){
      myservo.write(pos);
      delay(15);
    }
    ifopen=1;
  }
  if(distance<=limit) secure=0;
  if(distance>limit&&ifopen==1){
    ++secure;
    if(secure>=400){
      for(pos=20;pos<90;++pos){
      myservo.write(pos);
      delay(15);
      }
     secure=0;ifopen=0;
     }
    }
  
  }
 
 else{
 if(distance<=limit){
  digitalWrite(pin1,HIGH);
  tone(pin2,500);
  delay(1000);
  }
  else{noTone(pin2);}
  
  int i;
  i=analogRead(A3);
  if(i<200){
    digitalWrite(pin1,HIGH);
    tone(pin2,500);
    delay(1000);
  }
  else{
    digitalWrite(pin1,LOW);
    noTone(pin2);
  }
 }
}

void TimeUpdate()
{
  newtime=millis();
  if(newtime-oldtime>=interval)
  {
    oldtime=newtime;
    flagupdate=true;      
    }
  if(flagupdate)
  {
    minutes++;
    if(minutes==60)
    {
      minutes=0;
      ++hours;
      if(hours==100)
      {
        minutes=0;
        hours=0;
        }
      }
    }
  if(ClockPoint)tm1637.point(POINT_ON);//POINT_ON = 1,POINT_OFF = 0;
  else tm1637.point(POINT_ON); 
  TimeDisp[2] = minutes / 10;
  TimeDisp[3] = minutes % 10;
  TimeDisp[0] = hours / 10;
  TimeDisp[1] = hours % 10;
  }

void doPause()
{
  if(flagpause)
  {
    flagpause=false;
    }
    else
    {
      flagpause=true;
      }
  }

void steal()
{
  if(flagon)
  {
    flagon=false;
    }
  else
  {
    flagon=true;
    }
  }
