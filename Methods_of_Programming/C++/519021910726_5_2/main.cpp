//文件名：5_2
//输出一个矩阵的鞍点
#include <iostream>

using namespace std;

int main()
{
    const int LEN=10;
    int a[LEN][LEN];
    int m,n,i,j,k,row,col;
    bool flag=true;
    cout<<"Please input m,n:";
    cin>>m>>n;
    cout<<'\n'<<"Please input array:"<<endl;
    for(i=0;i<m;++i)
        for(j=0;j<n;++j)
        cin>>a[i][j];
    for(i=0;i<m;++i)
       {
           flag=true;
           for(j=0;j<n-1;++j)
            if(a[i][j]>a[i][j+1])
                {row=i;col=j;}
            else{row=i;col=j+1;}
            for(k=0;k<m;++k)
            if (a[row][col]>a[k][col])
             {flag=false; break;}

           if(flag)
            cout<<"mat"<<'['<<row<<']'<<'['<<col<<']'<<'='<<a[row][col]<<endl;
            }

    if(!flag)
        cout<<"Not Found";
    return 0;
}
