#include"LongLongInt.h"


int main()
{
    LongLongInt a("12345678912345678900"),b("98765432198765432100"),c;
    c=a;
    c.display();
    c.addLong(a,b);
    c.display();
    return 0;
}

