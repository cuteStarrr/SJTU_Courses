//文件名；3_4;
//判断三点是否共线；
#include <iostream>

using namespace std;

int main()
{
   double x1,y1,x2,y2,x3,y3,k1=0,k2=0;
   cout<<"请输入第一个点的坐标（x1,y1）:";
   cin>>x1>>y1;
   cout<<"请输入第二个点的坐标（x2,y2）:";
   cin>>x2>>y2;
   cout<<"请输入第三个点的坐标（x3,y3）:";
   cin>>x3>>y3;
   if (x1==x2)
      if(x2==x3) cout<<"Yes";
      else cout<<"No";
   else if(x2==x3) cout<<"No";
        else {k1=(y1-y2)/(x1-x2),k2=(y2-y3)/(x2-x3);
             if (k1==k2) cout<<"Yes";
             else cout<<"No"<<endl;}



    return 0;
}
