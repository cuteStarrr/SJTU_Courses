#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED

#include <iostream>

using namespace std;


class Time{
friend int operator-(const Time &a,const Time &b);
friend ostream & operator<<(ostream & os,const Time &obj);
private:
    int hour;
    int minute;
    int second;
public:
    Time(int a=0,int b=0,int c=0){hour=a;minute=b;second=c;}
    Time & operator++();
    Time & operator--();
    Time & operator+=(int s);
    Time & operator-=(int s);
};

#endif // TIME_H_INCLUDED
