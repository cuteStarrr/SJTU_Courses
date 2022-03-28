#include"Time.h"


int operator-(const Time &a,const Time &b)
{
    return a.hour*3600+a.minute*60+a.second-b.hour*3600-b.minute*60-b.second;
}


ostream & operator<<(ostream & os,const Time &obj)
{
    if(obj.hour<10) os<<'0'<<obj.hour<<':';
    else os<<obj.hour<<':';
    if(obj.minute<10) os<<'0'<<obj.minute<<':';
    else os<<obj.minute<<':';
    if(obj.second<10) os<<'0'<<obj.second;
    else os<<obj.second;
    return os;
}


Time & Time::operator++()
{
    if(second<59) ++second;
    else if(minute<59) {second=0;++minute;}
         else if(hour<23) {second=0;minute=0;++hour;}
              else {second=0;minute=0;hour=0;}
    return *this;
}


Time & Time::operator--()
{
    if(second>0) --second;
    else if(minute>0) {second=59;--minute;}
         else if(hour>0) {second=59;minute=59;--hour;}
              else {second=59;minute=59;hour=23;}
    return *this;
}



Time & Time::operator+=(int s)
{
    int tmp;
    tmp=hour*3600+minute*60+second+s;
    hour=(tmp/3600)%24;
    tmp=tmp%3600;
    minute=tmp/60;
    second=tmp%60;
    return *this;
}


Time & Time::operator-=(int s)
{
    int tmp;
    tmp=hour*3600+minute*60+second-s;
    hour=(tmp/3600)%24;
    tmp=tmp%3600;
    minute=tmp/60;
    second=tmp%60;
    return *this;
}
