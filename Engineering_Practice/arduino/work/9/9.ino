int pin=6;
void setup() {
  // put your setup code here, to run once:

}
float Value;
float num;
void loop() {
  // put your main code here, to run repeatedly:
Value=analogRead(A0);
num=map(Value,0,1023,0,255);
analogWrite(pin,num);
delay(1000);
}
