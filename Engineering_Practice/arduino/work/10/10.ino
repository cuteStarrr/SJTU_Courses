int LED1=4;
int LED2=7;
int LED3=2;
void setup() {
  // put your setup code here, to run once:
pinMode(LED1,OUTPUT);
pinMode(LED2,OUTPUT);
pinMode(LED3,OUTPUT);
Serial.begin(9600);
}
int value;
void loop() {
  // put your main code here, to run repeatedly:
  value=analogRead(A1);
  Serial.println(value);
  delay(1000);
  if (value<=70)
  {
    digitalWrite(LED1,HIGH);
    digitalWrite(LED2,LOW);
    digitalWrite(LED3,LOW);
    delay(1000);
    }
  else if(value<=105)
       {
        digitalWrite(LED1,HIGH);
        digitalWrite(LED2,HIGH);
        digitalWrite(LED3,LOW);
        delay(1000);
        }
        else {
          digitalWrite(LED1,HIGH);
          digitalWrite(LED2,HIGH);
          digitalWrite(LED3,HIGH);
          delay(1000);
          }

}
