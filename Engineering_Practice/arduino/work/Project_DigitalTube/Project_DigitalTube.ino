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
int pin1=8;
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
volatile bool digitalflagon=false;
char command;

#define CLK A4//pins definitions for TM1637 and can be changed to other ports        
#define DIO A5
#define button 2
TM1637 tm1637(CLK,DIO);

void setup()
{
  tm1637.set(BRIGHT_TYPICAL);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
  tm1637.init();
  Timer1.initialize(10000);//timing for 10ms
  Timer1.attachInterrupt(TimingISR);//declare the interrupt serve routine:TimingISR  
  attachInterrupt(0,isstop,RISING);
  //pinMode(echo,INPUT);
  //pinMode(trig,OUTPUT);
  //pinMode(pin1,OUTPUT);
  myservo.attach(5);
  myservo.write(90);
}
void loop()
{
  //digitalWrite(trig,LOW);
  //delayMicroseconds(2);
  //digitalWrite(trig,HIGH);
  //delayMicroseconds(10);
  //digitalWrite(trig,LOW);
  
  switch(command)
  {
    case 'S':stopwatchStart();break;
    case 'P':stopwatchPause();break;
    default:break;
  }
  if(Update == ON)
  {
    TimeUpdate();
    tm1637.display(TimeDisp);
  }
  distance=pulseIn(echo,HIGH)/58.00;
  if(flagon){
   //if(distance<=limit&&ifopen==0){
    for(pos=90;pos>20;--pos){
      myservo.write(pos);
      delay(15);
    }
    ifopen=1;
    digitalWrite(pin1,HIGH);
  //}
  if(distance<=limit) secure=0;
  if(distance>limit&&ifopen==1){
    ++secure;
    if(secure>=400){
      for(pos=20;pos<90;++pos){
      myservo.write(pos);
      delay(15);
      }
     secure=0;ifopen=0;
     digitalWrite(pin1,LOW);
     }
    }
  
  }
 

}
//************************************************
void isstop()
{
  if(digitalflagon)
  {
    command='P';
    digitalflagon=false;
    }
  else
  {
    command='S';
    digitalflagon=true;
    }
  }




void TimingISR()
{
  microsecond_10 ++;
  Update = ON;
  if(microsecond_10 == 100){
    second ++;
    if(second == 60)
    {
      second = 0;
    }
    microsecond_10 = 0;  
  }
  ClockPoint = (~ClockPoint) & 0x01;
  if(Flag_ReadTime == 0)
  {
    _microsecond_10 = microsecond_10;
    _second = second;
  }
}
void TimeUpdate(void)
{
  if(ClockPoint)tm1637.point(POINT_ON);//POINT_ON = 1,POINT_OFF = 0;
  else tm1637.point(POINT_ON); 
  TimeDisp[2] = _microsecond_10 / 10;
  TimeDisp[3] = _microsecond_10 % 10;
  TimeDisp[0] = _second / 10;
  TimeDisp[1] = _second % 10;
  Update = OFF;
}
void stopwatchStart()//timer1 on
{
  Flag_ReadTime = 0;
  TCCR1B |= Timer1.clockSelectBits; 
}
void stopwatchPause()//timer1 off if [CS12 CS11 CS10] is [0 0 0].
{
  TCCR1B &= ~(_BV(CS10) | _BV(CS11) | _BV(CS12));
}
