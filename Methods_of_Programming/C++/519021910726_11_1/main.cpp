//文件名：11_1
//实现复数的加法、乘法、输入和输出
#include <iostream>

using namespace std;

void jiafa(int,int,int,int,int*,int*);
void chengfa(int,int,int,int,int*,int*);
struct fushu{
    int a;
    int b;}m,n;
int p,q;
int main()
{
   cout<<"请分别输入两个复数，先输入实部再输入虚部：";
   cin>>m.a>>m.b>>n.a>>n.b;
   jiafa(m.a,m.b,n.a,n.b,&p,&q);
   cout<<"和："<<p<<'+'<<q<<'i';
   cout<<endl;
   chengfa(m.a,m.b,n.a,n.b,&p,&q);
   cout<<"积："<<p<<'+'<<q<<'i';
    return 0;
}



//函数：jiafa
//实现复数的加法
void jiafa(int a,int b,int c,int d,int*p,int*q)
{
    *p=a+c;
    *q=b+d;
}


//函数：chengfa
//实现复数的乘法
void chengfa(int a,int b,int c,int d,int*p,int*q)
{
    *p=a*c-b*d;
    *q=b*c+a*d;
}
