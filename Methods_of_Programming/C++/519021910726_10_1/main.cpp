//文件名：10_1
//输出最短字符串的有效长度
#include <iostream>
#include <cstring>
using namespace std;

char **p;
int n,i,*q,num,len;
int minlen(char *str[],int n);
int main()
{
    cout<<"请输入字符串个数：";
    cin>>n;
    p=new char *[n];
    q=new int[n];
    cout<<"请输入字符串不超过哪个长度：";
    cin>>len;
    cout<<"请依次输入字符串：";
    for(i=0;i<n;++i)
    {
     p[i]=new char[len+1];
     cin>>p[i];
    }
    num=minlen(p,n);
    cout<<num;
    delete []q;
    for(i=0;i<n;++i)
        delete [] p[i];
    delete []p;
    return 0;
}



//函数：int minlen(char *str[],int n);
//计算有n个元素的指针数组str中最短的字符串长度
int minlen(char *str[],int n)
{
    int k,ml=0,m;
    for(k=0;k<n;++k)
        q[k]=strlen(str[k]);
    for(m=0;m<n;++m)
        if(q[m]<q[ml])
            ml=m;
    return q[ml];
}
