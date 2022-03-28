#include <iostream>
#include <fstream>


using namespace std;

int main()
{
    ifstream infile;
    infile.open("hello.cpp");
    ofstream outfile("hello_linenum.cpp");
    if(!infile) {cout<<"open wrong!"<<endl;return -1;}
    if(!outfile) {cout<<"create wrong!"<<endl;return -1;}
    int i=0;
    char tmp[80];
    while(!infile.eof())
    {
        infile.getline(tmp,80);
        i+=1;
        outfile<<i<<" "<<tmp<<endl;
    }
    infile.close();
    outfile.close();
    return 0;
}
