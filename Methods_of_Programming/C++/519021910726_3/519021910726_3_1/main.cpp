//文件名；3_1
//计算某户居民的水费

#include <iostream>

using namespace std;

int main()
{
   double t,cost;
   cout<<"请输入月用水量（吨）；";
   cin>>t;
   if (t>10) cost=15+2*(t-10);
   else cost=1.5*t;
   cout<<"水费（元）；"<<cost<<endl;
    return 0;
}
