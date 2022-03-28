int incomingByte = 0; // for incoming serial data
const int LedPin=8;
void setup() {
  Serial.begin(9600); 
  pinMode(LedPin,OUTPUT);
}
int n=0;
void loop() {
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read()-48;

    // say what you got:
    for(n=0;n<incomingByte;){
  digitalWrite(LedPin,HIGH);
  delay(1000);
  digitalWrite(LedPin,LOW);
  delay(1000);
  ++n;
  Serial.print("n=");
  Serial.println(n);
    }
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
  }
}
