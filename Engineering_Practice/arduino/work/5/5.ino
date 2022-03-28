int pin=8;
int button=2;
int buttonState=0;
void setup() {
  // put your setup code here, to run once:
pinMode(pin,OUTPUT);
pinMode(button,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
buttonState=digitalRead(button);
if(buttonState==HIGH)
{
  delay(80);
  if(buttonState==HIGH)
      {
      digitalWrite(pin,HIGH); 
      delay(1000);
      digitalWrite(pin,LOW);
      delay(1000);
      }
}
else {digitalWrite(pin,LOW);}
}
