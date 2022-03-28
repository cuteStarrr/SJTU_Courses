//文件名；2-2
//计算四个数的平均值
#include<iostream>
using namespace std;
int main()
{
    int a,b,c,d;
    double e;

    cout<<"请输入四个整型数:"<<endl;
    cin>>a>>b>>c>>d;
    e=double(a+b+c+d)/4;
    cout<<a<<' '<<b<<' '<<c<<' '<<d<<"的平均值是"<<e<<endl;

    return 0;

}
