//文件名：9_3
//将Julian历法转化为公历的日期
#include <iostream>

using namespace std;
int ryear[12]={31,29,31,30,31,30,31,31,30,31,30,31};
int pyear[12]={31,28,31,30,31,30,31,31,30,31,30,31};//闰年平年的月份个数
char *name[]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};//每个月份的名字
char **year;//指向月份名字
int yue,ri,n,num,result;
int Convert (int n,int num,int *p,int *q);
int main()
{
    year=name;
    cout<<"Please input the year:";
    cin>>n;
    cout<<"Please input the day:";
    cin>>num;
    result=Convert(n,num,&yue,&ri);
    if(result==0)
       cout<<year[yue]<<ri;
    else cout<<"NULL";
    return 0;
}


//函数：Convert
//将Julian历法转化为公历的日期
int Convert (int n,int num,int *p,int *q)//p为返回的月份下标，q为返回的日期
{
    int i,m=0,k,sum=0;
    if((n%4==0&&n%100!=0)||n%400==0)//判断平年闰年
    {
        if(num>366) return -1;
        for(i=0;i<12;++i){
            m+=ryear[i];
            if(num<=m) {
               *p=i;
               for (k=0;k<i;++k)
                   sum+=ryear[k];
               *q=num-sum;
               break;}
        }
        return 0;
    }
    else {
        if(num>365) return -1;
        for(i=0;i<12;++i){
            m+=pyear[i];
            if(num<=m) {
               *p=i;
               for (k=0;k<i;++k)
                   sum+=pyear[k];
               *q=num-sum;
               break;}
        }
        return 0;
    }
}
