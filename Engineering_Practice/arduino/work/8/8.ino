int pin=6;
void setup() {
  // put your setup code here, to run once:

}
int num=0;
void loop() {
  // put your main code here, to run repeatedly:
if(num<256)
{
analogWrite(pin,num);
delay(1000);
++num;
}
}
