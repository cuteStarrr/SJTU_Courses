#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
/*
The process to calculate the dynamic can be divided into four steps:
1.Create an empty cost matrix DTW with X and Y labels as amplitudes of the two series to be compared.
2.Use the given state transition function to fill in the cost matrix.
3.Identify the warping path starting from top right corner of the matrix and traversing to bottom left. The traversal path is identified based on the neighbor with minimum value.
i.e., When we reach the point (i, j) in the matrix, the next position is to choose the point with the smallest cost among (i-1,j-1), (i,j-1), and (i-1,j),
For the sake of simplicity, when the cost is equal, the priority of the selection is (i-1,j-1), (i,j-1), and (i-1,j) in order.
4.Calculate th time normalized distance. We define it as the average cost of the selected points.
*/
using namespace std;
double max(double x,double y){
    if(x>y) return x;
    return y;
}

double Min(double x,double y){
    if(x>y) return y;
    return x;
}

double distance_w(vector<int> x, vector<int> y,int w){
    int n = x.size();
    int m = y.size();
    int tw;
    tw=((n-m>0)? (n-m):(m-n));
    tw=max(w,tw);
        
    vector<vector<int> > DTW;
    //Use the given state transition function to fill in the cost matrix.
    /*
    Please write your code here.
    */
   #define MAX 10000

   int i,j,distan,min;

   for(i=0;i<=n;++i)
       DTW[i].resize(m+1);

   for(i=0;i<=n;++i){
       for(j=0;j<=m;++j)
           DTW[i][j]=MAX;
   }


   DTW[0][0]=0;

   for(i=1;i<=n;++i){
       for(j=max(1,i-tw);j<=Min(m,i+tw);++j){
           distan=(x[i]-y[j]>0)? (x[i]-y[j]):-(x[i]-y[j]);
           min=Min(DTW[i-1][j-1],DTW[i][j-1]);
           min=Min(min,DTW[i-1][j]);
           DTW[i][j]=distan+min;
       }
   }

    vector<int> d;
    //Identify the warping path.
    /*
    Please write your code here.
    */

   i=n;
   j=m;
   int u,v;

   d.push_back(DTW[i][j]);
   while(i>0||j>0){
       min=DTW[i-1][j-1];
       u=i-1;
       v=j-1;
       if(DTW[i][j-1]<min)
           min=DTW[i][j-1];
           u=i;
           v=j-1;
       if(DTW[i-1][j]<min)
           min=DTW[i-1][j];
           u=i-1;
           v=j;
       d.push_back(min);
       i=u;
       j=v;
   }
   d.push_back(DTW[0][0]);


    double ans = 0;
    //Calculate th time normalized distance
    /*
    Please write your code here.
    */
    j=d.size();

   for(i=0;i<=j;++i)
   {
       ans=ans+i*d.back();
       d.pop_back();
   }
   ans=ans/j;
   return ans;
}


double distance(vector<int> x, vector<int> y) {
    int n = x.size();
    int m = y.size();
    vector<vector<int> > DTW;
    //Use the given state transition function to fill in the cost matrix.
    /*
    Please write your code here.
    */
   #define MAX 10000

   int i,j,distan,min;

   for(i=0;i<=n;++i)
       DTW[i].resize(m+1);

   for(i=0;i<=n;++i){
       for(j=0;j<=m;++j)
           DTW[i][j]=MAX;
   }

   DTW[0][0]=0;

   for(i=1;i<=n;++i){
       for(j=1;j<=m;++j){
           distan=(x[i]-y[j]>0)? (x[i]-y[j]):-(x[i]-y[j]);
           min=Min(DTW[i-1][j-1],DTW[i][j-1]);
           min=Min(min,DTW[i-1][j]);
           DTW[i][j]=distan+min;
       }
   }

    vector<int> d;
    //Identify the warping path.
    /*
    Please write your code here.
    */

   i=n;
   j=m;
   int u,v;

   d.push_back(DTW[i][j]);
   while(i>0||j>0){
       min=DTW[i-1][j-1];
       u=i-1;
       v=j-1;
       if(DTW[i][j-1]<min)
           min=DTW[i][j-1];
           u=i;
           v=j-1;
       if(DTW[i-1][j]<min)
           min=DTW[i-1][j];
           u=i-1;
           v=j;
       d.push_back(min);
       i=u;
       j=v;
   }
   d.push_back(DTW[0][0]);


    double ans = 0;
    //Calculate th time normalized distance
    /*
    Please write your code here.
    */
    j=d.size();

   for(i=0;i<=j;++i)
   {
       ans=ans+i*d.back();
       d.pop_back();
   }
   ans=ans/j;
    return ans;
}

int main(){
	vector<int> X,Y;
	//test case 1
	X = {37,37,38,42,25,21,22,33,27,19,31,21,44,46,28};
	Y = {37,38,42,25,21,22,33,27,19,31,21,44,46,28,28};
	cout<<distance(X,Y)<<endl;
	//test case 2
	X = {11,14,15,20,19,13,12,16,18,14};
	Y = {11,17,13,14,11,20,15,14,17,14};
	cout<<distance(X,Y)<<endl;
	//Remark: when you modify the code to add the window constraint, the distance function has thus three inputs: X, Y, and the size of window w.
	return 0;
}
