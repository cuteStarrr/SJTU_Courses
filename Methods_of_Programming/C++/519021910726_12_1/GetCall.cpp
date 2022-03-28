//用于接收用户指令

#include"name.h"

void GetCall()
{
    while(num!=1&&num!=2&&num!=3&&num!=4&&num!=5&&num!=6&&num!=9)
    {
        cout<<"请输入命令（回车结束）：";
        cin>>num;
    }
    return ;
}
