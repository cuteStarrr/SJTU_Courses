int pinB=3;
int pinG=5;
int pinR=6;
void setup() {
  // put your setup code here, to run once:
pinMode(pinB,OUTPUT);
pinMode(pinG,OUTPUT);
pinMode(pinR,OUTPUT);
}
float Value;
float num;
int k=0;
void loop() {
  // put your main code here, to run repeatedly:
Value=analogRead(A0);
k=Value/341;
switch(k){
case 0:
num=map(Value,0,341,0,255);
analogWrite(pinB,num);
analogWrite(pinR,0);
analogWrite(pinG,0);
delay(1000);
break;
case 1:
num=map(Value,342,683,0,255);
analogWrite(pinG,num);
analogWrite(pinR,0);
analogWrite(pinB,0);
delay(1000);
break;
case 2:
num=map(Value,684,1023,0,255);
analogWrite(pinR,num);
analogWrite(pinB,0);
analogWrite(pinG,0);
delay(1000);
break;
}
}
