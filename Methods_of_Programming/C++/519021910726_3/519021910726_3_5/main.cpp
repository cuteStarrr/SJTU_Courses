//文件名：3_5
//判断一个数是否是回文数；
#include <iostream>

using namespace std;

int main()
{
    int num,m,n,p,q;
    cout<<"请输入一个五位正整数：";
    cin>>num;
    m=num/10000,n=num%10,p=(num/1000)%10,q=(num/10)%10;
    (m==n&&p==q)? cout<<"Yes"<<endl:cout<<"No"<<endl;
    return 0;
}
