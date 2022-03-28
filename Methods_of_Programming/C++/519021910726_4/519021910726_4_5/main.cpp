//文件名：4_5
//设计一个猜字游戏
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    int i,finger,num1,num2,num3,NUM1,NUM2,NUM3,a=0,b=0;
    srand(time(NULL));
    NUM1=rand()%10;
    NUM2=rand()%10;
    NUM3=rand()%10;
    while (NUM1==NUM2||NUM1==NUM3||NUM2==NUM3)
    {
        srand(time(NULL));
    NUM1=rand()%10;
    NUM2=rand()%10;
    NUM3=rand()%10;
    }

    for (i=7;i>=1;--i)
    {
        cout<<"请输入你猜测的数字（还有"<<i<<"次机会）：";
        cin>>finger;
        num1=finger/100;
        num2=finger/10;
        num2=num2%10;
        num3=finger%10;
        if (NUM1==num1) ++a;
        else if(num1==NUM2||num1==NUM3) ++b;
        if (NUM2==num2) ++a;
        else if(num2==NUM1||num2==NUM3) ++b;
        if (NUM3==num3) ++a;
        else if(num3==NUM1||num3==NUM2) ++b;
        cout<<'\n'<<a<<'A'<<b<<'B'<<endl;
        if (a==3&&b==0) {cout<<"恭喜，你猜对了。";return 0;}
        else a=0,b=0;
    }
    cout<<"很遗憾，你没有在规定次数内猜对。答案是"<<NUM1<<NUM2<<NUM3<<"。"<<endl;
    return 0;
}
