//文件名：3_7(2)
//反解密密码
#include <iostream>

using namespace std;

int main()
{
    int num,p,q,m,n,onum;
    cout<<"请输入一个四位整数：";
    cin>>num;
    m=num/1000;
    (m<=7)? m=m+3:m=m-7;
   n=(num/100)%10;
   (n<=7)? n=n+3:n=n-7;
   p=(num/10)%10;
   (p<=7)? p=p+3:p=p-7;
   q=num%10;
   (q<=7)? q=q+3:q=q-7;
   onum=1000*p+100*q+10*m+n;
   cout<<onum<<endl;

    return 0;
}
