//控制海龟移动

#include"name.h"
void Move(int order,int left,int right,int n)
{
    int turn,i;
    turn=(right>left)? 0:1;
    switch(turn){
    case 0:d=right-left;d=d%4;
           switch(d){
    case 0:if(order==2){
              for(i=1;i<n+1;++i)
                    floor[r-i][c]=1;
              r=r-n;}
           else r=r-n;break;
    case 1:if(order==2){
              for(i=1;i<n+1;++i)
                    floor[r][c+i]=1;
              c=c+n;}
           else c=c+n;break;
    case 2:if(order==2){
              for(i=1;i<n+1;++i)
                    floor[r+i][c]=1;
              r=r+n;}
           else r=r+n;break;
    case 3:if(order==2){
              for(i=1;i<n+1;++i)
                    floor[r][c-i]=1;
              c=c-n;}
           else c=c-n;break;
    }break;
    case 1:d=left-right;d=d%4;
           switch(d){
    case 0:if(order==2){
              for(i=1;i<n+1;++i)
                    floor[r-i][c]=1;
              r=r-n;}
           else r=r-n;break;
    case 1:if(order==2){
              for(i=1;i<n+1;++i)
                    floor[r][c-i]=1;
              c=c-n;}
           else c=c-n;break;
    case 2:if(order==2){
              for(i=1;i<n+1;++i)
                    floor[r+i][c]=1;
              r=r+n;}
           else r=r+n;break;
    case 3:if(order==2){
              for(i=1;i<n+1;++i)
                    floor[r][c+i]=1;
              c=c+n;}
           else c=c+n;break;
    }break;
    }

}
