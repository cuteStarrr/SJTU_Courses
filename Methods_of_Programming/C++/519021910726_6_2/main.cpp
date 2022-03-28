//文件名：6_2
//寻找一个字符在字符串中的位置
#include <iostream>

using namespace std;

int main()
{
   char ch[81];
   int i,num=-1;
   char x;
   cout<<"Please input a string:";
   cin.getline(ch,81);
   cout<<'\n'<<"Please input a character:";
   cin.get(x);//保证能接收到所有字符
   for(i=0;i<=80;++i)//查找是否有相等的字符
    if(ch[i]==x)
        num=i;
    if(num>0)
        cout<<'\n'<<"Index="<<num;
    else cout<<'\n'<<"Not Found";
    return 0;
}
