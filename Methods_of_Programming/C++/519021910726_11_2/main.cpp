//文件名：11_2
//模拟一个显示时间的电子时钟
#include <iostream>
#include <windows.h>
#include <stdio.h>

using namespace std;

void setTime(char h[],char m[],char s[]);
void increase(char h[],char m[],char s[]);
void showTime();
struct timeT{
char h[3];
char m[3];
char s[3];
}time;
int main()
{
    setTime(time.h,time.m,time.s);
    while(true)
    {
        increase(time.h,time.m,time.s);
        showTime();
    }
    return 0;
}



//函数：setTime
//用于设置时钟的时间
//用法：void setTime(int,int,int)
void setTime(char h[],char m[],char s[])
{
    cout<<"请输入时间（时、分、秒，24小时制）：";
    cin>>h>>m>>s;
    return ;
}


//函数：increase
//模拟时间过去了一秒
//用法：void increase(int,int,int)
void increase(char h[],char m[],char s[])
{
    Sleep(1000);
    if(s[1]<'9') ++s[1];
    else{
        s[1]='0';
        if(s[0]<'5') ++s[0];
        else {
                s[0]='0';
        if(m[1]<'9') ++m[1];
        else {
                m[1]='0';
                if(m[0]<'5') ++m[0];
                else {m[0]='0';
                if(h[1]<'9'&&h[0]<'2') ++h[1];
                else{
                    if(h[1]=='9'&&h[0]<'2') {
                            h[1]='0';
                            ++h[0];}
                    else if(h[1]=='3') {h[0]='0';h[1]='0';}
                }
            }
        }
    }
  }
}


//函数：showTime
//显示当前时间
//用法：void showTime()
void showTime()
{
    system("cls");
    cout<<time.h<<':'<<time.m<<':'<<time.s;
    return ;
}
