#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#define MAX_TERMS 101
#define MAX_ROW 6  //矩陣的列
#define MAX_COL 6  //矩陣的行數

typedef struct//給稀疏矩陣用的結構
{
   int col;
   int row;
   int value;
}term;


void fastTranspose(term a[], term b[] )//轉致函式
{
   int rowterms[MAX_COL]  ,  startingPos[MAX_COL];
   int i,j;
   int numCols =a[0].col;   //a[]的行數
   int numTerms=a[0].value;  //a[]的非零值的數目
   b[0].row = numCols;     //b[]的列數變成a[]的行數
   b[0].col = a[0].row;   //b[]的行數變成a[]的列數
   b[0].value=numTerms;//非零值的數目
   
   if(numTerms>0)//若是非零矩陣
    {
       for(i=0;i<numCols;i++)// rowterms先設為0
          rowterms[i]=0;
     
      /*計算每一列有多少個非零值  例：非零值8個 有6列 :為(0,1,4)(0,2,7)(0,5,2)(2,1,4)(2,4,9),(4,5,8),(4,4,5),(5,1,9)
          第0列有3個 第2列有2個 第4列有2個 第5列有1個 共8個*/
       for(i=1;i<= numTerms;i++)
          rowterms[ a[i].col ]++;
      
       startingPos[0]= 1;
       for(i=1;i<numCols; i++)
         startingPos[i]= startingPos[i-1]+rowterms[i-1];//rowterms[i-1]=第i-1列有幾列,startingPos[i-1]=第i-1列的起始位置
       
       for(i=1; i<=numTerms; i++)
         {
           j=startingPos[ a[i].col ]++;
           b[j].row=a[i].col;
           b[j].col=a[i].row;
           b[j].value=a[i].value;
         }  
    }
}
void storeSum(term d[],int *totalD,int row,int column,int *sum)
{
  if(*sum!=0)
    {
        if(*totalD<MAX_TERMS)//填入Row,Col,Value至d[]
      {
        d[++*totalD].row=row;
        d[*totalD].col=column;
        d[*totalD].value=*sum;
        *sum=0;
       }
      else 
       {
         fprintf(stderr,"Numbers of terms in product exceeds %d\n",MAX_TERMS);
         exit(EXIT_FAILURE);
       }
    }
}

int COMPARE(int a,int newb)//比較a b 兩值的大小
{
   if(a>newb) return 1;
   else if(a==newb)
              return 0;
   else if(a<newb)
             return -1;
}

void mmult(term a[],term b[],term d[])
{
   int i , j , column , totalB=b[0].value,colsB=b[0].col;
   int rowsA=a[0].row , colsA=a[0].col ,totalA=a[0].value;
   int rowBegin=1 , row=a[1].row;
   term newB[MAX_TERMS];//???????
   int totalD=0 ;
   int sum=0;
  if(colsA != b[0].row)//若a[]的Col不等於b[]的Row 錯誤
   {
     fprintf(stderr,"Incompatible  matrices\n");
     exit(EXIT_FAILURE);
   }

   fastTranspose(b,newB);//newB=b的轉置
   
   //設定邊界條件
  a[ totalA+1 ].row=rowsA;  //將a[].row新增一格填入元素rowsA  
  newB[ totalB+1 ].row=colsB;  //將newB[].row新增一格填入元素colsB
  newB[ totalB+1 ].col=0;  //將newB.col新增一格填0
  
  for(i=1;i<=totalA ;)
   {
      column=newB[1].row;        //column變成newB[]的第一列的內容值
       for(j=1;j<=totalB+1;)
       {
          if(a[i].row != row)     //row=a[1].row 若跟a[i].row不相等
            {
              storeSum(d,&totalD,row,column,&sum);
               i=rowBegin;
               for(; newB[j].row==column ;j++)  {}  //得到當newB[j].row！＝column時的 j值
        
               column=newB[j].row;
             } 
           else if(newB[j].row != column)
             {
               storeSum(d,&totalD,row,column,&sum);
               i=rowBegin;
               column=newB[j].row;  
             }
           else 
             switch( COMPARE( a[i].col,newB[j].col) )//比較a[i].col和newB[j].col的大小
              {
                case 1:
                       i++;  
                       break;
                case 0:
                       sum+=( a[i++].value*newB[j++].value);
                       break;
                case -1:
                       j++;break; 
              }
        }

       for(; a[i].row==row;i++) {}  //得到當a[i].row！＝row時的 i值
       rowBegin = i ,row=a[i].row;
    }
  d[0].row=rowsA;
  d[0].col=colsB;
  d[0].value=totalD;
}

