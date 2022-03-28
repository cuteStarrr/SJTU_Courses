#ifndef SAVINGACCOUNT_H_INCLUDED
#define SAVINGACCOUNT_H_INCLUDED

#include <iostream>
#include<cmath>
#include<cstring>

using namespace std;

class SavingAccount{
private:
    int account;
    char time[11];
    double money;
    static int num;
    static double rate;
public:
    static void Number(){++num;}
    SavingAccount(const char a[11]="0",double m=0.0)
{
    account=num;
    Number();
    strcpy(time,a);
    money=m;
}

    static void SetRate(double newrate){rate=newrate;}
    void Calculate(int n){money*=pow(1.0+rate,n);}
    void display()const{cout<<money<<endl;}
};


int SavingAccount::num=1;
double SavingAccount::rate=0.012;
#endif // SAVINGACCOUNT_H_INCLUDED
