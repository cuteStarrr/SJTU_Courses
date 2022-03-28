int pin=8;
int button=2;
int buttonState=0;
int num=1;
int n=0;
void setup() {
  // put your setup code he+re, to run once:
pinMode(pin,OUTPUT);
pinMode(button,INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(pin,LOW);
buttonState=digitalRead(button);
if(buttonState==HIGH)
{
  delay(80);
  if(buttonState==HIGH)
  {
  if(num%4==0)
  {
    digitalWrite(pin,HIGH);
    delay(1000);
    digitalWrite(pin,LOW);
    delay(1000);
    Serial.print("num=");
    Serial.print(num);
    Serial.println(",open");
    ++num;
    }
   else
   {
    delay(1000);
    Serial.print("num=");
    Serial.print(num);
    Serial.println(",close");
    ++num;}
  }
}
}
