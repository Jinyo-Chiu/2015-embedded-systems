#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#define STACK_SIZE 50 

#define ADD_SUB   1       /*代表 加減*/
#define MULT_DIV  2   	   /* 代表 乘除 */
#define LEFT      3         /* 代表左括號 */
#define RIGHT     4          /* 代表右括號 */

char stack[STACK_SIZE];       /* 堆疊陣列 */
int top=-1;                  /* 堆疊頂端指標 */ 
int priority[STACK_SIZE];        /*優先權堆疊 */


void push(char s,int number){
   if(top>=STACK_SIZE-1){
      printf("堆疊滿了");
   }
   else{
     top++;
     stack[top]=s;
     priority[top]=number;
   }
}

void pop(){
    if (top==-1){
      printf("堆疊已空\n");
    }
    else{
  /*不要印出  '('*/
       if( priority[top ]!=LEFT){
    printf("%c",stack[top]);
       }
       top--;
    }
} 

/* 運算子處理 */
void Operator(char ch,int number) {

  if(top==-1&&number!=RIGHT) /* 若堆疊為空 直接push */
      push(ch,number);
  else{
        switch(number){          
             /* 若輸入為 ')' 從堆疊頂端依序pop直到出現'('  */
           case RIGHT:
                for(priority[top];priority[top]!=LEFT;pop()) ;
                    pop();//把最後的 '(' pop 但不印出 
                break;                       
            /* 若輸入為 '('  直接 PUSH  */
           case LEFT:
                push(ch,number);
                break;    
            /* 若輸入是 '+' '-' '*' '/' */
           case ADD_SUB:
           case MULT_DIV:
   
                if( priority[top]==LEFT||priority[top]<number){
                   push(ch,number);
                }
                else{
       /* 若堆疊內優先權 大於number  */
                    while((priority[top]>=number)&&priority[top]!=LEFT)
                           pop(); /* 先POP 堆疊內再PUSH number  */ 
                    push(ch,number);
                }   
                break;
            /*當字串已scan完 堆疊不為空 pop 剩下的運算子*/           
            case 0:  
       while(top!=-1) 
                      pop();
                 break;
        }        
    }  
}         

int main(void){
    
    char *IndString;
    char buf[STACK_SIZE];
    int i=0;
    int error_OP = 0;
    printf("請輸入中序 :");
    IndString=gets(buf);//中序輸入
    printf("\n");
    printf("後序為:");

   /*若不等於結束字元*/ 
   while(*(IndString+i)!='\0' & !error_OP) {

       /*數字和字母是運算元所以直接印出 */
      if(isalnum(*(IndString+i))) {    
               printf("%c",*(IndString+i));
      }
      else if(ispunct(*(IndString+i))) {     //若不是數字 空白 字母  則為真 
       
             switch(*(IndString+i)){
                case '+':
                             Operator(*(IndString+i),ADD_SUB);                       
                             break;
                case '-':   
                             Operator(*(IndString+i),ADD_SUB);                       
                             break;         
             
                case '*':
                             Operator(*(IndString+i),MULT_DIV);
                             break;
                case '/':
                             Operator(*(IndString+i),MULT_DIV);
                             break;
                case '(':
                             Operator(*(IndString+i),LEFT);
                             break; 
                case ')':
                            Operator(*(IndString+i),RIGHT);
                            break;  
                default:
                            printf(" error Operator\n");
                            error_OP = 1;
       break;
            }   
       }     
     i++; 
   } 

   Operator('\0',0);//字串scan結束 
   puts("\n------------------------------------\n");
   return 0;
}