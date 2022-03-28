//文件名：9_4
//对字符串进行加密和解密
#include <iostream>
#include <cstring>

using namespace std;


char jiami (char,int);
char jiemi (char,int);
int a[7]={8,7,3,4,9,6,2};
char *p,*ch,*q;
int i,n,LEN;
int main()
{
    cout<<"Please input the largest length:";
    cin>>LEN;
    ch=new char[LEN+1];
    cout<<"Please input plain text:";
    cin>>ch;
    n=strlen(ch);
    p=new char[n+1];
    for(i=0;i<n;++i)
        p[i]=jiami(ch[i],i);
    cout<<"Encrypt:"<<p<<endl;;
    q=new char[n+1];
    for(i=0;i<n;++i)
        q[i]=jiemi(p[i],i);
    cout<<"Decrypt:"<<q;
    delete p;
    delete q;
    return 0;
}



//函数：jiami
//将每个字符进行加密
char jiami (char p,int k)
{
    int num;
    num=p+a[k%7];
    if (num>122) num=num%91;
    return num;
}



//函数：jiemi
//将每个字符进行解密
char jiemi (char p,int k)
{
    int num;
    num=p-a[k%7];
    if (num<32) num=num+91;
    return num;
}
