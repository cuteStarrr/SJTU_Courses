#include"SavingAccount.h"

int main()
{
    SavingAccount ac1("2019.10.01",10.0);
    SavingAccount ac2("2018.01.01",20.0);
    SavingAccount ac3("2017.02.01",30.0);
    ac1.Calculate(3);
    ac2.Calculate(3);
    ac3.Calculate(3);
    SavingAccount::SetRate(0.015);
    ac1.Calculate(3);
    ac2.Calculate(3);
    ac3.Calculate(3);
    ac1.display();
    ac2.display();
    ac3.display();
    return 0;
}
