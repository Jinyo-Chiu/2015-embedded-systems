#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define ROW 12  //列
#define COL 15  //行
#define stackMAX ROW*COL
#define offs 8

 typedef struct
 {
   short int vert;//垂直 Y
   short int horiz;//水平 X
 }offsets;

offsets move[offs];//儲存移動方向的陣列 

//老鼠的移動表（有優先權 會先從正北方(vert=-1 horiz=0)開始選擇 若正北方不通再依序從順時針方向尋找）
void move_table() 
{
  move[0].vert=-1; move[0].horiz=0;
  move[1].vert=-1; move[1].horiz=1;
  move[2].vert=0;  move[2].horiz=1;
  move[3].vert=1;  move[3].horiz=1;
  move[4].vert=1;  move[4].horiz=0;
  move[5].vert=1;  move[5].horiz=-1;
  move[6].vert=0;  move[6].horiz=-1;
  move[7].vert=-1; move[7].horiz=-1;
}

typedef struct
{
  short int row;
   short int col;
  short int dir;
}element;

element stack[stackMAX];//推疊 有(row  col  dir)  三元素 
int top=-1;

void push(element a)
{
   if(top>=stackMAX-1)
      printf("推疊滿了\n");
   else
   {
     top++;
     stack[top].row=a.row;
     stack[top].col=a.col;
     stack[top].dir=a.dir;
   }
}
element pop()
{
   element x;
     if (top<=-1)
      {
         printf("推疊空了\n");
      }
    else
    {
      x.row=stack[top].row;
      x.col=stack[top].col;
      x.dir=stack[top].dir;
      top--;
      return x;
    }
}

//迷宮矩陣為row=12 col=15 不過Row跟Col各+2 為要防止走出邊界所以最外圍都是1    0=可以走  1=不能走
int maze[ROW+2][COL+2] = { {1  ,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,  1},

                           {1  ,0,1,0,0,0,1,1,0,0,0,1,1,1,1,1,  1},
                           {1  ,1,0,0,0,1,1,0,1,1,1,0,0,1,1,1,  1},
                           {1  ,0,1,1,0,0,0,0,1,1,1,1,0,0,1,1,  1},
                           {1  ,1,1,0,1,1,1,1,0,1,1,0,1,1,0,0,  1},
                           {1  ,1,1,0,1,0,0,1,0,1,1,1,1,1,1,1,  1},
                           {1  ,0,0,1,1,0,1,1,1,0,1,0,0,1,0,1,  1},
                           {1  ,0,0,1,1,0,1,1,1,0,1,0,0,1,0,1,  1},
                           {1  ,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,  1},
                           {1  ,0,0,1,1,0,1,1,0,1,1,1,1,1,0,1,  1},
                           {1  ,1,1,0,0,0,1,1,0,1,1,0,0,0,0,0,  1},
                           {1  ,0,0,1,1,1,1,1,0,0,0,1,1,1,1,0,  1},
                           {1  ,0,1,0,0,1,1,1,1,1,0,1,1,1,1,0,  1},

                           {1  ,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,  1} };

int mark[ROW+2][COL+2]={0};//計號矩陣  記錄老鼠走過的路 
int EXIT_ROW=ROW-1,EXIT_COL=COL;//終點的Row跟Col 

void path()//找尋路徑 
{
   int i,j, row, col, nextRow, nextCol, dir, found=0;
   element position;
   mark[1][1]=1;//起始點先做計號 
   top=0;
   stack[0].row=1;
   stack[0].col=1;
   stack[0].dir=1;

   while(top>-1 && found!=1)//當推疊不為空 
     {
       position=pop();//pop給position 
       row=position.row;
       col=position.col;
       dir=position.dir;
     
      while(dir<offs && found!=1)//dir<0ffs代表移動表還有可以走的路 
        { //以dir的方向移動    
           nextRow=row+move[dir].vert;//下一次移動的row 
           nextCol=col+move[dir].horiz;//下一次移動的col
          
           if(nextRow==EXIT_ROW && nextCol == EXIT_COL)//是否有發現終點 
              found=1;
           else  if(!maze[nextRow][nextCol] && !mark[nextRow][nextCol] )//合法的移動而且mark沒做記號 代表先前沒來過 
                  {
                      mark[nextRow][nextCol]=1;//做記號 
                      //儲存目前的位置和方向
                      position.row=row; 
                      position.col=col;
                      position.dir=++dir;
                      //保存至推疊 
                      push(position);
                      row=nextRow;
                      col=nextCol;
                      dir=0;
                  }
           else ++dir;              
         }    
      }
    
    if(found==1)//若發現終點 
    {     
        printf("老鼠走過的路\n");
        for(i=1;i<=ROW;i++)
        for(j=1;j<=COL;j++)
         {
          if(mark[i][j]!=0)
             printf("X ");//印出X代表老鼠走過的所有路逕
          else
          printf("%d ",mark[i][j]);  
          if(j==COL)
            printf("\n");
         }  
     printf("\n################################\n");
      printf("發現出口\n");      
       for(i=0;i<=top;i++)
         maze[ stack[i].row ][ stack[i].col ]=9;   
       maze[row][col]=9;
       maze[EXIT_ROW][EXIT_COL]=9;
       for(i=1;i<=ROW;i++)
        for(j=1;j<=COL;j++)
         {
          if(maze[i][j]==9)//印出最終路徑 
             printf("* ");
          else 
             printf("%d ",maze[i][j]);
             
          if(j==COL)
            printf("\n");         
         }              
    }    
   else 
      printf("the maze does not have a path\n");      
}

int main(void)
{
  move_table() ;
  path();
  return 0;     
}
