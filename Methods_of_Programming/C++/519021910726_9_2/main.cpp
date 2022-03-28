//文件名：9_2
//约瑟夫环问题
#include <iostream>

using namespace std;
int n,i;
int *p;
int number(int a[],int size);

int main()
{
    cout<<"Please input n:";
    cin>>n;
    if(n<=1) {cout<<"Not Found";return 0;}
    p=new int[n];
    for(i=1;i<n+1;++i){
        p[i-1]=i;
    }
    cout<<"Last code:"<<number(p,n);
    delete []p;
    return 0;
}



//函数：int number(int a[],int size)
//作用：找到最后剩下的人的号码
int number(int a[],int size)
{
    int m,tmp,num0,num1;
    if(size==2) return a[1];
    num0=a[0];
    num1=a[1];
    for(m=3;m<size;++m)
    {
        tmp=a[m-3];
        a[m-3]=a[m];
        a[m]=tmp;
    }
    a[m-3]=num0;
    a[m-2]=num1;
    return number(a,size-1);
}
