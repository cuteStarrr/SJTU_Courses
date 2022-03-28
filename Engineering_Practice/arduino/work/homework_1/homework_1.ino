int LEDpin=9;//LED灯
int Soundpin=2;//蜂鸣器
void setup() {
  // put your setup code here, to run once:
pinMode(LEDpin,OUTPUT);
pinMode(Soundpin,OUTPUT);
}
int value;//读取模拟值
int num;//转换到LED灯的电压
float x;//转换到弧度区间，用于模拟蜂鸣器的频率
float h;//蜂鸣器的频率
void loop() {
  // put your main code here, to run repeatedly:
value=analogRead(A2);
num=map(value,0,1023,0,255);
x=map(value,0,1023,0,90);
h=1500+1500*sin(x*3014159/180);//用三角函数来模拟蜂鸣器的变化
tone(Soundpin,h);
analogWrite(LEDpin,num);
delay(10);}
