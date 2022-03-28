//文件名：6_4
//统计一篇英文文章的英文字母、数字、和其他非空白字符
#include <iostream>

using namespace std;

int main()
{
    char a[803];
    int n,i,eng=0,num=0,re=0;

    cout<<"请输入行数：";
    cin>>n;
    cout<<'\n'<<"请输入英文文章(以+结束)："<<'\n';
    cin.getline(a,803,'+');
    for(i=0;a[i]!='\0';++i)//依次读取每个字符
    {if('a'<=a[i]&&a[i]<='z') ++eng;//依次加入每种字符
    else {if('A'<=a[i]&&a[i]<='Z') ++eng;
          else if('0'<=a[i]&&a[i]<='9') ++num;
               else if(a[i]!=' ') ++re;}}
         cout<<'\n'<<"英文字母："<<eng<<endl;//输出结果
         cout<<"数字："<<num<<endl;
         cout<<"其他字符"<<re-n<<endl;

    return 0;
}
