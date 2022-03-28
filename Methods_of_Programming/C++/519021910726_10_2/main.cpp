//文件名：10_2
//判断一个字符是否在该字符串中出现，并输出字符串中该字符之后的内容
#include <iostream>
#include <cstring>
using namespace std;

int len,k,n,LEN;
char ch,*str,*newstr;
char *mystrrchr(char *str,char ch);
int main()
{
    cout<<"请输入字符串最大长度：";
    cin>>LEN;
    str=new char[LEN];
    cout<<"请输入一个字符串：";
    cin>>str;
    len=strlen(str);
    cout<<"请输入要查找的字符：";
    cin>>ch;
    newstr=mystrrchr(str,ch);
    if(newstr==NULL) cout<<"NULL";
    else  for(k=0;newstr[k]!='\0';++k)
             cout<<newstr[k];
    delete [] newstr;
    delete [] str;
    return 0;
}



//函数：char *mystrrchr(char *str,char ch)
//判断一个字符是否在该字符串中出现，并输出字符串中该字符最后出现的位置
char *mystrrchr(char *str,char ch)
{
    int i;
    for(i=len-1;i>=0;--i)
        if(str[i]==ch) return &(str[i]);
    return NULL;
}
