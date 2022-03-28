#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#include <iostream>

using namespace std;


class Point {
friend ostream & operator<<(ostream & os,const Point &obj);
friend istream & operator>>(istream & is, Point &obj);
friend Point operator-(const Point &p);
private:
    double x;
    double y;
    double z;
public:
    Point(double a=0,double b=0,double c=0){x=a;y=b;z=c;}
};

#endif // POINT_H_INCLUDED
