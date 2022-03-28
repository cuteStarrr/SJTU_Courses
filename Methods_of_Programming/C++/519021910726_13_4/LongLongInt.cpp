//头文件的实现
#include"LongLongInt.h"

int i,num;//i用于计数，num用于整数与字符之间的转化
bool flag=false;//用于判断相加时是否应该进位
char tmp;//用于交换顺序


LongLongInt::LongLongInt(char *ch)
{
    n=strlen(ch);
    p=new char[n+1];
    strcpy(p,ch);
    p[n]='\0';
}


LongLongInt &LongLongInt::operator=(const LongLongInt &l)
{
    if(this==&l) return *this;
    delete []p;
    n=strlen(l.p);
    p=new char[n+1];
    strcpy(p,l.p);
    p[n]='\0';
    return *this;
}


void LongLongInt::addLong (const LongLongInt &a,const LongLongInt &b)
{
    if(p) delete []p;
    if(a.n>b.n) p=new char[a.n+1];
    else p=new char[b.n+1];
    for(i=1;i<(a.n+1)&&i<(b.n+1);++i)
        {
            if(a.p[a.n-i]+b.p[b.n-i]-'0'-'0'+flag>9)
            {
                num=a.p[a.n-i]+b.p[b.n-i]-'0'-10+flag;
                p[i-1]=num;
                flag=true;
            }
            else {
                num=a.p[a.n-i]+b.p[b.n-i]-'0'+flag;
                p[i-1]=num;
                flag=false;
            }
        }
        if(a.n>b.n)
            {for(i=b.n;i<a.n;++i)
            {if(a.p[a.n-i-1]-'0'+flag>9)
            {
                p[i]='0';
                flag=true;
            }
            else  {num=a.p[a.n-i-1]+flag;
                   p[i]=num;
                   flag=false;
                  }}
            if(flag){p[a.n]='1';p[a.n+1]='\0';}
            else p[a.n]='\0';
            }
        if(b.n>a.n)
            {for(i=a.n;i<b.n;++i)
            {if(b.p[b.n-i-1]-'0'+flag>9)
            {
                p[i]='0';
                flag=true;
            }
            else  {num=b.p[b.n-i-1]+flag;
                   p[i]=num;
                   flag=false;
                  }}
            if(flag){p[b.n]='1';p[b.n+1]='\0';}
            else p[b.n]='\0';
            }
        if(a.n==b.n)
           if(flag){
              p[a.n]='1';
              p[a.n+1]='\0';
                   }
            else p[a.n]='\0';
        n=strlen(p);
    Correct();
}



void LongLongInt::Correct()
{
    for(i=0;i<n/2;++i)
    {
        tmp=p[i];
        p[i]=p[n-1-i];
        p[n-1-i]=tmp;
    }
}
