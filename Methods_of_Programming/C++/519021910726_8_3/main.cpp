//文件名：8_3
//将十进制数转化为其他进制数
#include <iostream>

using namespace std;
void printInt(int n,int base);

int main()
{
    int n,base;
    cout<<"Please input n,base(2<=base<=16):";
    cin>>n>>base;
    cout<<endl;
    cout<<n<<"(10)=";
    printInt(n,base);
    cout<<'('<<base<<')';
    cout<<endl;
    return 0;
}

//函数：printInt
//用法：printInt(int n,int base)
//作用：将十进制数转化为其他进制数
void printInt(int n,int base)
{
    char number[17]="0123456789ABCDEF";
    if(n<base) cout<<number[n];
    else {
            printInt(n/base,base);
            cout<<number[n%base];
         }
}
