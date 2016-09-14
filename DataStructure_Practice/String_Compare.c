#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define max_pattern_size 100  
int failure[max_pattern_size];//失敗陣列

int pmatch(char *string,char *pat)
{
  int i=0,j=0;
  int lens=strlen(string);//string的長度
  int lenp=strlen(pat);//pat的長度
  while(i<lens&&j<lenp)//
  {
    if(string[i]==pat[j])//i=j繼續比對下一個字
      {
        i++;
        j++;
      }
    else if(j==0)    i++; //j=0代表的pat的第一個字還沒找到 所以繼續走訪string 所以才要i++
     else j=failure[j-1]+1;
  }

   return ( (j==lenp)?(i-lenp) :-1); //若 j=lenp就傳回（i-lenp的數值） 否則就傳回-1

}
void fail(char *pat)//失敗函式
{
  int n=strlen(pat);//取得patten的長度
  int i,j;
  failure[0]=-1;
   for(j=1;j<n;j++)
    {
       i=failure[j-1];

       while( ( pat[j]!=pat[i+1]&&(i>=0) ))
            i=failure[i];
 
        if(pat[j]==pat[i+1])
         failure[j]=i+1;
        else
         failure[j]=-1;
    }  
}
int main(void)
{
  
  char string[256],pat[256];//string=被比對的字串  pat=比對的樣本 

  printf("Please enter string: ");
  gets(string);
  while( strncmp("exit",pat,4)!=0 )//輸入比對字串 若輸入exit可以離開
   {
      printf("Please enter patten: ");//
      gets(pat);

      int key;
      fail(pat);
      key=pmatch(string,pat);//得到比對成功的pat在string的起始位置  例：string='1111222111'  pat='122'  所以key=3
     if(key==-1)
     printf("Error ! Not Find.\n");
     else if(key>=0)
     {
      printf("get it ,in the %d word\n",key+1);
      break;
     }
  }
  system("pause");
  return 0;
}


