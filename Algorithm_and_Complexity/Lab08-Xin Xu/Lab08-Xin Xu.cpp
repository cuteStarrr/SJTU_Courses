#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
//Please put this source code in the same directory with SCC.in
//And do NOT change the file name.
/*
This function computes the number of Strongly Connected Components in a graph
Args:
    n: The number of nodes in the graph. The nodes are indexed as 0~n-1
    edge: The edges in the graph. For each element (a,b) in edge, it means
          there is a directed edge from a to b
          Notice that there may exists multiple edge and self-loop
Return:
    The number of strongly connected components in the graph.
*/

int SCC(int n, vector<pair<int,int>>& edge) {

    extern int* previsit=new int[n];
    extern int* postvisit=new int[n];
    extern int* visited=new int[n];
    extern int clock=1;

    for(int i=0;i<n;++i){
        visited[i]=0;
    }

    for(int i=0;i<n;++i){
        if(!visited[i]){
            EXPLORE(i,edge);
        }
    }

    extern int post_index;
    extern int post_max;
    
    MAX_NumIndex(n,post_index,post_max);

    extern vector<int> firstnum;
    extern vector<int> secondnum;
    int num;

    while(post_max!=0){
        EXPLORE_CC(post_index,edge);
        while(!firstnum.empty()){
            num=firstnum.back();
            firstnum.pop_back();
            for(int j=0;j<edge.size();++j){
                if(num==edge[j].first||num==edge[j].second){
                    edge.erase(edge.begin()+j,edge.begin()+j+1);
                }
            }
        }
        while(!secondnum.empty()){
            num=secondnum.back();
            secondnum.pop_back();
            for(int j=0;j<edge.size();++j){
                if(num==edge[j].first||num==edge[j].second){
                    edge.erase(edge.begin()+j,edge.begin()+j+1);
                }
            }
        }
        edge.push_back(make_pair<int,int>(-1,-1));
        MAX_NumIndex(n,post_index,post_max);
    }
    
    return edge.size();
}

void EXPLORE(int point,vector<pair<int,int>>& edge){

    visited[point]=1;
    previsit[point]=clock;
    ++clock;
    for(int j=0;j<edge.size();++j){
        if(edge[j].second==point){
            if(!visited[edge[j].first]){
                EXPLORE(edge[j].first,edge);
            }
        }
    }
    postvisit[point]=clock;
    ++clock;
}

void MAX_NumIndex(int n,int post_index,int post_max){


    post_index=0,
    post_max=postvisit[0];

    for(int i=1;i<n;++i){
        if(postvisit[i]>post_max){
            post_index=i;
            post_max=postvisit[i];
        }
    }
}

void EXPLORE_CC(int start,vector<pair<int,int>>& edge){

    visited[start]=0;
    postvisit[start]=0;
    for(int j=0;j<edge.size();++j){
        if(edge[j].first==start){
            if(visited[edge[j].second]){
                firstnum.push_back(edge[j].first);
                secondnum.push_back(edge[j].second);
                EXPLORE_CC(edge[j].second,edge);
            }
        }
    }
}

int SCC(int n, vector<pair<int,int>>& edge) {

    extern int previsit[n];
    extern int postvisit[n];
    extern int visited[n]={0};
    extern int clock=1;

    for(int i=0;i<n;++i){
        if(!visited[i]){
            EXPLORE(i,edge);
        }
    }

    extern int post_index;
    extern int post_max;
    
    MAX_NumIndex(n,post_index,post_max);

    extern vector<int> firstnum;
    extern vector<int> secondnum;
    int num;

    while(post_max!=0){
        EXPLORE_CC(post_index,edge);
        while(!firstnum.empty()){
            num=firstnum.back();
            firstnum.pop_back();
            for(int j=0;j<edge.size();++j){
                if(num==edge[j].first||num==edge[j].second){
                    edge.erase(edge.begin()+j,edge.begin()+j+1);
                }
            }
        }
        while(!secondnum.empty()){
            num=secondnum.back();
            secondnum.pop_back();
            for(int j=0;j<edge.size();++j){
                if(num==edge[j].first||num==edge[j].second){
                    edge.erase(edge.begin()+j,edge.begin()+j+1);
                }
            }
        }
        edge.push_back(make_pair<int,int>(-1,-1));
        MAX_NumIndex(n,post_index,post_max);
    }
    
    return edge.size();
}
//Please do NOT modify anything in main(). Thanks!
int main()
{
    int m,n;
    vector<pair<int,int>> edge;
    ifstream fin;
    ofstream fout;
    fin.open("SCC.in");
    cout<<fin.is_open()<<endl;
    fin>>n>>m;
    cout<<n<<" "<<m<<endl;
    int tmp1,tmp2;
    for(int i=0;i<m;i++)
    {
        fin>>tmp1>>tmp2;
        edge.push_back(pair<int,int>(tmp1,tmp2));
    }
    fin.close();
    int ans=SCC(n,edge);
    fout.open("SCC.out");
    fout<<ans<<'\n';
    fout.close();
    return 0;
}