void spareCreate(term d[],int value)//創造出一個稀疏矩陣
{
  int i=0,j=0;
  term temp;
  d[0].row=MAX_ROW;d[0].col=MAX_COL;d[0].value=value;//第0格存放 （Row的大小,Col的大小,非零值總數目）
   for(i=1;i<=value;i++)//從d[1]開始存放資料
   {  
      d[i].row=rand()%MAX_ROW;//用亂數隨機產生Row
      d[i].col=rand()%MAX_COL;//用亂數隨機產生Col
      d[i].value=rand()%9+1;//
       for(j=1;j<i;j++)
       {
         //檢查是否有相同的Row跟Col,例:d[2]=(0,5,5),d[3]=(0,5,8),將d[3]退回去重新取亂數
         if((d[i].row==d[j].row)&&(d[i].col==d[j].col))
           { 
             i--;
             break;
           }
       }
   }
   for(i=value;i>1;i--)//從d[1]開始將row排序
     {
      for(j=2;j<=i;j++)
       if(d[j-1].row>d[j].row)//若(d[j-1].row)大於它的後一格(d[j].row)則兩者互換Row,Col
         {
          temp.row=d[j-1].row;
           temp.col=d[j-1].col;
          d[j-1].row=d[j].row;
          d[j-1].col=d[j].col;
          d[j].row=temp.row;
           d[j].col=temp.col;
         }
     }

    for(i=value;i>1;i--)//從d[1]開始將col排序
      {
        for(j=2;j<=i;j++)
         if((d[j].row==d[j-1].row)&&(d[j-1].col>d[j].col))//若(d[j-1].col)大於它的後一格(d[j].col)且兩者row值一樣就互換
          {
             temp.col=d[j].col;
             d[j].col=d[j-1].col;
             d[j-1].col=temp.col;
          }
      }
}

int main(void)
{
  term a[MAX_TERMS]={0},b[MAX_TERMS]={0},d[MAX_TERMS]={0};//宣告為term型態的陣列
  srand(time(NULL));
  int i=0,j=0,numA,numB;
  printf("Please Enter a[]'s number:");//輸入a[] 的非零值數目
    scanf("%d",&numA);
   spareCreate(a,numA);//產生稀疏 a[]
  printf("Please Enter b[]'s number:");
   scanf("%d",&numB);//輸入b[] 的非零值數目
   
   spareCreate(b,numB);
   mmult( a, b, d);  //a[]*b[] 

   printf("Matrix a=\n");
   printf("Num    Row    Col    value");
    for(i=0;i<=a[0].value;i++)
      printf("\n[%d]    [%d]    [%d]    [%d]",i,a[i].row,a[i].col,a[i].value);

   printf("\nMatrix b=\n");
   printf("Num    Row    Col    value");
    for(i=0;i<=b[0].value;i++)
      printf("\n[%d]    [%d]    [%d]    [%d]",i,b[i].row,b[i].col,b[i].value);
  
   printf("\n Matrix d=a*b=\n");
   printf("Num    Row    Col    value");
    for(i=0;i<=d[0].value;i++)
      printf("\n[%d]    [%d]    [%d]    [%d]",i,d[i].row,d[i].col,d[i].value); 
  printf("\n");
  system("pause");
  return 0;  
}


