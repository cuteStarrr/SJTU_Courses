//文件名：6_3
//去掉一个字符串的重复字符并将其按从大到小排列
#include <iostream>

using namespace std;

int main()
{
   char a[81];char b[81];
   int i,j=0,k,m,tmp,n,q;
   bool flag=true,boo=true;
   cout<<"Please input a string:";
   cin.getline(a,81);
   for(i=0;a[i]!='\0';++i)//取a[]中的一个元素
   {for(k=0;k<i;++k)
   {flag=true;
   if(a[i]==a[k])//判断是否重复
    {flag=false;break;}
   }
    if(flag)
    {b[j]=a[i];++j;}//j的大小为不重复字符的个数

   }

    for(n=1;n<j;++n)//最多j-1次起泡来排列顺序
    {
        for(m=0;m<j-n;++m)
        {
            boo=true;
            if(b[m]<b[m+1])
            {
                tmp=b[m];b[m]=b[m+1];b[m+1]=tmp;
                boo=false;
            }
        }
        if(boo)break;

    }
   cout<<endl;
   for(q=0;q<j;++q)
    cout<<b[q];
    return 0;
}
