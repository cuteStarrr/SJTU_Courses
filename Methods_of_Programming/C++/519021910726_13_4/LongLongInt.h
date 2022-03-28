#ifndef LONGLONGINT_H_INCLUDED
#define LONGLONGINT_H_INCLUDED
#include<cstring>
#include <iostream>

using namespace std;

extern int i,num;
extern bool flag;
extern char tmp;


class LongLongInt {
private:
    char *p;
    int n;//存放字符串的长度
    void Correct();
public:
    LongLongInt(char *ch="11");
    LongLongInt(const LongLongInt &z){
    if(p) delete []p;
    p=new char[z.n+1];
    n=z.n;
    strcpy(p,z.p);
    p[n]='\0';
}
    LongLongInt &operator=(const LongLongInt &l);
    void addLong (const LongLongInt &,const LongLongInt &);
    void display ()const {cout<<p<<endl;}
    ~LongLongInt(){if(p) delete [] p; }
};


#endif // LONGLONGINT_H_INCLUDED
