#include <iostream>

using namespace std;

#define MAX 10000

const int n = 7;
double p[n + 1] = {0,0.04,0.06,0.08,0.02,0.10,0.12,0.14};
double q[n + 1] = {0.06,0.06,0.06,0.06,0.05,0.05,0.05,0.05};

int root[n + 1][n + 1];//Record the root node of the optimal subtree
double e[n + 2][n + 2];//Record the expected cost of the subtree
double w[n + 2][n + 2];//Record the probability sum of the subtree

void optimal_binary_search_tree(double *p,double *q,int n)
{
//The result is stored in e.
/*

Please write your code here.
*/

int i,j,k;
double MIN,tmp;

for(i=1;i<=n;++i){
    for(j=i;j<=n;++j){
        w[i][j]=q[i-1];
        for(k=i;k<=j;++k)
            w[i][j]=w[i][j]+q[k]+p[k];
    }
}

for(i=1;i<=n;++i){
    for(j=i-1;j>=0;--j)
        e[i][j]=0;
}

for(i=0;i<n;++i){
    for(j=1;j<=n-i;++j){
        MIN=MAX;
        for(k=j;k<=j+i;++k){
            tmp=e[j][k-1]+e[k+1][j+i];
            if(tmp<MIN)
                MIN=tmp;
        }
        e[j][j+i]=MIN+w[j][j+i];
    }
}

cout<<e[1][n]<<endl;

}

/*
You can print the structure of the optimal binary search tree based on root[][]
The format of printing is as follows:
k2 is the root
k1 is the left child of k2
d0 is the left child of k1
d1 is the right child of k1
k5 is the right child of k2
k4 is the left child of k5
k3 is the left child of k4
d2 is the left child of k3
d3 is the right child of k3
d4 is the right child of k4
d5 is the right child of k5
*/
void print_tree(int i, int j, int parent, bool isLeft)
{


if(i<=j&&i>0&&j<=n)
{
    cout<<'k'<<root[i][j]<<" is the ";
    if(isLeft)
        cout<<"left ";
    else
        cout<<"right ";
    cout<<"child of k"<<parent<<endl;

    print_tree(i,root[i][j]-1,root[i][j],true);
    print_tree(root[i][j]+1,j,root[i][j],false);

}

//if(i==j&&i>0&&i<=n){
//    cout<<'d'<<root[i][j]-1<<" is the left child of k"<<root[i][j]<<endl;
//   cout<<'d'<<root[i][j]<<" is the right child of k"<<root[i][j]<<endl;
//    return ;
//}

if(i>j){
    if(isLeft)
        cout<<'d'<<j<<" is the left child of k"<<parent<<endl;
    else
        cout<<'d'<<parent<<" is the right child of k"<<parent<<endl;
    return ;
}


return ;

}
void construct_optimal_bst(int i,int j)
{
//You can adjust the number of input parameters
/*
Please write your code here.
*/

double MIN=MAX;
int r,k;

if (j<i) return ;

for(k=i;k<=j;++k){
    if(e[i][k-1]+e[k+1][j]<MIN){
        MIN=e[i][k-1]+e[k+1][j];
        r=k;
    }
}

root[i][j]=r;
if(i==1&&j==n)
    cout<<'k'<<root[i][j]<<" is the root."<<endl;

construct_optimal_bst(i,r-1);
construct_optimal_bst(r+1,j);

}

int main()
{
    optimal_binary_search_tree(p,q,n);
    cout<<"The cost of the optimal binary search tree is: "<<e[1][n]<<endl;
    cout << "The structure of the optimal binary search tree is: " << endl;
    construct_optimal_bst(1,n);
    print_tree(1,root[1][n]-1,root[1][n],true);
    print_tree(root[1][n]+1,n,root[1][n],false);
}
