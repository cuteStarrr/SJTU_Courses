#ifndef JIHE_H_INCLUDED
#define JIHE_H_INCLUDED

#include <iostream>

using namespace std;
template <class t> class jihe;
template <class t> ostream& operator<<(ostream &os,const jihe<t> &obj);
template <class t> jihe<t> operator*(const jihe<t> &,const jihe<t> &);
template <class t> jihe<t> operator+(const jihe<t> &,const jihe<t> &);
template <class t> jihe<t> operator-(const jihe<t> &,const jihe<t> &);
template <class t> void paixu(t *pp,int &n)//将集合元素按从小到大排列
{
    int i,j,m;
    t tmp,*p;
    bool flag;
    m=n;
    p=new t[m];
    for(i=0;i<m;++i)
        p[i]=pp[i];
    for(i=1;i<m;++i)
    {
        flag=true;
        for(j=0;j<m-i;++j)
            if(p[j]>p[j+1]) {tmp=p[j+1];p[j+1]=p[j];p[j]=tmp;flag=false; }
        if(flag) break;
    }
    for(i=0;i<m-1;++i)
        if(p[i]==p[i+1]) --n;
    delete []pp;
    pp=new t[n];
    j=0;
    for(i=0;i<m-1;++i)
        if(p[i]!=p[i+1]) {pp[j]=p[i];++j;}
    pp[j]=p[m-1];
    delete []p;
}


template <class t>
class jihe {
    friend jihe<t> operator*(const jihe<t> &a,const jihe<t> &b)
    {
    int i,j,m=0,n;
    t tmp[a.n+b.n];
    t *p;
    n=0;
    for(i=0;i<a.n;++i)
        for(j=0;j<b.n;++j)
            if(a.p[i]==b.p[j]) {++n;tmp[m]=a.p[i];++m; }
    p=new t[n];
    for(i=0;i<n;++i)
        p[i]=tmp[i];
    return jihe<t>(p,n);
    }

    friend jihe<t> operator+(const jihe<t> &a,const jihe<t> &b)
    {
    int i,m;
    t tmp[a.n+b.n];
    for(i=0;i<a.n;++i)
        tmp[i]=a.p[i];
    for(i=a.n;i<a.n+b.n;++i)
        tmp[i]=b.p[i-a.n];
    m=a.n+b.n;
    return jihe<t>(tmp,m);
    }
    friend jihe<t> operator-(const jihe<t> &a,const jihe<t> &b)
    {
    int i,j,n,m=0;
    t *p,*tmp;
    bool flag;
    n=a.n;
    for(i=0;i<a.n;++i)
        for(j=0;j<b.n;++j)
            if(a.p[i]==b.p[j]) --n;
    p=new t[n];
    for(i=0;i<a.n;++i)
       {
           flag=true;
           for(j=0;j<b.n;++j)
              if(a.p[i]==b.p[j]) flag=false;
           if(flag) {p[m]=a.p[i];++m;}
       }
    return jihe<t>(p,n);
    }
    friend ostream& operator<<(ostream &os,const jihe &obj)
    {
    int i;
    for(i=0;i<obj.n;++i)
        os<<obj.p[i]<<' ';
    return os;
    }

private:
    t *p;
    int n;
public:
    jihe(const t*,int);
    ~jihe() {if(p) delete []p;}


};

#endif // JIHE_H_INCLUDED


