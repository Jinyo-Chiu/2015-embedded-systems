#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#define size 50 //�h�������̤j����

typedef struct polynomial  
{
  int expn;//  ����
  float ceof;// �Y��
}poly;

void Poly_Attach(poly n[],float Ceof,int Expn);  //���J�h����
void Poly_Remove(poly n[],int Expn);             //�R���h����
poly *Single_Mult(poly b[],float Ceof,int Expn); //�h������@�����k
poly *Muilt(poly a[],poly b[]);                  //�h�������k
void AddPoly(poly a[],poly b[],poly c[]);        //�h�����[�k

void Poly_Zero(poly n[])//�гy�X�@�ӹs�h����
{
   int i;
   for(i=0;i<size;i++)
    {
      n[i].expn=0;
      n[i].ceof=0.0;
     }
}
int Poly_IsZero(poly n[])//�P�_�O�_���s�h���� �Y�O�h�Ǧ^  1
{
  if(n[0].ceof!=0)//�Y�Y�Ƥ����s
        return -1;
    else 
        return 1;
  
}
int LeadExp(poly n[])  //�Ǧ^�@�h�������̰�����
{
   return n[0].expn;
}
float Coef(poly n[],int Expn)  //�Ǧ^�Y�@���趵���Y��
{
     int i,flag=0;
     if(Poly_IsZero(n)==1)//�Y���s�h���� �Ǧ^0
       return 0;

     for(i=0;n[i].ceof!=0;i++)
     {
         if(n[i].expn==Expn&&n[i].ceof!=0)
           {
            flag=1;  //�N����즸��
            return n[i].ceof;
           } 
      }
    if(flag==0)//�S�����
       {
         fprintf(stderr,"Coef() is Error\n");
          getch(); 
          exit(-1);
       }
}
void Poly_Attach(poly n[],float Ceof,int Expn)//���J�@�Ӷ��� ��h����
{     
     int i,j=0,flag=0;
      poly temp; 
        
       for(i=0;n[i].ceof!=0;i++) //
           {
           if((n[i].expn==Expn))//�Y�n���J�����趵 �b���h�����w�s�b �h��ܿ��~
                  {
                fprintf(stderr,"Attach() is Error !\n");
                   getch(); 
                   exit(-1); 
                  }
           }
       if(Poly_IsZero(n)==1)//�Y���h�����O�s�h����  �h�i�H�������J
           {
          n[0].expn=Expn;
          n[0].ceof=Ceof;
           } 
       else //�}�l���J�h����
         {
         for(i=0;n[i].ceof!=0;i++)  {} //��X���h��������

           n[i].expn=Expn;//�N�n���J���s���趵 �����J���h����������
           n[i].ceof=Ceof;//�N�n���J���s�Y�ƶ� �����J���h����������
            for(j=i;j>0;j--)
               {
                if(n[j].expn>n[j-1].expn)//�q�h�����ѫ᩹�e��� �M��洫  
                    {
                 temp.expn=n[j-1].expn;
                 temp.ceof=n[j-1].ceof; 
                 n[j-1].expn=n[j].expn;  
                 n[j-1].ceof=n[j].ceof;
                 n[j].expn=temp.expn;
                 n[j].ceof= temp.ceof;
                    }
               }
         }
  
 }
