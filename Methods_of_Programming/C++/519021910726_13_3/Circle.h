#ifndef CIRCLE_H_INCLUDED
#define CIRCLE_H_INCLUDED
#include <iostream>

using namespace std;
class Circle{
double X;
double Y;
double R;
public:
    Circle(double,double,double);
    void getO () const;
    void getR ()const;
    void setR (double);
    void moveTo (double,double);
    void display (Circle &) const;
};

#endif // CIRCLE_H_INCLUDED
