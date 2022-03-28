#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

struct studentT{
char name[21];
int year;
int month;
int day;
char tel[12];
char address[51];
};

int main()
{
    int n,i,j,k,m;
    struct studentT *p,tmp;
    bool flag;
    cout<<"Please input n(n<10):";
    cin>>n;
    cout<<endl;
    p=new studentT[n];
    for(i=0;i<n;++i)
    {
        cin.getline(p[i].name,20,' ');
        cin>>p[i].year>>p[i].month>>p[i].day;
        cin.getline(p[i].tel,12,' ');
        cin.getline(p[i].address,51);
    }
    for(i=1;i<n;++i)
    {
        flag=true;
        for(j=0;j<n-i;++j)
        {
            k=0;
            m=p[j].name[k]-p[j+1].name[k];
            while(!m&&p[j].name[k]!='\0'&&p[j+1].name[k]!='\0')
                {++k; m=p[j].name[k]-p[j+1].name[k];}
            if(m>0) {tmp=p[j+1];p[j+1]=p[j];p[j]=tmp;flag=false; }
        }
        if(flag) break;
    }
    ofstream outfile("address.txt",ios::out);
    if(!outfile)
        cerr<<"wrong!"<<endl;
    for(i=0;i<n;++i)
    {
        outfile.write(p[i].name,strlen(p[i].name));
        outfile<<' '<<p[i].year<<'/'<<p[i].month<<'/'<<p[i].day<<' ';
        outfile.write(p[i].tel,strlen(p[i].tel));
        outfile.write(p[i].address,strlen(p[i].address));
        outfile<<endl;
    }
    outfile.close();
    delete []p;
    return 0;
}
