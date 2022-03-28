#include"Point.h"



ostream & operator<<(ostream & os,const Point &obj)
{
    os<<"("<<obj.x<<","<<obj.y<<","<<obj.z<<")";
    return os;
}



istream & operator>>(istream & is, Point &obj)
{
    is>>obj.x>>obj.y>>obj.z;
    return is;
}



Point operator-(const Point &p)
{
    Point tmp;
    tmp.x=-p.x;
    tmp.y=-p.y;
    tmp.z=-p.z;
    return tmp;
}
