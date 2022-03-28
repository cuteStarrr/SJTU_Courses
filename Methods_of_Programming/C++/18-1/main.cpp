#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    int n=123;
    double f=1.234;
    char str[20]="Hello everyone!";
    cout<<oct<<n<<endl;
    cout<<showbase<<n<<endl;
    cout<<scientific<<f<<endl;
    cout<<uppercase<<scientific<<f<<endl;
    cout<<fixed;
    for(int i=2;i<5;++i)
        {cout.precision(i);
        cout<<f<<'\0';}
    cout<<endl;
    cout<<str<<endl;
    cout<<(void*)str<<endl;//cout<<&str<<endl;Ò²¿É
    cout.width(30);cout<<setfill('@')<<right<<str<<endl;
    cin>>oct>>n;cout<<hex<<n<<endl;
    cin.getline(str,12,'!');cout<<str;
    return 0;
}
