//文件名：5_1
//将n个整数按从小到大的顺序排列
#include <iostream>

using namespace std;

int main()
{
    const int NUM=20;
    int a[NUM];
    int n,i,k,tmp;
    bool flag=true;
    cout<<"Please input n:";
    cin>>n;
    cout<<'\n'<<"Please input"<<n<<"integers:";
    for (i=0;i<n;++i)
    cin>>a[i];
    for(k=1;k<n;++k){
        for(i=0;i<n-k;++i)
          if (a[i]<a[i+1])
          {tmp=a[i];a[i]=a[i+1];a[i+1]=tmp;flag=false;}
          if(flag) break;
    }
     cout<<'\n'<<"Sorted sequence:";
     for(i=0;i<n;++i)
            cout<<a[i]<<' ';


    return 0;
}
