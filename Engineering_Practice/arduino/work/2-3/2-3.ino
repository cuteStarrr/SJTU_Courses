int incomingByte = 0; // for incoming serial data
const int LedPin=8;
void setup() {
  Serial.begin(9600);
  pinMode(LedPin,OUTPUT); 
}
int n=1;
void loop() {
  // send data only when you receive data:
  while(n)
  {
    Serial.println("0:close");
    Serial.println("1:Open");
    --n;
  }
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read()-48;
    if(incomingByte)
    {
    digitalWrite(LedPin,HIGH);
    delay(1000);
    digitalWrite(LedPin,LOW);
    delay(1000);
    // say what you got:
    Serial.print(incomingByte, DEC);
    Serial.println(" Open ");
    }
    else{
      digitalWrite(LedPin,LOW);
      delay(2000);
      Serial.print(incomingByte, DEC);
      Serial.println(" Close ");
      }
  }
  
}
