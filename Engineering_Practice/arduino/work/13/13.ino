#include<Servo.h>

Servo myservo;
int pos;
int oldpos;

void setup() {
  // put your setup code here, to run once:
  myservo.attach(6);

}
int value;
int num;
void loop() {
  // put your main code here, to run repeatedly:
  value=analogRead(A1);
  num=map(value,0,1023,0,180);
  oldpos=myservo.read();
  if(oldpos<num)
     for(pos=oldpos;pos<num+1;++pos)
     {
      myservo.write(pos);
      delay(50);
      }
   else for(pos=oldpos;pos>num-1;--pos)
     {
      myservo.write(pos);
      delay(50);
      }

}