void Poly_Remove(poly n[],int Expn)//�R���h�������䤤�@��
{
   int i,flag=0;
    for(i=0;n[i].ceof!=0;i++)
      {
         if(n[i].expn==Expn)//�h�������o�@��
          {
            int j;
            for(j=i;n[j].ceof!=0;j++)//��n�R�������л\�� �ѫ᭱�����@�Ӥ@�ӸɤW
               {
              n[j].expn=n[j+1].expn;
              n[j].ceof=n[j+1].ceof;
                }
             flag=1;//�N��R�����\
              
          }
     }  
  if(flag==0)//�R������
     {
      fprintf(stderr,"Remove() is Error \n");
      getch(); 
      exit(-1);
     }         
}
int Compare(int a,int b)//���a,b
{
  if(a>b) 
     return 1;
  else if(a==b)
     return 0;
  else if(a<b)
     return -1;
}
void AddPoly(poly a[],poly b[],poly add_Result[])//����h�����[�k
{
    float sum=0.0;
   poly A[size],B[size];
   Poly_Zero(A);
   Poly_Zero(B);
   memcpy(A,a,size*sizeof(poly));//�]��a[]�٭n�Ψ� �ҥH�ƻs�t�@�Ӧۤv A[]�Ӵ��N
   memcpy(B,b,size*sizeof(poly));//�]��b[]�٭n�Ψ� �ҥH�ƻs�t�@�Ӧۤv B[]�Ӵ��N
       while((Poly_IsZero(A)==-1)&&(Poly_IsZero(B)==-1)) //��A[],B[]�������Ů�
       {
         switch( Compare(LeadExp(A),LeadExp(B)))//���A[],B[]���̰�����
         {
          case 1:  //A>B                                             
                   Poly_Attach( add_Result,Coef(A,LeadExp(A)),LeadExp(A) ); //���J�h����A��X�����h����
                   Poly_Remove(A,LeadExp(A));   //�R��A���̰�����
                   break;
          case 0://A==B
                
                   sum=Coef(A,LeadExp(A))+Coef(B,LeadExp(B));   //A,B ����ۦP �Y�Ƭۥ[��sum
                   if(sum!=0)
                       {
                   Poly_Attach(add_Result,sum,LeadExp(A));
                   Poly_Remove(A,LeadExp(A));  //�R��A���̰�����
                   Poly_Remove(B,LeadExp(B));  //�R��B���̰�����
                       }
                   break;
         case -1: //A<B                                                
                   Poly_Attach(add_Result,Coef(B,LeadExp(B)),LeadExp(B) );//���J�h����B��X�����h����
                   Poly_Remove(B,LeadExp(B));    //�R��B���̰�����
                   break;
        }
      }
  if(Poly_IsZero(A)<0) //�Y�h����A���Ѿl��  �h�������J�ܦX�����h���� �çR���̰�����
     {
      for(;A[0].ceof!=0;Poly_Attach(add_Result,Coef(A,LeadExp(A)),LeadExp(A)),Poly_Remove(A,LeadExp(A))) {}
     }
  else if(Poly_IsZero(B)<0)//�Y�h����B���Ѿl��  �h�������J�ܦX�����h���� �çR���̰�����
     {
      for(;B[0].ceof!=0;Poly_Attach(add_Result,Coef(B,LeadExp(B)),LeadExp(B)),Poly_Remove(B,LeadExp(B))) {}
     }
       
}
poly *Single_Mult(poly b[],float Ceof,int Expn)//����涵�����k
{
   static poly Result[size];//�ŧi������  �]���n�N��Ӱ}�C�Ǧ^�h 
   Poly_Zero(Result);
   int i;
   memcpy(Result,b,size*sizeof(poly));
   for(i=0;Result[i].ceof!=0;i++)
   {
     Result[i].ceof=Result[i].ceof*Ceof;
     Result[i].expn=Result[i].expn+Expn;
    }   
    return Result; 
}
poly *Muilt(poly a[],poly b[])//�h�������k
{ 
   static poly Result[size];//���G�}�C
          Poly_Zero(Result);
  poly *temp;        //�Ȧs���� �Ψ�Ū��Single_Mult�]�^�ǨӪ��}�C
  poly  trans[size];//��e�}�C
  Poly_Zero(trans);
  int i;
   for(i=0;a[i].ceof!=0;i++)
   {
     temp=Single_Mult(b,a[i].ceof,a[i].expn);
     AddPoly(temp,Result,trans);   //�[�k�����G�|�Q���trans
     memcpy(Result,trans,size*sizeof(poly)); //�M��Ntrans�ƻs��Result[]
     Poly_Zero(trans);  //�Ntrans�M��  �M��A�h����s���[�k  �ҥHResult[]�|�@���֥[ �ܤj                      
   }
 return Result;
}
int main(void)
{
     poly a[size],b[size],add_Result[size];
     Poly_Zero(a);
     Poly_Zero(b);
     Poly_Zero(add_Result);
     poly *muilt_Result; //���k����  
     float ceof;  //�Y��
     int   expn;  //���� 

     int   i,length;
     printf("��JA(X)  �аݭn�X���H\n");
      scanf("%d",&length);
    for (i=0; i<length; i++)
    {
     printf("��%d�� �Y�ơG  ����:  ",i+1);
     scanf("%f  %d",&ceof,&expn);
     Poly_Attach(a,ceof,expn);   //���J�h����
     }
   printf("\n��JB(X)  �аݭn�X���H\t");
    scanf("%d",&length);
    for (i=0; i<length; i++)
    {
     printf("��%d�� �Y�ơG  ����:\t",i+1);
        scanf("%f  %d",&ceof,&expn);
     Poly_Attach(b,ceof,expn);//���J�h����
    }
    AddPoly(a,b,add_Result);//����[�k 
    printf("The A(x)+B(X)=\n");
    for(i=0;add_Result[i+1].ceof!=0;i++)
       printf("%.2fX^%d+",add_Result[i].ceof,add_Result[i].expn);
    printf("%.2fX^%d",add_Result[i].ceof,add_Result[i].expn);

     printf("\n\n\n");
     printf("The A(x)*B(x)=\n");
  
     muilt_Result=Muilt(a,b);//���歼�k 
    for(i=0;muilt_Result[i+1].ceof!=0;i++)   
      printf("%.2fX^%d+",muilt_Result[i].ceof,muilt_Result[i].expn);
   printf("%.2fX^%d",muilt_Result[i].ceof,muilt_Result[i].expn);
  printf("\n");
  
  system("pause");
  return 0;
}


