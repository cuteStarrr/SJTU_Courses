//文件名：4_6
//输出西西弗数转换过程
#include <iostream>

using namespace std;

int main()
{
    int num,item,i,n,ou=0,ji=0;
    cout<<"Input a natural number:";
    cin>>num;
    cout<<'\n'<<num;
    for (i=0;i<=7;++i)
    {item=num%10;
        if (item%2==0) ++ou;
        else ++ji;
    num=num/10;
    }
    num=ou*100+ji*10+i;
    cout<<"->"<<num;
    ou=0;
    ji=0;
    while (num!=123)                 //若要考虑西西弗斯数的位数，则进行程序改写
    {                                //增加一个记位数的变量
        for (n=0;n<=2;++n)           //判断位数不仅要该位为零，而且要该位的高一位也为零（防止中间有零的情况的误判）
        {item=num%10;
        if (item%2==0) ++ou;
        else ++ji;
        num=num/10;}
    num=ou*100+ji*10+n;
    cout<<"->"<<num;
    ou=0;
    ji=0;
    }
    return 0;
}
