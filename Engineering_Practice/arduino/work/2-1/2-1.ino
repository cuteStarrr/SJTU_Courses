const int LedPin=8;
void setup() {
  // put your setup code here, to run once:
pinMode(LedPin,OUTPUT);
Serial.begin(9600);
}
int n=0;
void loop() {
  // put your main code here, to run repeatedly:
while(n<2){
  digitalWrite(LedPin,HIGH);
  delay(1000);
  digitalWrite(LedPin,LOW);
  delay(1000);
  ++n;
  Serial.print("n=");
  Serial.println(n);
}

}
