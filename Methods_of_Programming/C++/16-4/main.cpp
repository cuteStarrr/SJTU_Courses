#include"jihe.h"


int main()
{
    int n1,n2;
    int i;
    cout<<"请输入第一个集合的个数："<<endl;
    cin>>n1;
    cout<<"请输入第二个集合的个数："<<endl;
    cin>>n2;
    int j1[n1],j2[n2];
    cout<<"请输入第一个集合的元素："<<endl;
    for(i=0;i<n1;++i)
        cin>>j1[i];
    cout<<"请输入第二个集合的元素："<<endl;
    for(i=0;i<n2;++i)
        cin>>j2[i];
    jihe<int> obj1(j1,n1),obj2(j2,n2);
    cout<<"交："<<obj1*obj2<<endl;
    cout<<"并："<<obj1+obj2<<endl;
    cout<<"差："<<obj1-obj2<<endl;
    return 0;
}


template<class t>
jihe<t>::jihe(const t *f,int num)
{
    int i;
    n=num;
    p=new t[n];
    for(i=0;i<n;++i)
        p[i]=f[i];
    paixu(p,n);
}
