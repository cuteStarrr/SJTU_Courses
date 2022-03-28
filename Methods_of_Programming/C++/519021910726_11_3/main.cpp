//文件名：11_3
//建立一个班级通信录
#include <iostream>

using namespace std;

struct birthdayT{
int year;
int month;
int day;}birthday;
struct studentT{
char name[21];
birthdayT birthday;
char tel[12];
char address[51];
}*p;
int n,i;
void Compare(studentT [],int);
int main()
{
    cout<<"Please input n(n<10):";
    cin>>n;
    p=new studentT[n+1];
    for(i=0;i<n;++i){
        cin>>p[i].name>>p[i].birthday.year>>p[i].birthday.month>>p[i].birthday.day>>p[i].tel>>p[i].address;
    }
    Compare(p,n);
    for(i=0;i<n;++i){
        cout<<p[i].name<<' '<<p[i].birthday.year<<' '<<p[i].birthday.month<<' '<<p[i].birthday.day<<' '<<p[i].tel<<' '<<p[i].address<<endl;
    }
    delete []p;
    return 0;
}



//函数：void Compare(studentT [],int)
//比较同学的年龄
//用法：void Compare(studentT [],int)
void Compare(studentT st[],int n)
{
    int i,max=0,j;
    for(j=0;j<n;++j)
    {
        max=j;
        for(i=j;i<n;++i)
    {
        if(st[i].birthday.year>st[max].birthday.year)
            max=i;
        if(st[i].birthday.year==st[max].birthday.year){
            if(st[i].birthday.month>st[max].birthday.month)
                max=i;
            else if(st[i].birthday.month==st[max].birthday.month)
            {
                if(st[i].birthday.day>st[max].birthday.day)
                    max=i;
            }
        }
    }
    st[n+1]=st[j];st[j]=st[max];st[max]=st[n+1];
    }

}
