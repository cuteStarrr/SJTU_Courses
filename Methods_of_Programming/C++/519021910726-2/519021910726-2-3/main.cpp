//文件名：2-3
//求出一个三位数的百位数字、十位数字、个位数字

#include <iostream>

using namespace std;

int main()
{
    int num,b,c,d;
    cout<<"请输入一个三位整数"<<endl;
    cin>>num;
    b=num/100;
    c=(num/10)%10;
    d=num%10;
    cout<<num<<"的百位数字是"<<b<<','<<"十位数字是"<<c<<','<<"个位数字是"<<d<<endl;
    return 0;
}
