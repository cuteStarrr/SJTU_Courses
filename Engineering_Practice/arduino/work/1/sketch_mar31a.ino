const int LedPin=8;
void setup() {
  // put your setup code here, to run once:
pinMode(LedPin,OUTPUT);
}
int n=0;
void loop() {
  // put your main code here, to run repeatedly:
while(n<3){
  digitalWrite(LedPin,HIGH);
  delay(1000);
  digitalWrite(LedPin,LOW);
  delay(1000);
  ++n;
}

}
