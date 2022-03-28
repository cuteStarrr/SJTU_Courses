int RED=6;
int BLUE=5;
int GREEN=3;//闪亮的灯球
int Soundpin=2;//蜂鸣器
void setup() {
  // put your setup code here, to run once:
pinMode(Soundpin,OUTPUT);
pinMode(RED,OUTPUT);
pinMode(BLUE,OUTPUT);
pinMode(GREEN,OUTPUT);
}
int value;//读取模拟值
int num;//转换到LED灯的电压
int red;
int blue;
int green;//灯球的颜色
float x;//转换到弧度区间，用于模拟蜂鸣器的频率
float h;//蜂鸣器的频率
void loop() {
  // put your main code here, to run repeatedly:
value=analogRead(A0);
num=map(value,0,1023,0,255);
x=map(value,0,1023,0,90);
h=1500+1500*sin(x*3014159/180);//用三角函数来模拟蜂鸣器的变化
if (value==0)
    red=blue=green=0;
else if (value==255)
         red=blue=green=255;
     else {
            randomSeed(analogRead(0));
            green=random(-0.5*num,0.5*num)+num;
            randomSeed(analogRead(0));
            red=random(-0.5*num,0.5*num)+num;
            randomSeed(analogRead(0));
            blue=random(-0.5*num,0.5*num)+num;
            }
tone(Soundpin,h);
colorRGB(red,blue,green);
delay(10);
}

void colorRGB(int red, int blue, int green){
analogWrite(RED,constrain(red,0,255));
analogWrite(BLUE,constrain(blue,0,255));
analogWrite(GREEN,constrain(green,0,255));
}
