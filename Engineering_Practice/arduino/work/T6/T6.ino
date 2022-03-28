int Soundpin=2;
void setup() {
  // put your setup code here, to run once:
  pinMode(Soundpin,OUTPUT);
  Serial.begin(9600);

}
int value;
int num;
void loop() {
  // put your main code here, to run repeatedly:
  value=analogRead(A1);
  Serial.println(value);
  delay(1000);
  num=map(value,20,160,0,1500)+1000;
  tone(Soundpin,num);

}
