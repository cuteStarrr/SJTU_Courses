int LED=6;

void setup() {
  // put your setup code here, to run once:
pinMode(LED,OUTPUT);
Serial.begin(9600);
analogWrite(LED,255);
delay(1000);
analogWrite(LED,0);
delay(1000);
analogWrite(LED,255);
delay(1000);
analogWrite(LED,0);
delay(1000);
}

int value;
int num;
void loop() {
  // put your main code here, to run repeatedly:
value=analogRead(A1);
Serial.println(value);
delay(1000);
if(value<=100)
{num=map(value,20,100,0,255);
analogWrite(LED,num);
delay(1000);}
if(value>100)
{
  analogWrite(LED,255);
  delay(500);
  analogWrite(LED,0);
  delay(500);
  }
}
