//文件名：Circle.cpp
//圆的成员函数的实现
#include"Circle.h"



Circle::Circle(double x,double y,double r):X(x),Y(y),R(r)
{

}


void Circle::getO()const
{
   cout<<"圆心为："<<"("<<X<<","<<Y<<")"<<endl;
}


void Circle::getR()const
{
    cout<<"半径为："<<R<<endl;
}


void Circle::setR(double r)
{
    R=r;
}


void Circle::moveTo(double x,double y)
{
    X=x;
    Y=y;
}

void Circle::display(Circle &tmp)const
{
    cout<<"圆心为："<<"("<<tmp.X<<","<<tmp.Y<<")"<<endl;
    cout<<"半径为："<<tmp.R<<endl;
}



