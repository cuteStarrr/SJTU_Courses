#include"Time.h"

int main()
{
    Time t1(23,59,58),t2(23,59,58);
    ++t1;
    cout<<t1<<endl;
    --t2;
    cout<<t2<<endl;
    t1+=70;
    cout<<t1<<endl;
    t2-=80;
    cout<<t2<<endl;
    cout<<t1-t2<<endl;
    return 0;
}
