#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define ROW 12  //�C
#define COL 15  //��
#define stackMAX ROW*COL
#define offs 8

 typedef struct
 {
   short int vert;//���� Y
   short int horiz;//���� X
 }offsets;

offsets move[offs];//�x�s���ʤ�V���}�C 

//�ѹ������ʪ�]���u���v �|���q���_��(vert=-1 horiz=0)�}�l��� �Y���_�褣�q�A�̧Ǳq���ɰw��V�M��^
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

element stack[stackMAX];//���| ��(row  col  dir)  �T���� 
int top=-1;

void push(element a)
{
   if(top>=stackMAX-1)
      printf("���|���F\n");
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
         printf("���|�ŤF\n");
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

//�g�c�x�}��row=12 col=15 ���LRow��Col�U+2 ���n����X��ɩҥH�̥~�򳣬O1    0=�i�H��  1=���ਫ
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

int mark[ROW+2][COL+2]={0};//�p���x�}  �O���ѹ����L���� 
int EXIT_ROW=ROW-1,EXIT_COL=COL;//���I��Row��Col 

void path()//��M���| 
{
   int i,j, row, col, nextRow, nextCol, dir, found=0;
   element position;
   mark[1][1]=1;//�_�l�I�����p�� 
   top=0;
   stack[0].row=1;
   stack[0].col=1;
   stack[0].dir=1;

   while(top>-1 && found!=1)//����|������ 
     {
       position=pop();//pop��position 
       row=position.row;
       col=position.col;
       dir=position.dir;
     
      while(dir<offs && found!=1)//dir<0ffs�N���ʪ��٦��i�H������ 
        { //�Hdir����V����    
           nextRow=row+move[dir].vert;//�U�@�����ʪ�row 
           nextCol=col+move[dir].horiz;//�U�@�����ʪ�col
          
           if(nextRow==EXIT_ROW && nextCol == EXIT_COL)//�O�_���o�{���I 
              found=1;
           else  if(!maze[nextRow][nextCol] && !mark[nextRow][nextCol] )//�X�k�����ʦӥBmark�S���O�� �N����e�S�ӹL 
                  {
                      mark[nextRow][nextCol]=1;//���O�� 
                      //�x�s�ثe����m�M��V
                      position.row=row; 
                      position.col=col;
                      position.dir=++dir;
                      //�O�s�ܱ��| 
                      push(position);
                      row=nextRow;
                      col=nextCol;
                      dir=0;
                  }
           else ++dir;              
         }    
      }
    
    if(found==1)//�Y�o�{���I 
    {     
        printf("�ѹ����L����\n");
        for(i=1;i<=ROW;i++)
        for(j=1;j<=COL;j++)
         {
          if(mark[i][j]!=0)
             printf("X ");//�L�XX�N��ѹ����L���Ҧ����w
          else
          printf("%d ",mark[i][j]);  
          if(j==COL)
            printf("\n");
         }  
     printf("\n################################\n");
      printf("�o�{�X�f\n");      
       for(i=0;i<=top;i++)
         maze[ stack[i].row ][ stack[i].col ]=9;   
       maze[row][col]=9;
       maze[EXIT_ROW][EXIT_COL]=9;
       for(i=1;i<=ROW;i++)
        for(j=1;j<=COL;j++)
         {
          if(maze[i][j]==9)//�L�X�̲׸��| 
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
  
  system("pause");
  return 0;     
}

