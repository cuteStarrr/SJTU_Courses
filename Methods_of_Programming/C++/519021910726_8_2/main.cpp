//文件名：8_2
//找出两个数之间的完全数
#include <iostream>

using namespace std;
bool perfectNumber(int n);

int main()
{
    int m,n,i;
    bool FLAG;
    cout<<"Please input m,n(1<=m,n<=10000):";
    cin>>m>>n;
    cout<<'\n'<<"Perfect number in ["<<m<<"，"<<n<<"]:";
    for(i=m;i<=n;++i)
        {
            FLAG=perfectNumber(i);
            if(FLAG) cout<<i<<' ';
        }
    return 0;
}

//函数：perfectNumber
//用法：perfectNumber(int n)
//作用：判断一个数是不是完全数
bool perfectNumber(int n)
{
    int k,s=0;
    bool flag=false;
    for(k=1;k<n;++k)
        if(n%k==0) s+=k;
    if(s==n) flag=true;
    return flag;
}
