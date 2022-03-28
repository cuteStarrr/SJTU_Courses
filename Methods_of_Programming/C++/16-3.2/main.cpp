#include <iostream>

using namespace std;


template <class t>
int xun(t x,int d,int g,t *p)
{
    bool flag;
    t tmp;
    int m,i,j;
    for(i=1;i<g-d+1;++i)
    {
        flag=true;
        for(j=0;j<g-d+1-i;++j)
            if(p[j]>p[j+1])
        {
            tmp=p[j+1];p[j+1]=p[j];p[j]=tmp;
            flag=false;
        }
        if(flag) break;
    }
    while(d<=g)
    {
        m=(d+g)/2;
        if(p[m]==x) {return m;break;}
        else if(p[m]<x) d=m+1;
             else g=m-1;
    }
    if(d<=g) return m;
    else return 0;
}

int main()
{
    int n,po,i;
    double x,*p;
    cout <<"请输入要查找的数组规模："<<endl;
    cin>>n;
    cout<<"输入数组："<<endl;
    p=new double[n];
    for(i=0;i<n;++i)
        cin>>p[i];
    cout<<"输入要查找的元素："<<endl;
    cin>>x;
    po=xun(x,0,n-1,p);
    for(i=0;i<n;++i)
        cout<<p[i]<<' ';
    if(po) cout<<"找到了，在"<<po+1<<"位置";
    else cout<<"没有找到";
    delete []p;
    return 0;
}
