//文件名；2-1
//计算两个整数的和、积、商和余数

#include <iostream>

using namespace std;

int main()
{
    int a,b,c,d,e,f;
cout<<"请输入两个整数"<<endl;
cin>>a>>b;
c=a+b;
d=a*b;
e=a/b;
f=a%b;
cout<<a<<'+'<<b<<'='<<c<<endl;
cout<<a<<'*'<<b<<'='<<d<<endl;
cout<<a<<'/'<<b<<'='<<e<<endl;
cout<<a<<'%'<<b<<'='<<f<<endl;

return 0;

}
