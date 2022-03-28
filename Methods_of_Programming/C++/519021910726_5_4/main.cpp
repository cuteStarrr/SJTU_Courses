//文件名：5_4
//判断每个月的13号落到星期几
#include <iostream>

using namespace std;

int main()
{
    int p[12]={31,28,31,30,31,30,31,31,30,31,30,31};int r[12]={31,29,31,30,31,30,31,31,30,31,30,31};
    int j,i,n,k,num=13,Mon=0,Tue=0,Wed=0,Thu=0,Fri=0,Sat=1,Sun=0;
    cout<<"请输入要计算的年份数n：";
    cin>>n;
    for(i=1900;i<1900+n;++i)
        for(j=0;j<12;++j)
        {if((i%4==0&&i%100!=0)||i%400==0)
        {num=num+r[j];
        k=num%7;}
        else {num=num+p[j];
        k=num%7;}
    switch(k){
    case 0:++Sun;break;
    case 1:++Mon;break;
    case 2:++Tue;break;
    case 3:++Wed;break;
    case 4:++Thu;break;
    case 5:++Fri;break;
    case 6:++Sat;break;
    }
    if((i==1900+n-1)&&(j==10)) break;
        }

      cout<<'\n'<<Mon<<' '<<Tue<<' '<<Wed<<' '<<Thu<<' '<<Fri<<' '<<Sat<<' '<<Sun<<endl;

    return 0;
}
