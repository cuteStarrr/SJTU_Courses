//文件名：5_6
//找出1到200中平方在给定进制下为回文数的数及其回文数
#include <iostream>

using namespace std;

int main()
{
    char a[16]="0";
    char b[16]="0";
    int num,NUM;
    int i,B,j,k,m;
    bool flag;
    cout<<"请输入进制B：";
    cin>>B;
    for(i=1;i<=200;++i)
    {
        flag=true;
        num=i;
        NUM=num*num;//表示出该数和该平方数
        for(k=0;num!=0;++k)//将该数转换为B进制
        {
            if(num%B>=10)
            b[k]='A'+num%B-10;
            else b[k]=num%B+'0';
            num=num/B;
        }//此时k比需要的数多1
        for(j=0;NUM!=0;++j)//将平方数转换为B进制
        {
            if(NUM%B>=10)
                a[j]='A'+NUM%B-10;
            else a[j]=NUM%B+'0';
                NUM=NUM/B;
        }//此时j比需要的个数多1
        for(m=0;m<j-1-m;++m)//判断是否为回文数
        if(a[m]!=a[j-1-m]) {flag=false;break;}
        if(flag)//输出回文数
        {for(;k>0;--k)
            cout<<b[k-1];
        cout<<' ';
        for(;j>0;--j)
            cout<<a[j-1];
        cout<<endl;}

    }

    return 0;
}
