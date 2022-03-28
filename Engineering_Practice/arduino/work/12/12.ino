#include<Servo.h>

Servo myservo;
int pos;
void setup() {
  // put your setup code here, to run once:
  myservo.attach(6);

}

void loop() {
  // put your main code here, to run repeatedly:
  for(pos=0;pos<180;++pos)
  {
    myservo.write(pos);
    delay(100);
    }
  for(pos=180;pos>0;--pos)
  {
    myservo.write(pos);
    delay(100);
    }

}
