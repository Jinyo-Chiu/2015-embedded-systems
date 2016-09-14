#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#define size 50 //多項式的最大長度

typedef struct polynomial  
{
  int expn;//  次方
  float ceof;// 係數
}poly;

void Poly_Attach(poly n[],float Ceof,int Expn);  //插入多項式
void Poly_Remove(poly n[],int Expn);             //刪除多項式
poly *Single_Mult(poly b[],float Ceof,int Expn); //多項式單一項乘法
poly *Muilt(poly a[],poly b[]);                  //多項式乘法
void AddPoly(poly a[],poly b[],poly c[]);        //多項式加法

void Poly_Zero(poly n[])//創造出一個零多項式
{
   int i;
   for(i=0;i<size;i++)
    {
      n[i].expn=0;
      n[i].ceof=0.0;
     }
}
int Poly_IsZero(poly n[])//判斷是否為零多項式 若是則傳回  1
{
  if(n[0].ceof!=0)//若係數不為零
        return -1;
    else 
        return 1;
  
}
int LeadExp(poly n[])  //傳回一多項式的最高次方
{
   return n[0].expn;
}
float Coef(poly n[],int Expn)  //傳回某一次方項的係數
{
     int i,flag=0;
     if(Poly_IsZero(n)==1)//若為零多項式 傳回0
       return 0;

     for(i=0;n[i].ceof!=0;i++)
     {
         if(n[i].expn==Expn&&n[i].ceof!=0)
           {
            flag=1;  //代表有找到次方
            return n[i].ceof;
           } 
      }
    if(flag==0)//沒有找到
       {
         fprintf(stderr,"Coef() is Error\n");
          getch(); 
          exit(-1);
       }
}
void Poly_Attach(poly n[],float Ceof,int Expn)//插入一個項次 到多項式
{     
     int i,j=0,flag=0;
      poly temp; 
        
       for(i=0;n[i].ceof!=0;i++) //
           {
           if((n[i].expn==Expn))//若要插入的次方項 在此多項式已存在 則顯示錯誤
                  {
                fprintf(stderr,"Attach() is Error !\n");
                   getch(); 
                   exit(-1); 
                  }
           }
       if(Poly_IsZero(n)==1)//若此多項式是零多項式  則可以直接插入
           {
          n[0].expn=Expn;
          n[0].ceof=Ceof;
           } 
       else //開始插入多項式
         {
         for(i=0;n[i].ceof!=0;i++)  {} //找出此多項式長度

           n[i].expn=Expn;//將要插入的新次方項 先插入此多項式的尾端
           n[i].ceof=Ceof;//將要插入的新係數項 先插入此多項式的尾端
            for(j=i;j>0;j--)
               {
                if(n[j].expn>n[j-1].expn)//從多項式由後往前比較 然後交換  
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
void Poly_Remove(poly n[],int Expn)//刪除多項式的其中一項
{
   int i,flag=0;
    for(i=0;n[i].ceof!=0;i++)
      {
         if(n[i].expn==Expn)//多項式有這一項
          {
            int j;
            for(j=i;n[j].ceof!=0;j++)//把要刪除的項覆蓋掉 由後面的項一個一個補上
               {
              n[j].expn=n[j+1].expn;
              n[j].ceof=n[j+1].ceof;
                }
             flag=1;//代表刪除成功
              
          }
     }  
  if(flag==0)//刪除失敗
     {
      fprintf(stderr,"Remove() is Error \n");
      getch(); 
      exit(-1);
     }         
}
int Compare(int a,int b)//比較a,b
{
  if(a>b) 
     return 1;
  else if(a==b)
     return 0;
  else if(a<b)
     return -1;
}
void AddPoly(poly a[],poly b[],poly add_Result[])//執行多項式加法
{
    float sum=0.0;
   poly A[size],B[size];
   Poly_Zero(A);
   Poly_Zero(B);
   memcpy(A,a,size*sizeof(poly));//因為a[]還要用到 所以複製另一個自己 A[]來替代
   memcpy(B,b,size*sizeof(poly));//因為b[]還要用到 所以複製另一個自己 B[]來替代
       while((Poly_IsZero(A)==-1)&&(Poly_IsZero(B)==-1)) //當A[],B[]都不為空時
       {
         switch( Compare(LeadExp(A),LeadExp(B)))//比較A[],B[]的最高次方
         {
          case 1:  //A>B                                             
                   Poly_Attach( add_Result,Coef(A,LeadExp(A)),LeadExp(A) ); //插入多項式A到合成的多項式
                   Poly_Remove(A,LeadExp(A));   //刪除A的最高次方
                   break;
          case 0://A==B
                
                   sum=Coef(A,LeadExp(A))+Coef(B,LeadExp(B));   //A,B 次方相同 係數相加至sum
                   if(sum!=0)
                       {
                   Poly_Attach(add_Result,sum,LeadExp(A));
                   Poly_Remove(A,LeadExp(A));  //刪除A的最高次方
                   Poly_Remove(B,LeadExp(B));  //刪除B的最高次方
                       }
                   break;
         case -1: //A<B                                                
                   Poly_Attach(add_Result,Coef(B,LeadExp(B)),LeadExp(B) );//插入多項式B到合成的多項式
                   Poly_Remove(B,LeadExp(B));    //刪除B的最高次方
                   break;
        }
      }
  if(Poly_IsZero(A)<0) //若多項式A有剩餘項  則全部插入至合成的多項式 並刪除最高次方
     {
      for(;A[0].ceof!=0;Poly_Attach(add_Result,Coef(A,LeadExp(A)),LeadExp(A)),Poly_Remove(A,LeadExp(A))) {}
     }
  else if(Poly_IsZero(B)<0)//若多項式B有剩餘項  則全部插入至合成的多項式 並刪除最高次方
     {
      for(;B[0].ceof!=0;Poly_Attach(add_Result,Coef(B,LeadExp(B)),LeadExp(B)),Poly_Remove(B,LeadExp(B))) {}
     }
       
}
poly *Single_Mult(poly b[],float Ceof,int Expn)//執行單項式乘法
{
   static poly Result[size];//宣告為全域  因為要將整個陣列傳回去 
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
poly *Muilt(poly a[],poly b[])//多項式乘法
{ 
   static poly Result[size];//結果陣列
          Poly_Zero(Result);
  poly *temp;        //暫存指標 用來讀取Single_Mult（）傳來的陣列
  poly  trans[size];//轉送陣列
  Poly_Zero(trans);
  int i;
   for(i=0;a[i].ceof!=0;i++)
   {
     temp=Single_Mult(b,a[i].ceof,a[i].expn);
     AddPoly(temp,Result,trans);   //加法的結果會被放到trans
     memcpy(Result,trans,size*sizeof(poly)); //然後將trans複製到Result[]
     Poly_Zero(trans);  //將trans清空  然後再去執行新的加法  所以Result[]會一直累加 變大                      
   }
 return Result;
}
int main(void)
{
     poly a[size],b[size],add_Result[size];
     Poly_Zero(a);
     Poly_Zero(b);
     Poly_Zero(add_Result);
     poly *muilt_Result; //乘法指標  
     float ceof;  //係數
     int   expn;  //次方 

     int   i,length;
     printf("輸入A(X)  請問要幾項？\n");
      scanf("%d",&length);
    for (i=0; i<length; i++)
    {
     printf("第%d項 係數：  次方:  ",i+1);
     scanf("%f  %d",&ceof,&expn);
     Poly_Attach(a,ceof,expn);   //插入多項式
     }
   printf("\n輸入B(X)  請問要幾項？\t");
    scanf("%d",&length);
    for (i=0; i<length; i++)
    {
     printf("第%d項 係數：  次方:\t",i+1);
        scanf("%f  %d",&ceof,&expn);
     Poly_Attach(b,ceof,expn);//插入多項式
    }
    AddPoly(a,b,add_Result);//執行加法 
    printf("The A(x)+B(X)=\n");
    for(i=0;add_Result[i+1].ceof!=0;i++)
       printf("%.2fX^%d+",add_Result[i].ceof,add_Result[i].expn);
    printf("%.2fX^%d",add_Result[i].ceof,add_Result[i].expn);

     printf("\n\n\n");
     printf("The A(x)*B(x)=\n");
  
     muilt_Result=Muilt(a,b);//執行乘法 
    for(i=0;muilt_Result[i+1].ceof!=0;i++)   
      printf("%.2fX^%d+",muilt_Result[i].ceof,muilt_Result[i].expn);
   printf("%.2fX^%d",muilt_Result[i].ceof,muilt_Result[i].expn);
  printf("\n");
  
  system("pause");
  return 0;
}


