//文件名：9_1
//在数组中查找特定元素是否存在
#include <iostream>

using namespace std;
int search(int arr[],int n,int key);
int n,i,key,num;
int *p,*q;
int main()
{
    cout<<"Please input n:";
    cin>>n;
    p=new int[n];
    q=new int[n];
    cout<<"Please input"<<' '<<n<<' '<<"integers:";
    for(i=0;i<n;++i)
        cin>>p[i];
    cout<<"Please input key:";
    cin>>key;
    num=search(p,n,key);
    if(num==-1) cout<<"Not Found";
    else cout<<"Index=";
    for(i=0;i<num;++i)
        cout<<q[i]<<' ';
    delete []p;
    delete []q;
    return 0;
}


//函数：search(int arr[],int n,int key)
//在一个元素个数为n的数组arr中查找元素key
int search(int arr[],int n,int key)
{
    int k,m=0;
    bool flag=false;
    for(k=0;k<n;++k){
        if(arr[k]==key) {q[m]=k; ++m; flag=true;} //可能有多个下标，所以存到一个字符串里
    }
    if(!flag) return -1;
    else return m;

}
