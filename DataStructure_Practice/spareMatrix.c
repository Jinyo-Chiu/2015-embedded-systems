#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#define MAX_TERMS 101
#define MAX_ROW 6  //�x�}���C
#define MAX_COL 6  //�x�}�����

typedef struct//���}���x�}�Ϊ����c
{
   int col;
   int row;
   int value;
}term;


void fastTranspose(term a[], term b[] )//��P�禡
{
   int rowterms[MAX_COL]  ,  startingPos[MAX_COL];
   int i,j;
   int numCols =a[0].col;   //a[]�����
   int numTerms=a[0].value;  //a[]���D�s�Ȫ��ƥ�
   b[0].row = numCols;     //b[]���C���ܦ�a[]�����
   b[0].col = a[0].row;   //b[]������ܦ�a[]���C��
   b[0].value=numTerms;//�D�s�Ȫ��ƥ�
   
   if(numTerms>0)//�Y�O�D�s�x�}
    {
       for(i=0;i<numCols;i++)// rowterms���]��0
          rowterms[i]=0;
     
      /*�p��C�@�C���h�֭ӫD�s��  �ҡG�D�s��8�� ��6�C :��(0,1,4)(0,2,7)(0,5,2)(2,1,4)(2,4,9),(4,5,8),(4,4,5),(5,1,9)
          ��0�C��3�� ��2�C��2�� ��4�C��2�� ��5�C��1�� �@8��*/
       for(i=1;i<= numTerms;i++)
          rowterms[ a[i].col ]++;
      
       startingPos[0]= 1;
       for(i=1;i<numCols; i++)
         startingPos[i]= startingPos[i-1]+rowterms[i-1];//rowterms[i-1]=��i-1�C���X�C,startingPos[i-1]=��i-1�C���_�l��m
       
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
        if(*totalD<MAX_TERMS)//��JRow,Col,Value��d[]
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

int COMPARE(int a,int newb)//���a b ��Ȫ��j�p
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
  if(colsA != b[0].row)//�Ya[]��Col������b[]��Row ���~
   {
     fprintf(stderr,"Incompatible  matrices\n");
     exit(EXIT_FAILURE);
   }

   fastTranspose(b,newB);//newB=b����m
   
   //�]�w��ɱ���
  a[ totalA+1 ].row=rowsA;  //�Na[].row�s�W�@���J����rowsA  
  newB[ totalB+1 ].row=colsB;  //�NnewB[].row�s�W�@���J����colsB
  newB[ totalB+1 ].col=0;  //�NnewB.col�s�W�@���0
  
  for(i=1;i<=totalA ;)
   {
      column=newB[1].row;        //column�ܦ�newB[]���Ĥ@�C�����e��
       for(j=1;j<=totalB+1;)
       {
          if(a[i].row != row)     //row=a[1].row �Y��a[i].row���۵�
            {
              storeSum(d,&totalD,row,column,&sum);
               i=rowBegin;
               for(; newB[j].row==column ;j++)  {}  //�o���newB[j].row�I��column�ɪ� j��
        
               column=newB[j].row;
             } 
           else if(newB[j].row != column)
             {
               storeSum(d,&totalD,row,column,&sum);
               i=rowBegin;
               column=newB[j].row;  
             }
           else 
             switch( COMPARE( a[i].col,newB[j].col) )//���a[i].col�MnewB[j].col���j�p
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

       for(; a[i].row==row;i++) {}  //�o���a[i].row�I��row�ɪ� i��
       rowBegin = i ,row=a[i].row;
    }
  d[0].row=rowsA;
  d[0].col=colsB;
  d[0].value=totalD;
}

void spareCreate(term d[],int value)//�гy�X�@�ӵ}���x�}
{
  int i=0,j=0;
  term temp;
  d[0].row=MAX_ROW;d[0].col=MAX_COL;d[0].value=value;//��0��s�� �]Row���j�p,Col���j�p,�D�s���`�ƥء^
   for(i=1;i<=value;i++)//�qd[1]�}�l�s����
   {  
      d[i].row=rand()%MAX_ROW;//�ζü��H������Row
      d[i].col=rand()%MAX_COL;//�ζü��H������Col
      d[i].value=rand()%9+1;//
       for(j=1;j<i;j++)
       {
         //�ˬd�O�_���ۦP��Row��Col,��:d[2]=(0,5,5),d[3]=(0,5,8),�Nd[3]�h�^�h���s���ü�
         if((d[i].row==d[j].row)&&(d[i].col==d[j].col))
           { 
             i--;
             break;
           }
       }
   }
   for(i=value;i>1;i--)//�qd[1]�}�l�Nrow�Ƨ�
     {
      for(j=2;j<=i;j++)
       if(d[j-1].row>d[j].row)//�Y(d[j-1].row)�j�󥦪���@��(d[j].row)�h��̤���Row,Col
         {
          temp.row=d[j-1].row;
           temp.col=d[j-1].col;
          d[j-1].row=d[j].row;
          d[j-1].col=d[j].col;
          d[j].row=temp.row;
           d[j].col=temp.col;
         }
     }

    for(i=value;i>1;i--)//�qd[1]�}�l�Ncol�Ƨ�
      {
        for(j=2;j<=i;j++)
         if((d[j].row==d[j-1].row)&&(d[j-1].col>d[j].col))//�Y(d[j-1].col)�j�󥦪���@��(d[j].col)�B���row�Ȥ@�˴N����
          {
             temp.col=d[j].col;
             d[j].col=d[j-1].col;
             d[j-1].col=temp.col;
          }
      }
}

int main(void)
{
  term a[MAX_TERMS]={0},b[MAX_TERMS]={0},d[MAX_TERMS]={0};//�ŧi��term���A���}�C
  srand(time(NULL));
  int i=0,j=0,numA,numB;
  printf("Please Enter a[]'s number:");//��Ja[] ���D�s�ȼƥ�
    scanf("%d",&numA);
   spareCreate(a,numA);//���͵}�� a[]
  printf("Please Enter b[]'s number:");
   scanf("%d",&numB);//��Jb[] ���D�s�ȼƥ�
   
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


