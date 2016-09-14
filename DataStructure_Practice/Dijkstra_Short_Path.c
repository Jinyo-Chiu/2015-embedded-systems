#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define FALSE 0
#define TRUE 1
#define MAX_VERTICES  8   //頂點數目
short int visited[MAX_VERTICES];

void shortestPath(int v,int cost[][MAX_VERTICES],int distance[],int n,short int found[])
{
  /* v=起始點,n=頂點數目,cost[][]=相鄰矩陣,distance[]存放最短路徑 例:v=5,distance[3]->代表從起始點5到頂點3的距離
     found[]=顯示路徑有沒有找到 例:found[4]=false代表頂點4的路徑還沒決定好*/

    int i,u,w;
    for(i=0;i<n;i++)
       {
          found[i]=FALSE;//一開始所有的頂點都還沒被決定好
          distance[i]=cost[v][i];//紀錄一開始從起始點v至各個頂點的距離
       }
    
    found[v]=TRUE;//一開始起始點已被決定
    distance[v]=0;//起始點為0
    for(i=0;i<n-2;i++)
       {
          u=choose(distance,n,found);
          found[u]=TRUE;    //頂點u已被決定
           for(w=0;w<n;w++)
             if(!found[w])    //若found[w]=flase
               if(distance[u]+cost[u][w]<distance[w])//（若起始點v到u + u到w)的距離 < （起始點v到w）
                 distance[w]=distance[u]+cost[u][w];  //w的路徑被更新
       }
}

int choose(int distance[],int n,short int found[])//挑選一個頂點
{
   int i,min,minpos;
   min=INT_MAX;//代表無窮
   minpos=-1;
   for(i=0;i<n;i++)
        if(distance[i]< min && !found[i] )//若distance[i]<INT_MAX,且若found[i]=flase,代表v,i有一還沒被決定的路徑
          { 
               min=distance[i];
               minpos=i;
          }

   return minpos;
}
int main(void)
{
    int distance[8]={0};
    int max=99999;    //代表無窮
    int i,j; 
   int cost[8][8]={{0,max,max,max,max,max,max,max},   //相鄰矩陣 代表一有向圖
                    {300,0,max,max,max,max,max,max},
                    {1000,800,0,max,max,max,max,max},
                    {max,max,1200,0,max,max,max,max},
                    {max,max,max,1500,0,250,max,max},
                    {max,max,max,1000,max,0,900,1400},
                    {max,max,max,max,max,max,0,1000},
                    {1700,max,max,max,max,max,max,0}};
  
    printf("Graph G=\n");
       for(i=0;i<8;i++)
         {
           printf("[%d]",i);
           for(j=0;j<8;j++)
            {
              if(cost[i][j]==max)
                printf("      X");
              else
               printf(" %6d",cost[i][j]);
            }
            printf("\n\n");
         }
   short int found[8];
   int start;
   while(1)
  {
    printf("\n選擇起始點(0-7)按-1離開\n");
    scanf("%d",&start);
     if(start==-1) break;
    if(start<0||start>7)   continue;
    shortestPath(start,cost,distance,8,found);
    for(i=0;i<8;i++)
      {
       if(distance[i]>=max) 
       printf("%d到%d的最短路徑=無窮\n",start,i);
        else
       printf("%d到%d的最短路徑=%d\n",start,i,distance[i]);
      }
   }
  system("pause");
 return 0;
}
