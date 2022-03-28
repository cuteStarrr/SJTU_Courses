//文件名；3_3;
//鸡兔同笼问题；

#include <iostream>

using namespace std;

int main()
{
   int m,n,chicken,rabbit;
   cout<<"请输入鸡和兔的总数量:";
   cin>>n;
   cout<<"请输入鸡和兔的腿的总数量；";
   cin>>m;
     if (m>=2*n&&m<=4*n)
     {chicken=(4*n-m)/2;rabbit=(m-2*n)/2;
      cout<<"鸡："<<chicken<<",兔；"<<rabbit<<endl;}
     else cout<<"无解"<<endl;

    return 0;
}
