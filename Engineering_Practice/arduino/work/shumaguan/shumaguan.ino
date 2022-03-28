//开关不是很灵敏，可能要换一个开关
#define SEG_A 6
#define SEG_B 8
#define SEG_C 10
#define SEG_D 12
#define SEG_E 13
#define SEG_F 7
#define SEG_G 9
#define SEG_H 11
 
#define COM1 A0
#define COM2 4
#define COM3 3
#define COM4 5

#define button 2
 
 
unsigned char table[10][8] =                
{
    {0, 0,  1,  1,  1,  1,  1,  1},         //0
    {0, 0,  0,  0,  0,  1,  1,  0},         //1
    {0, 1,  0,  1,  1,  0,  1,  1},         //2
    {0, 1,  0,  0,  1,  1,  1,  1},         //3
    {0, 1,  1,  0,  0,  1,  1,  0},         //4
    {0, 1,  1,  0,  1,  1,  0,  1},         //5
    {0, 1,  1,  1,  1,  1,  0,  1},         //6
    {0, 0,  0,  0,  0,  1,  1,  1},         //7
    {0, 1,  1,  1,  1,  1,  1,  1},         //8
    {0, 1,  1,  0,  1,  1,  1,  1}          //9
};
 
void setup()
{
    pinMode(SEG_A,OUTPUT);      //设置为输出引脚
    pinMode(SEG_B,OUTPUT);
    pinMode(SEG_C,OUTPUT);
    pinMode(SEG_D,OUTPUT);
    pinMode(SEG_E,OUTPUT);
    pinMode(SEG_F,OUTPUT);
    pinMode(SEG_G,OUTPUT);
    pinMode(SEG_H,OUTPUT);
 
    pinMode(COM1,OUTPUT);
    pinMode(COM2,OUTPUT);
    pinMode(COM3,OUTPUT);
    pinMode(COM4,OUTPUT);
    attachInterrupt(0,isstop,RISING);
}
int q=0;
int b=0;
int s=0;
int g=0; 
volatile bool flagon=false;
bool flagminute;
unsigned long oldtime=0;
unsigned long newtime=0;
int buttonstate=0;
long interval=1000;
void loop()
{
    flagminute=false;
    if(flagon)
    {Display(1,q);           //第1位显示千位
    delay(500);
    Display(2,b);           //第2位显示百位
    delay(500);
    Display(3,s);           //第3位显示十位
    delay(500);
    Display(4,g);           //第4位显示个位
    delay(500);
    newtime=millis();
    if(newtime-oldtime>=interval)
    {
      oldtime=newtime;
      flagminute=true;
      }
    if(flagminute)
    {
      g=g+1;
    if(g==10)
    {
      g=0;
      s=s+1;
      if(s==10)
      {
        s=0;
        ++b;
        if(b==10)
        {
          b=0;
          ++q;
          if(q==10)
          {
            q=0;
            b=0;
            s=0;
            g=0;
            }
          }
        }
      }
      }
    }
}

void isstop()
{
  if(flagon)
  {
    flagon=false;
    }
  else
  {
    flagon=true;
    }
  }

void Display(unsigned char com,unsigned char num)//第com位，显示num
{
    digitalWrite(SEG_A,LOW);            //去除余晖
    digitalWrite(SEG_B,LOW);
    digitalWrite(SEG_C,LOW);
    digitalWrite(SEG_D,LOW);
    digitalWrite(SEG_E,LOW);
    digitalWrite(SEG_F,LOW);
    digitalWrite(SEG_G,LOW);
    digitalWrite(SEG_H,LOW);
 
    switch(com)                     //选通位选
    {
        case 1:
            digitalWrite(COM1,LOW);     //选择位1
            digitalWrite(COM2,HIGH);
            digitalWrite(COM3,HIGH);
            digitalWrite(COM4,HIGH);
            break;
        case 2:
            digitalWrite(COM1,HIGH);
            digitalWrite(COM2,LOW);     //选择位2
            digitalWrite(COM3,HIGH);
            digitalWrite(COM4,HIGH);
            break;
        case 3:
            digitalWrite(COM1,HIGH);
            digitalWrite(COM2,HIGH);
            digitalWrite(COM3,LOW);     //选择位3
            digitalWrite(COM4,HIGH);
            break;
        case 4:
            digitalWrite(COM1,HIGH);
            digitalWrite(COM2,HIGH);
            digitalWrite(COM3,HIGH);
            digitalWrite(COM4,LOW);     //选择位4
            break;
        default:break;
    }
 
    digitalWrite(SEG_A,table[num][7]);          //a查询码值表
    digitalWrite(SEG_B,table[num][6]);
    digitalWrite(SEG_C,table[num][5]);
    digitalWrite(SEG_D,table[num][4]);
    digitalWrite(SEG_E,table[num][3]);
    digitalWrite(SEG_F,table[num][2]);
    digitalWrite(SEG_G,table[num][1]);
    digitalWrite(SEG_H,table[num][0]);
}
