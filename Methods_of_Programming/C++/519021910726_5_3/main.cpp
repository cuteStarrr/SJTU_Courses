//文件名：5_3
//判断开着的灯的编号
#include <iostream>

using namespace std;

int main()
{
    const int LEN=1000;
    int a[LEN]={0};
    int n,k,i,j;
    cout<<"Please input n,k(k<=n<=1000):";
    cin>>n>>k;
    for(j=0;j<n;++j)
    a[j]=1;
    for(i=2;i<=k;++i)
        for(j=0;j<n;++j)
        if((j+1)%i==0)
        a[j]=-a[j];
    for(j=0;j<n;++j)
        if(a[j]>0)
        cout<<j+1<<' ';


    return 0;
}
