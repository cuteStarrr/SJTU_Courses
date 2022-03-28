int pin1=2;
int pin2=3;
int tonepin=8;
int tonetime=1000;
volatile bool isplay=false;
int len;

#define C_0 0
#define C_1 262
#define C_2 294
#define C_3 330
#define C_4 350
#define C_5 393
#define C_6 441
#define C_7 495
#define C1 525

int tune[]={C_3,C_1,C_3,C_3,C_1,C_3,C_3,C_5,C_6,
            C_5,C_0,C_6,C_6,C_6,C_5,C_4,C_4,C_4,
            C_2,C_3,C_2,C_1,C_2,C_0,C_3,C_0,C_1,
            C_0,C_3,C_0,C_1,C_0,C_3,C_3,C_5,C_6,
            C_6,C_0,C1,C_5,C_5,C_6,C_3,C_2,C_1,
            C_2,C_3,C_5,C_0,C1,C_5,C_5,C_6,C_3,
            C_2,C_1,C_2,C_3,C_1};

float duration[]={1,1,0.5,0.5,1,0.5,0.5,0.5,0.5,1,1,
                  0.5,0.5,0.5,0.5,0.5,0.5,1,0.5,0.5,
                  0.5,0.5,1,1,0.5,0.5,0.5,0.5,0.5,0.5,
                  0.5,0.5,0.5,0.5,0.5,0.5,1,1,1,0.5,
                  0.5,1,1,0.5,0.5,0.5,0.5,1,1,1,0.5,
                  0.5,1,1,0.5,0.5,0.5,0.5,2};
                  
char tunechar[]={'3','1','3','3','1','3','3','5','6',
            '5','0','6','6','6','5','4','4','4',
            '2','3','2','1','2','0','3','0','1',
            '0','3','0','1','0','3','3','5','6',
            '6','0','1','5','5','6','3','2','1',
            '2','3','5','0','1','5','5','6','3',
            '2','1','2','3','1'};


void continueMusic()
{
  if(digitalRead(pin1)==HIGH)
      {
        delay(80);
        if(digitalRead(pin1)==HIGH)
            isplay=true;
      }
}

void stopMusic()
{
  if(digitalRead(pin2)==LOW)
      {
        delay(80);
        if(digitalRead(pin2)==LOW){
            Serial.print('\n');
            Serial.println("stop Music:count ducks, push another button to continue");
            noTone(tonepin);
            isplay=false;}
        }
  }


void setup() {
  // put your setup code here, to run once:
  pinMode(tonepin,OUTPUT);//蜂鸣器的接线端
  pinMode(pin1,INPUT);
  pinMode(pin2,INPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(pin1),continueMusic,CHANGE);
  attachInterrupt(digitalPinToInterrupt(pin2),stopMusic,CHANGE);
  len=sizeof(tune)/sizeof(tune[0]);//乐谱的长度

}

void loop() {
  // put your main code here, to run repeatedly:
if(isplay){
    for(static int i=0;i<len;++i){
      if(isplay){
          Serial.print(tunechar[i]);
          Serial.print(" ");
          tone(tonepin,tune[i]);//蜂鸣器发出声音
          delay(tonetime*duration[i]);}//每个音符应该停顿多少秒
      else {while(!isplay){}
            --i;}
    }
    Serial.println('\n');
    Serial.println("The music is ended!");
    noTone(tonepin);
}
while(isplay){}
}
