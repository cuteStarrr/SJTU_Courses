//文件名：8_1
//判断100以内的任意两个数之间的素数个数
#include <iostream>

using namespace std;

bool isPrime(int n);
int main()
{
    int m,n,num=0,i;
    bool FLAG;
    cout<<"Please input m,n(1<=m,n<=100):";
    cin>>m>>n;
    for(i=m;i<=n;++i)
    {

       FLAG=isPrime(i);
       if(FLAG) ++num;

    }
    cout<<'\n'<<"Count="<<num<<endl;

    return 0;
}

//函数：isPrime(int n)
//用法：isPrime(int n)
//判断n是否为素数
bool isPrime(int n)
{
    bool flag=true;
    int k;
    if(n==1) flag=false;//1不是素数
    else for(k=2;k<n;++k)
             if (n%k==0) flag=false;
    return flag;
}
