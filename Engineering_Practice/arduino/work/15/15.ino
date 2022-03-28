int pin1=2;
int pin2=3;
int LED=8;

void LEDlight()
{
  if(digitalRead(pin1)==HIGH)
     Serial.println("Open!");
  digitalWrite(LED,HIGH);
  }

void LEDclose()
{
  if(digitalRead(pin2)==HIGH)
     Serial.println("Close!");
  digitalWrite(LED,LOW);
  }

void setup() {
  // put your setup code here, to run once:
  pinMode(LED,OUTPUT);
  pinMode(pin1,INPUT);
  pinMode(pin2,INPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(pin1),LEDlight,CHANGE);
  attachInterrupt(digitalPinToInterrupt(pin2),LEDclose,CHANGE);
  digitalWrite(LED,LOW);

}

void loop() {
  // put your main code here, to run repeatedly:

}
