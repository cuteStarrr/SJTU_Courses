#include"name.h"

int main()
{
    OutPut();
    while(num!=9)
    {
        GetCall();
        switch(num){
           case 1:order=1;break;
           case 2:order=2;break;
           case 3:++rit;break;
           case 4:++lft;break;
           case 5:{cout<<"请输入步数：";
                  cin>>n;Move(order,lft,rit,n);} break;
           case 6:Print();break;
        }
        num=0;
        GetCall();
    }
    if(num==9) return 0;
}
