//文件名：10_5
//利用随机数组成一个句子
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

int i,num[6],n;
char **p;
char *words[]={"The ","A ","One ","Some ","Any ","boy ","girl ","dog ","town ","car ","drove ","jumped ","ran ","walked ","skipped ","to ","from ","over ","under ","on ","the ","a ","one ","some ","any ","boy.","girl.","dog.","town.","car."};
int main()
{
    srand(time(NULL));
   num[0]=rand()*5/(RAND_MAX+1);
   num[1]=rand()*5/(RAND_MAX+1);
   num[2]=rand()*5/(RAND_MAX+1);
   num[3]=rand()*5/(RAND_MAX+1);
   num[4]=rand()*5/(RAND_MAX+1);
   num[5]=rand()*5/(RAND_MAX+1);
   p=words;
   for(i=0;i<6;++i)
    {
        n=num[i]+5*i;                      //此处将p看作一个指向字符串的指针数组，   另一种写法： n=num[i]+5*i;
        cout<<p[n];                        //实际上还可以将p视作指针                              p=words+n;
    }                                                                                           //cout<<*p;
    return 0;
}
