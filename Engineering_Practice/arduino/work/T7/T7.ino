#include<Servo.h>

Servo myservo;
int pos;
void reset();
void setup() {
  // put your setup code here, to run once:
  myservo.attach(6);
  reset();
  Serial.begin(9600);

}
int value;
int num;
int n=1;
void loop() {
  // put your main code here, to run repeatedly:
  for(pos=0;pos<180;++pos)
  {
    value=analogRead(A0);
    Serial.println(value);
    num=map(value,0,1023,100,10);
    myservo.write(pos);
    delay(num);
    }
  for(pos=180;pos>0;--pos)
  {
    value=analogRead(A0);
    Serial.println(value);
    num=map(value,0,1023,100,10);
    myservo.write(pos);
    delay(num);
    }

}

void reset()
{
  int p;
  p=myservo.read();
  for(;p>0;--p)
  {
    myservo.write(p);
    delay(100);
    }
  }
