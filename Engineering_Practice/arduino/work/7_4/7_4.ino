void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}
float Value;
void loop() {
  // put your main code here, to run repeatedly:
Value=analogRead(A0);
Serial.println(Value);
Serial.println(Value*10/1023);
delay(1000);
}
